#include "SceneManagerMenu.h"
#pragma once

void SceneManagerMenu::OnEntityCreate(Entity& ent)
{
	SW_ASSERT(m_cur_ind <= 1000 * 1000, "limit of menus reached");
	m_menus.push_back(EntityMenu(ent, m_cur_ind));
	m_cur_ind++;
}

void SceneManagerMenu::Draw()
{
	//for
//bool opened = true;
//ImGui::ShowDemoWindow(&opened);

	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);


	if (!m_scene_manager_opened) return;

	if (!ImGui::Begin("Scene Manager", &m_scene_manager_opened, ImGuiWindowFlags_MenuBar))
	{
		ImGui::End();
		return;
	}

	int no_name_ind = 1;
	int ind = 0;

	auto it = m_menus.begin();
	while (it != m_menus.end())
	{
		EntityMenu& menu = *it;
		if (menu.IsValid())
		{
			menu.Show();
			it++;
		}
		else
		{
			it = m_menus.erase(it);
		}
	}

	ImGui::End();
}

void EntityMenu::Show()
{
	ImGui::PushID(m_id);

	std::string name = std::string("No name Entity");
	if (m_entity.HasComponent<NameComponent>())
		name = m_entity.GetComponent<NameComponent>().name;

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		if (ImGui::TreeNode("Transform"))
		{
			TransformComponent& transform_c = m_entity.GetComponent<TransformComponent>();

			ImGui::InputFloat4("##row 1", &transform_c.transform[0][0], 2);
			ImGui::InputFloat4("##row 2", &transform_c.transform[1][0], 2);
			ImGui::InputFloat4("##row 3", &transform_c.transform[2][0], 2);
			ImGui::InputFloat4("##row 4", &transform_c.transform[3][0], 2);

			if (ImGui::Button("Generate Transform"))
			{
				m_tr_gen_menu.SetLoad(&(transform_c.transform));
				m_tr_gen_menu.m_visible = true;
			}

			

			ImGui::TreePop();
		}
		//mb move inside transform 
		m_tr_gen_menu.Draw();

		if (m_entity.HasComponent<MeshComponent>())
		{
			MeshComponent& mesh_c = m_entity.GetComponent<MeshComponent>();
			if (ImGui::TreeNode("Mesh"))
			{
				ImGui::Checkbox("visible", &mesh_c.visible);
				ImGui::TreePop();
			}
		}
		if (m_entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNode("Camera"))
			{
				CameraComponent& cam_c = m_entity.GetComponent<CameraComponent>();

				ImGui::DragFloat("FOV", &(cam_c.m_FOV), 1, 1, 180);
				ImGui::InputFloat("near", &(cam_c.m_near), 0.1, 0.1, 1);
				ImGui::InputFloat("far", &(cam_c.m_far), 1, 10, 0);
				ImGui::InputFloat("aspect ratio", &(cam_c.m_AspectRatio), 0.05, 0.1, 2);

				ImGui::TreePop();
			}

		}

	}
	ImGui::PopID();
}
