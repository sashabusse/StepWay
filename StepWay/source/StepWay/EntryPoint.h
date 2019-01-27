#pragma once
#include "Application.h"
#include "Log.h"


extern StepWay::Application* StepWay::CreateApplication();


#ifdef SW_PLATFORM_WINDOWS

int main()
{
	StepWay::Log::Init();

	StepWay::Application* app = StepWay::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif