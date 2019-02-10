#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Memory/Memory.h"


bool StepWay::Application::Init()
{
	m_IsRunning = false;

	m_MemoryManager.Init();
	m_MainWindow = Window::Create();

	//main window initialization
	WindowProp prop;
	prop.height = 600;
	prop.width = 1000;
	prop.luX = 100;
	prop.luY = 100;
	prop.title = L"Main App Window";

	if (!m_MainWindow->Init(prop))
	{
		SW_CORE_ERROR("failed to Init Window");
		return false;
	}
	m_MainWindow->SetEventCallback(SW_BIND_METH_1(Application::OnEvent));


	m_IsRunning = ImplInit();
	return m_IsRunning;
}


void StepWay::Application::ShutDown()
{
	ImplShutDown();

	m_MainWindow->Destroy();
	//make static method for window deletion
	SW_DELETE m_MainWindow;
	m_MemoryManager.Destroy();
	SW_TRACE("Successful App Destruction");
}


void StepWay::Application::Run()
{
	SW_CORE_TRACE("Entering Main Loop");
	while (m_IsRunning)
	{
		//update layers
		for(auto it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			(*it)->OnUpdate();
		}

		//update overlays
		for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
		{
			(*it)->OnUpdate();
		}


		m_MainWindow->OnUpdate();
	}
}

void StepWay::Application::OnEvent(Event & e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowDestroyEvent>(SW_BIND_METH_1(Application::OnMainWindowClose));

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

void StepWay::Application::PushLayer(Layer * layer)
{
	SW_CORE_TRACE("(Layer)");
	m_layers.PushLayer(layer);
}

void StepWay::Application::PopLayer(Layer * layer)
{
	m_layers.PopLayer(layer);
}

void StepWay::Application::PushOverLay(Layer * overlay)
{
	SW_CORE_TRACE("(Overlay)");
	m_overlays.PushLayer(overlay);
}

void StepWay::Application::PopOverlay(Layer * overlay)
{
	m_overlays.PopLayer(overlay);
}


StepWay::Application::~Application()
{
}

void StepWay::Application::OnMainWindowClose(WindowDestroyEvent & e)
{
	SW_CORE_INFO("Main window closed");
	m_IsRunning = false;
}
