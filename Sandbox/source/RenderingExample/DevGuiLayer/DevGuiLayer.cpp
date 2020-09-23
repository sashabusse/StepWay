#include "DevGuiLayer.h"

void DevGuiLayer::OnAttach()
{
}

void DevGuiLayer::OnDetach()
{
}

void DevGuiLayer::OnGuiUpdate()
{
	if (m_MainMenuState.ShowAppStatistics) { ImGui::ShowMetricsWindow(&(m_MainMenuState.ShowAppStatistics)); }
	if (m_MainMenuState.ShowStyleEditor) { ImGui::Begin("Style Editor", &(m_MainMenuState.ShowStyleEditor)); ImGui::ShowStyleEditor(); ImGui::End(); }

	ImGui::Begin("menu bar", 0, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Metrics", NULL, &(m_MainMenuState.ShowAppStatistics));
			ImGui::MenuItem("Style Editor", NULL, &(m_MainMenuState.ShowStyleEditor));
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scenes"))
		{
			int ind = 1;
			for (SceneManagerMenu& sc_menu : m_scene_managers)
			{
				ImGui::MenuItem((std::string("Scene ") + std::to_string(ind)).c_str(), NULL, &(sc_menu.m_scene_manager_opened));
			}
		
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();
	for (SceneManagerMenu& sc_menu : m_scene_managers)
	{
		sc_menu.Draw();
	}


}

void DevGuiLayer::OnEvent(StepWay::Event& e)
{
	if (e.GetEventType() == EventType::SCENE_CREATED)
	{
		Scene* scene = static_cast<SceneCreateEvent*>(&e)->GetScenePtr();
		m_scene_managers.push_back(SceneManagerMenu(*scene));
	}

	if (e.GetEventType() == EventType::ENTITY_CREATED)
	{
		Entity ent = static_cast<EntityCreateEvent*>(&e)->GetEntity();

		for (SceneManagerMenu& sc_menu : m_scene_managers)
		{
			sc_menu.OnEntityCreate(ent);
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
