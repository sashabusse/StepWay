#include "StepWay.h"
#include "EntryPoint.h"
#include "RenderingExample/RenderingExample.h"
#include "RenderingExample/DevGuiLayer/DevGuiLayer.h"

class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() {};

	bool ImplSetUp()
	{
		SW_CORE_LEVEL_INFO();
		SW_LEVEL_TRACE();
		PushOverLay(std::shared_ptr<StepWay::Layer>(new DevGuiLayer()));
		PushLayer(std::shared_ptr<StepWay::Layer>(new RenderingExample()));
		return true;
	};
	void ImplShutDown()
	{
	};
	void ImplOnNewFrameStart() {};
	void ImplOnNewFrameEnd() {};
	StepWay::Layer* layer;

private:

};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}