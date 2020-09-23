#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Input/InputSystem.h"
#include "Memory/Memory.h"
//Just WTF is it doing here?
#include "Graphics/API/Shader.h"
#include "glad/glad.h"
#include "OpenGL/ErrorHandling.h"
#include "Graphics/API/RenderingCommands.h"


using StepWay::Graphics::API::GraphicsContext;
using StepWay::Graphics::API::GAPI_TYPE;


using namespace StepWay::Graphics::API;


namespace StepWay
{
	
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		SW_CORE_ASSERT(m_Instance == nullptr, "App was already initialized! Double Initialization!!");
		m_Instance = this;
	}


	bool Application::SetUp()
	{
		m_IsRunning = false;

		m_MemoryManager.SetUp();//rename it

		m_InputSystem = Input::InputSystem::Create();
		m_InputSystem->SetUp();

		m_MainWindow = Window::Create();

		//main window initialization
		WindowProperties prop;
		prop.height = 800;
		prop.width = 800;
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

		m_MainContext = GraphicsContext::Create(GAPI_TYPE::OPENGL, m_MainWindow);
		m_MainContext->SetUp();
		m_MainContext->MakeCurrent();

		Input::Mouse::SetEventCallback(SW_BIND_METH_1(Application::OnEvent));
		Input::Keyboard::SetEventCallback(SW_BIND_METH_1(Application::OnEvent));


		m_layers.SetUp();
		m_overlays.SetUp();

		m_dbgGUILayer = std::make_shared<DebugGUILayer>(&Application::GetWindow(), &Application::GetContext());
		PushLayer(m_dbgGUILayer);

		m_IsRunning = ImplSetUp();
		
		return m_IsRunning;
	}


	void Application::ShutDown()
	{
		ImplShutDown();

		m_layers.ShutDown();
		m_overlays.ShutDown();


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
			ImplOnNewFrameStart();

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


			//update GUI
			m_dbgGUILayer->BeginFrame();
			//update layers
			for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
			{
				if ((*it)->Enabled())
					(*it)->OnGuiUpdate();
			}

			//update overlays
			for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
			{
				if ((*it)->Enabled())
					(*it)->OnGuiUpdate();
			}
			m_dbgGUILayer->EndFrame();
			

			m_MainContext->SwapBuffers();

			Input::Mouse::OnUpdate();
			m_MainWindow->OnUpdate();

			ImplOnNewFrameEnd();
		}
	}

	void Application::OnEvent(Event & e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowDestroyEvent>(SW_BIND_METH_1(Application::OnMainWindowClose));
		dispatcher.Dispatch<WindowResizeEndEvent>(SW_BIND_METH_1_TO(Graphics::API::GraphicsContext::OnWindowResize, &Application::GetContext()));

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