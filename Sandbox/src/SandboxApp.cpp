#include "StepWay.h"
#include <cstdio>

class SandboxApp :public StepWay::Application
{
public:

};


StepWay::Application* StepWay::CreateApplication()
{
	printf("Creating Application\n");
	return new SandboxApp;
}

