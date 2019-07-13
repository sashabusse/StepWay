#include "StepWay.h"
#include <cstdio>


class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() {};

	bool ImplSetUp() override;
	void ImplShutDown() override;

	StepWay::Layer* layer;
};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}

class ExampleLayer : public StepWay::Layer
{
public:
	~ExampleLayer() {};

	virtual void OnAttach() override { SW_INFO("Example Layer Attached"); };
	virtual void OnDetach() override { SW_INFO("Example Layer Detached"); };
	virtual void OnUpdate() override { SW_INFO("Example Layer Update"); };
	virtual void OnEvent(StepWay::Event& e) override { SW_INFO("Example Layer Event"); };

	virtual std::string ToString() const { return "ExampleLayer"; };
	virtual std::wstring ToWString() const { return L"ExampleLayer"; };
protected:
};


bool SandboxApp::ImplSetUp()
{
	layer = SW_NEW ExampleLayer;
	//PushLayer(layer);
	return true;
}

void SandboxApp::ImplShutDown()
{
	PopLayer(layer);
	SW_DELETE layer;
}
