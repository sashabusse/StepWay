#include "StepWay.h"
#include <cstdio>


class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() { new char[1000]; };
};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creatin Application");
	return new SandboxApp;
}

