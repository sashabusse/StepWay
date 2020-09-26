#include "SceneManagerMenu.h"
#pragma once

void SceneManagerMenu::OnEvent(StepWay::Event& e)
{
	if (e.GetEventType() == EventType::ENTITY_CREATED)
	{
		Entity ent = static_cast<EntityCreateEvent*>(&e)->GetEntity();
		OnEntityCreate(ent);
	}
	if (e.GetEventType() == EventType::ENTITY_DESTROYED)
	{
		// nothing just validate entity before using
	}
}

void SceneManagerMenu::OnEntityCreate(Entity& ent)
{//and not forget about scene managers id and other on event
	m_menus.push_back(EntityMenu(ent));
}

void SceneManagerMenu::Draw()
{

	if (!m_scene_manager_opened) return;

	ImGui::PushID(m_scene.GetUID());

	if (!ImGui::Begin((std::string("Scene ") + std::to_string(m_scene.GetUID())).c_str(), &m_scene_manager_opened, ImGuiWindowFlags_MenuBar))
	{
		ImGui::End();
		return;
	}


	auto it = m_menus.begin();
	while (it != m_menus.end())
	{
		EntityMenu& menu = *it;
		if (menu.IsValid())
		{
			menu.Draw();
			it++;
		}
		else
		{
			it = m_menus.erase(it);
		}
	}

	ImGui::End();

	ImGui::PopID();
}



EntityMenu::EntityMenu(Entity& ent):
	m_entity(ent),
	//Mesh
	m_primitive_type(0),
	m_cube_pos({0,0,0}),
	m_cube_size({1,1,1}),
	m_plane_axes(0),
	m_plane_pos({0,0,0}),
	m_plane_size({1,1})
{
	memset(m_load_path, 0, sizeof(m_load_path));
};

void EntityMenu::Draw()
{
	ImGui::PushID(m_entity.GetUID());

	std::string name = std::string("Entity") + std::to_string(m_entity.GetUID());
	if (m_entity.HasComponent<NameComponent>())
		name = m_entity.GetComponent<NameComponent>().name;

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		DrawTransform();
		DrawMesh();
		DrawCamera();
		DrawNativeScript();

	}
	ImGui::PopID();
}

void EntityMenu::DrawTransform()
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
		ImGui::Separator();
	}
	m_tr_gen_menu.Draw();
}

void EntityMenu::DrawMesh()
{
	if (m_entity.HasComponent<MeshComponent>())
	{
		MeshComponent& mesh_c = m_entity.GetComponent<MeshComponent>();
		if (ImGui::TreeNode("Mesh"))
		{
			ImGui::Checkbox("visible", &mesh_c.visible);
			if (ImGui::Button("make flat normals"))
			{
				mesh_c.GetMesh().MakeFlatNormals();
				mesh_c.GetMesh().SetUpBuffers();
			}

			ImGui::Separator();

			ImGui::Text("Load From File");
			ImGui::InputText("##path", m_load_path, IM_ARRAYSIZE(m_load_path));
			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				mesh_c.SetMesh(Load3DModel(m_load_path)[0]);
				mesh_c.GetMesh().SetUpBuffers();
			}

			ImGui::Separator();

			ImGui::Text("Load Primitive");

			const char* types[] = { "Cube", "Plane" };
			ImGui::Combo("type", &m_primitive_type, types, IM_ARRAYSIZE(types));

			if (m_primitive_type == 0)//Cube
			{

				ImGui::PushID("Cube");

				ImGui::DragFloat3("position", &m_cube_pos.x, 0.01, 0);
				ImGui::DragFloat3("size", &m_cube_size.x, 0.01, 0);
				if (ImGui::Button("Load"))
				{
					mesh_c.SetMesh(LoadCube(m_cube_pos, m_cube_size));
					mesh_c.GetMesh().SetUpBuffers();
				}
				ImGui::PopID();
			}
			else
			{
				ImGui::PushID("Plane");

				const char* axes_types[] = { "XY", "XZ", "YZ" };
				ImGui::Combo("Axes", &m_plane_axes, axes_types, IM_ARRAYSIZE(axes_types));

				ImGui::DragFloat3("position", &m_plane_pos.x, 0.01, 0);
				ImGui::DragFloat2("size", &m_plane_size.x, 0.01, 0);

				if (ImGui::Button("Load"))
				{
					if (m_plane_axes == 0)
						mesh_c.SetMesh(LoadPlaneXY(m_plane_pos, m_plane_size));
					else if (m_plane_axes == 1)
						mesh_c.SetMesh(LoadPlaneXZ(m_plane_pos, m_plane_size));
					else
						mesh_c.SetMesh(LoadPlaneYZ(m_plane_pos, m_plane_size));
					mesh_c.GetMesh().SetUpBuffers();
				}

				ImGui::PopID();
			}


			ImGui::TreePop();
			ImGui::Separator();
		}
	}
}

void EntityMenu::DrawCamera()
{
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
			ImGui::Separator();
		}

	}
}

void EntityMenu::DrawNativeScript()
{
	if (m_entity.HasComponent<NativeScriptComponent>())
	{
		if (ImGui::TreeNode("Native Script"))
		{
			NativeScriptComponent& script_c = m_entity.GetComponent<NativeScriptComponent>();

			ImGui::Checkbox("enabled", &(script_c.m_enabled));

			ImGui::TreePop();
			ImGui::Separator();
		}
	}
}
