#include "DevGuiLayer.h"

void DevGuiLayer::OnAttach()
{
}

void DevGuiLayer::OnDetach()
{
}

void DevGuiLayer::OnGuiUpdate()
{
	//statistics
	if (m_MainMenuState.ShowAppStatistics) { ImGui::ShowMetricsWindow(&(m_MainMenuState.ShowAppStatistics)); }
	//style settings
	if (m_MainMenuState.ShowStyleEditor) { ImGui::Begin("Style Editor", &(m_MainMenuState.ShowStyleEditor)); ImGui::ShowStyleEditor(); ImGui::End(); }

	//main debug window
	ImGui::Begin("Debug GUI", 0, ImGuiWindowFlags_MenuBar);

	//menu
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Metrics", NULL, &(m_MainMenuState.ShowAppStatistics));
			ImGui::MenuItem("Style Editor", NULL, &(m_MainMenuState.ShowStyleEditor));
			ImGui::EndMenu();
		}

		//Scenes menu openers
		if (ImGui::BeginMenu("Scenes"))
		{
			for (SceneManagerMenu& sc_menu : m_scene_managers)
			{
				ImGui::MenuItem((std::string("Scene ") + std::to_string(sc_menu.GetScen().GetUID())).c_str(), NULL, &(sc_menu.m_scene_manager_opened));
			}
		
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();

	//Draw all the scene managers
	for (SceneManagerMenu& sc_menu : m_scene_managers)
	{
		sc_menu.Draw();
	}


}

void DevGuiLayer::OnEvent(StepWay::Event& e)
{

	//bool opened = true;
	//ImGui::ShowDemoWindow(&opened);

	if (e.GetEventType() == EventType::SCENE_CREATED)
	{
		Scene* scene = static_cast<SceneCreateEvent*>(&e)->GetScenePtr();
		m_scene_managers.push_back(SceneManagerMenu(*scene));
	}

	if (e.GetEventType() == EventType::SCENE_DESTROYED)
	{

		SceneDestroyEvent& sde = static_cast<SceneDestroyEvent&>(e);
		for (auto it = m_scene_managers.begin(); it!=m_scene_managers.end();it++)
		{
			SceneManagerMenu& sc_menu = *it;
			if (sc_menu.GetScen().GetUID() == sde.GetScenePtr()->GetUID())
			{
				m_scene_managers.erase(it);
				break;
			}
		}

	}

	if (e.GetEventType() == EventType::ENTITY_CREATED ||
		e.GetEventType() == EventType::ENTITY_DESTROYED)
	{
		for (SceneManagerMenu& sc_menu : m_scene_managers)
		{
			sc_menu.OnEvent(e);
		}
	}

}

std::string DevGuiLayer::ToString() const
{
	return "DevGuiLayer";
}

std::wstring DevGuiLayer::ToWString() const
{
	return L"DevGuiLayer";
}
