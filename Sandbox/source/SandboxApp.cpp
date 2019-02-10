#include "StepWay.h"
#include <cstdio>
#include "Platform/Win32/Win32Window.h"


class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() {};
};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creatin Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;
	return sandboxApp;
}

