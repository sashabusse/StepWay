#pragma once
#include "../../usings.h"
#include "SceneManagerMenu.h"
#include "LogConsole.h"



class DevGuiLayer : public StepWay::Layer
{
public:
	DevGuiLayer() {};

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnGuiUpdate() override;
	virtual void OnEvent(StepWay::Event& e) override;

	virtual std::string ToString() const override;
	virtual std::wstring ToWString() const override;

	virtual ~DevGuiLayer() {};


	void AddScene(Scene* scene)//temporary here move this functionality to on_event
	{
		m_scene_managers.push_back(SceneManagerMenu(*scene));
	}

private:

	struct MainMenuState
	{
		bool ShowAppStatistics = false;
		bool ShowStyleEditor = false;
		bool ShowLogConsole = false;
	} m_MainMenuState;

	std::list<SceneManagerMenu> m_scene_managers;
	LogConsole m_log_console;
	
};