#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Input/InputSystem.h"
#include "Memory/Memory.h"
//Just WTF is it doing here?
#include "Layers/DebugGUI/Win32Opengl/DebugGUILayer.h"
#include "glad/glad.h"


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
		

		m_MainContext = GraphicsContext::Create(GAPI_TYPE::OPENGL, m_MainWindow);
		m_MainContext->SetUp();
		m_MainContext->MakeCurrent();


		//---------------------------------------
		PushLayer(new DebugGUILayer(m_MainWindow, m_MainContext));
		//---------------------------------------


		m_IsRunning = ImplSetUp();
		return m_IsRunning;
	}


	void Application::ShutDown()
	{
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
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

			glClear(GL_COLOR_BUFFER_BIT);


			glBegin(GL_QUADS);

			glVertex2f(-0.8, -0.8);

			glVertex2f(0.8, -0.8);

			glVertex2f(0.8, 0.8);

			glVertex2f(-0.8, 0.8);

			glEnd();


			//update layers
			for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
			{
				(*it)->OnUpdate();
			}

			//update overlays
			for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
			{
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
			(*it)->OnEvent(e);
		}

		//Messaging layers
		for (auto it = m_layers.end(); it != m_layers.begin();)
		{
			--it;
			(*it)->OnEvent(e);
		}

	}

	void Application::PushLayer(Layer * layer)
	{
		SW_CORE_TRACE("(Layer)");
		m_layers.PushLayer(layer);
	}

	void Application::PopLayer(Layer * layer)
	{
		m_layers.PopLayer(layer);
	}

	void Application::PushOverLay(Layer * overlay)
	{
		SW_CORE_TRACE("(Overlay)");
		m_overlays.PushLayer(overlay);
	}

	void Application::PopOverlay(Layer * overlay)
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