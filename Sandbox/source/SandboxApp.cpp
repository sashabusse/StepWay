#include "StepWay.h"
#include <cstdio>


class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() { void* ptr = SW_ALIGNED_MALLOC(100, 16); SW_ALIGNED_FREE(ptr); };
};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creatin Application");
	return SW_NEW SandboxApp;
}

