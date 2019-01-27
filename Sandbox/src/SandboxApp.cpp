#include "StepWay.h"
#include <cstdio>

class SandboxApp :public StepWay::Application
{
public:

};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creatin Application");
	return new SandboxApp;
}

