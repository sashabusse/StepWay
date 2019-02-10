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
	m_MainWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	SW_CORE_INFO("Successful App Initialization");

	m_IsRunning = true;
	return true;
}


void StepWay::Application::Destroy()
{
	m_MainWindow->Destroy();
	//make static method for window deletion
	SW_DELETE m_MainWindow;
	m_MemoryManager.Destroy();
	SW_TRACE("Successful App Destruction");
}


void StepWay::Application::Run()
{
	SW_CORE_TRACE("Running...");
	while (m_IsRunning)
	{
		m_MainWindow->OnUpdate();
	}
}

void StepWay::Application::OnEvent(Event & e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowDestroyEvent>
		(std::bind(&Application::OnMainWindowClose,this,std::placeholders::_1));
}


StepWay::Application::~Application()
{
}

void StepWay::Application::OnMainWindowClose(WindowDestroyEvent & e)
{
	SW_CORE_INFO("Main window closed");
	m_IsRunning = false;
}
