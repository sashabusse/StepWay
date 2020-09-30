#pragma once
#include "TransformGeneratorMenu.h"
#include "imgui.h"

void TransformMenu::Draw()
{
	ImGui::PushID(m_id);
	ImGui::Separator();
	
	const char* m_types[] = { "Translate", "Scale", "Rotate" };
	ImGui::Combo("Type", (int*)&m_type, m_types, IM_ARRAYSIZE(m_types));

	if (m_type == TransformType::TRANSLATE)
	{
		ImGui::DragFloat3("##data", &m_data.x, 0.05f, 0, 0, "%.2f");
	}
	else if (m_type == TransformType::SCALE)
	{
		ImGui::DragFloat3("##data", &m_data.x, 0.02f, 0, 0, "%.2f");
	}
	else if (m_type == TransformType::ROTATE)
	{
		ImGui::DragFloat3("##data", &m_data.x, 1.0f, -180, 180, "%.2f");
	}
	ImGui::Checkbox("Enable", &m_enable);
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
		m_delete = true;
	}
	ImGui::Separator();
	ImGui::PopID();
}

glm::mat4 TransformMenu::GenerateMatrix()
{
	if (!m_enable) return glm::mat4(1.0f);
	if (m_type == TransformType::TRANSLATE)
	{
		return glm::translate(m_data);
	}
	else if (m_type == TransformType::SCALE)
	{
		return glm::scale(m_data);
	}
	else if (m_type == TransformType::ROTATE)
	{
		glm::vec3 rot_rad = glm::radians(m_data);
		return glm::eulerAngleXYZ(rot_rad.x, rot_rad.y, rot_rad.z);
	}
};


void TransfofmGeneratorMenu::LoadCurrent()
{
	SW_ASSERT(m_load_to != nullptr, "nullptr load");

	if (m_mode == 0)
	{
		LoadCurrentMode0();
	}
	else
	{
		LoadCurrentMode1();
	}
}

void TransfofmGeneratorMenu::LoadCurrentMode0()
{
	glm::vec3 rot_rad = glm::radians(m_rot);

	glm::mat4 result(1.0f);
	if (m_en_sc)
		result = glm::scale(m_scale) * result;
	if (m_en_rot)
		result = glm::eulerAngleXYZ(rot_rad.x, rot_rad.y, rot_rad.z) * result;
	if (m_en_tr)
		result = glm::translate(m_transl) * result;

	*m_load_to = result;
}

void TransfofmGeneratorMenu::LoadCurrentMode1()
{
	glm::mat4 result(1.0f);
	for (TransformMenu& menu : m_transforms)
	{
		result = menu.GenerateMatrix() * result;
	}
	*m_load_to = result;
}



void TransfofmGeneratorMenu::Draw()
{
	if (!m_visible) return;

	if (!ImGui::Begin("Transform Generator", &m_visible, ImGuiWindowFlags_MenuBar))
	{
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Mode"))
		{
			const char* modes[] = { "Mode 0", "Mode 1" };
			ImGui::Combo("Mode", &m_mode, modes, IM_ARRAYSIZE(modes));
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::Button("Generate"))
	{
		LoadCurrent();
	}
	ImGui::SameLine();
	ImGui::Checkbox("Continuous Generation", &m_continuous_gen);
	if (m_continuous_gen)
	{
		LoadCurrent();
	}

	
	if (m_mode == 0)
	{
		DrawMode0();
	}
	else
	{
		DrawMode1();
	}


	ImGui::End();
}





void TransfofmGeneratorMenu::DrawMode0()
{
	ImGui::Checkbox("##en_scale", &m_en_sc); ImGui::SameLine();
	ImGui::DragFloat3("Scale", &m_scale.x, 0.02f, 0, 0, "%.2f");

	ImGui::Checkbox("##en_rotation", &m_en_rot); ImGui::SameLine();
	ImGui::DragFloat3("Rotation", &m_rot.x, 1.0f, -180, 180, "%.2f");

	ImGui::Checkbox("##en_translation", &m_en_tr); ImGui::SameLine();
	ImGui::DragFloat3("Translation", &m_transl.x, 0.05f, 0, 0, "%.2f");
}

void TransfofmGeneratorMenu::DrawMode1()
{
	auto transforms_it = m_transforms.begin();
	while (transforms_it != m_transforms.end())
	{
		TransformMenu& tr_menu = *transforms_it;

		tr_menu.Draw();
		if (tr_menu.ShouldDelete())
			transforms_it = m_transforms.erase(transforms_it);
		else
			transforms_it++;
	}

	const char* types[] = { "Translate", "Scale", "Rotate" };
	ImGui::Combo("type", &m_nxt_type, types, IM_ARRAYSIZE(types));
	if (ImGui::Button("Add Transform"))
	{
		static LocalUIDGenerator uid_gen;
		m_transforms.push_back(TransformMenu((TransformMenu::TransformType)m_nxt_type, uid_gen.NextID()));
	}

}
