#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Input/InputSystem.h"
#include "Memory/Memory.h"
//Just WTF is it doing here?
#include "Layers/DebugGUI/DebugGUILayer.h"
#include "glad/glad.h"
#include "Graphics/API/Buffer.h"


using StepWay::Graphics::API::GraphicsContext;
using StepWay::Graphics::API::GAPI_TYPE;


namespace StepWay
{

	
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		SW_CORE_ASSERT(m_Instance == nullptr, "App was already initialized! Double Initialization!!");
		m_Instance = this;
	}

	//------------------------------------------------
	static Layer* dbgGui;
	static Graphics::API::VertexBuffer* buffer;
	using Graphics::API::ShaderDataType;
	//------------------------------------------------

	bool Application::SetUp()
	{
		m_IsRunning = false;

		m_MemoryManager.SetUp();//rename it

		m_InputSystem = Input::InputSystem::Create();
		m_InputSystem->SetUp();

		//TODO:
		//decide where to SetUp call!!!
		m_MainWindow = Window::Create();//think about protected constructors


		//main window initialization
		WindowProp prop;
		prop.height = 500;
		prop.width = 500;
		prop.luX = 100;
		prop.luY = 100;
		prop.title = "Main App Window";


		if (!m_MainWindow->SetUp(prop))
		{
			SW_CORE_ERROR("failed to Init Window");
			return false;
		}
		m_MainWindow->SetEventCallback(SW_BIND_METH_1(Application::OnEvent));
		m_MainWindow->SetPosition(0, 0);

		m_MainWindow->GetMouse().SetEventCallback(SW_BIND_METH_1(Application::OnEvent));
		m_MainWindow->GetKeyboard().SetEventCallback(SW_BIND_METH_1(Application::OnEvent));

		m_MainContext = GraphicsContext::Create(GAPI_TYPE::OPENGL, m_MainWindow);
		m_MainContext->SetUp();
		m_MainContext->MakeCurrent();

		m_layers.SetUp();
		m_overlays.SetUp();

		//---------------------------------------
		PushLayer(std::make_shared<DebugGUILayer>(m_MainWindow, m_MainContext));

		float data[9] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		buffer = Graphics::API::VertexBuffer::Create(Graphics::API::GAPI_TYPE::OPENGL);
		buffer->SetUp(data, 9 * sizeof(float));
		buffer->Bind();
		buffer->SetLayout({ ShaderDataType::FLOAT3 });
		//---------------------------------------


		m_IsRunning = ImplSetUp();
		return m_IsRunning;
	}


	void Application::ShutDown()
	{

		m_layers.ShutDown();
		m_overlays.ShutDown();

		ImplShutDown();


		m_MainContext->ShutDown();
		GraphicsContext::Destroy(m_MainContext);


		m_MainWindow->ShutDown();
		Window::Destroy(m_MainWindow);


		m_InputSystem->ShutDown();
		Input::InputSystem::Destroy(m_InputSystem);


		m_MemoryManager.ShutDown();
		SW_TRACE("Successful App Destruction");
	}


	void Application::Run()
	{
		SW_CORE_TRACE("Entering Main Loop");
		while (m_IsRunning)
		{
		
			//some test rendering here
			glClear(GL_COLOR_BUFFER_BIT);
			
			uint32 VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			{
				int i = 0;
				for (auto& element : buffer->GetLayout())
				{
					glEnableVertexAttribArray(i);
					glVertexAttribPointer(i, element.GetComponentCount(), GL_FLOAT, GL_TRUE, buffer->GetLayout().GetStride(), (void*)element.GetOffset());
					i++;
				}
			}
			
			glDrawArrays(GL_TRIANGLES, 0, 3);
			
			glDisableVertexAttribArray(0);
			glDeleteVertexArrays(1, &VAO);
			
			
			

			//update layers
			for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
			{
				if((*it)->Enabled())
					(*it)->OnUpdate();
			}
			
			//update overlays
			for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
			{
				if((*it)->Enabled())
					(*it)->OnUpdate();
			}
			

			m_MainContext->SwapBuffers();
			
			m_MainWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event & e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowDestroyEvent>(SW_BIND_METH_1(Application::OnMainWindowClose));

		SW_CORE_WARNING(e.ToString());

		//Messaging overlays
		for (auto it = m_overlays.end(); it != m_overlays.begin();)
		{
			--it;
			if ((*it)->Enabled())
				(*it)->OnEvent(e);
		}

		//Messaging layers
		for (auto it = m_layers.end(); it != m_layers.begin();)
		{
			--it;
			if ((*it)->Enabled())
				(*it)->OnEvent(e);
		}

	}

	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		SW_CORE_TRACE("(Layer)");
		m_layers.PushLayer(layer);
	}

	void Application::PopLayer(std::shared_ptr<Layer> layer)
	{
		m_layers.PopLayer(layer);
	}

	void Application::PushOverLay(std::shared_ptr<Layer> overlay)
	{
		SW_CORE_TRACE("(Overlay)");
		m_overlays.PushLayer(overlay);
	}

	void Application::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		m_overlays.PopLayer(overlay);
	}


	Application::~Application()
	{
	}

	void Application::OnMainWindowClose(WindowDestroyEvent & e)
	{
		SW_CORE_INFO("Main window closed");
		m_IsRunning = false;
	}

}