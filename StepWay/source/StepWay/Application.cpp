#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"


bool StepWay::Application::Init()
{
	m_MemoryManager.Init();

	SW_TRACE("Successful App Initialization");
	return true;
}


void StepWay::Application::Destroy()
{
	m_MemoryManager.Destroy();
	SW_TRACE("Successful App Destruction");
}


void StepWay::Application::Run()
{
	SW_CORE_TRACE("Running...");
}


StepWay::Application::~Application()
{
}
