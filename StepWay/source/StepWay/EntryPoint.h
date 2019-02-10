#pragma once
#include "Core.h"
#include "Application.h"
#include "Memory/Memory.h"
#include "Log.h"



extern StepWay::Application* StepWay::CreateApplication();

#ifdef SW_PLATFORM_WINDOWS

int main()
{
	//memory leak detection
#if defined(SW_PLATFORM_WINDOWS) && defined(SW_DEBUG)
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpFlag);
#endif
	
	StepWay::Log::Init();

	StepWay::Application* app = StepWay::CreateApplication();
	if (!app->Init())
	{
		SW_CORE_FATAL("App Initialization failed going down");
		return -1;
	}

	SW_CORE_INFO("Successful App Initialization");

	app->Run();
	app->ShutDown();
	SW_DELETE app;

	return 0;
}

#endif