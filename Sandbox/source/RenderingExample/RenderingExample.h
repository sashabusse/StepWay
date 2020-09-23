#pragma once
#include "../usings.h"



class RenderingExample : public StepWay::Layer
{
public:
	RenderingExample();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnGuiUpdate() override;
	virtual void OnEvent(StepWay::Event& e) override;

	virtual std::string ToString() const override;
	virtual std::wstring ToWString() const override;

	virtual ~RenderingExample() {};
private:

	Scene m_scene;
	Entity m_suzzane;
	Entity m_cam_entity;
	Entity m_ground_ent;
	Renderer m_renderer;

	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

	glm::vec4 m_color{ 1,1,1,1 };

	//GUI parameters
	struct MainMenuState
	{
		bool ShowAppStatistics = false;
		bool ShowStyleEditor = false;
	} m_MainMenuState;
	bool m_scene_manager_opened = true;
	ImGuiWindowFlags m_window_flags = ImGuiWindowFlags_MenuBar;
};