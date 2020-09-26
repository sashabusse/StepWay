#pragma once
#include "../usings.h"



class RenderingExample : public StepWay::Layer
{
public:
	RenderingExample();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(StepWay::Event& e) override;

	virtual std::string ToString() const override;
	virtual std::wstring ToWString() const override;

	virtual ~RenderingExample() {};
private:
	Scene m_scene;
	Entity m_cam_entity;
	Renderer m_renderer;
	std::shared_ptr<Shader> m_shader;
	glm::vec4 m_color{ 1,1,1,1 };
};