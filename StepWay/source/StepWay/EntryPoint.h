#pragma once
#include "Application.h"


extern StepWay::Application* StepWay::CreateApplication();


#ifdef SW_PLATFORM_WINDOWS

int main()
{
	//Initialization here


	StepWay::Application* app = StepWay::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif