#pragma once
#include "TransformGeneratorMenu.h"

void TransformMenu::Draw()
{
	ImGui::PushID(m_id);
	ImGui::Separator();
	
	//ImGui::Text(TypeToString(m_type).c_str());
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
		//later
	}
	ImGui::Separator();
	ImGui::PopID();
};


void TransfofmGeneratorMenu::LoadCurrent()
{
	SW_ASSERT(m_load_to != nullptr, "nullptr load");

	if (m_mode == 0)
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
	else
	{
		glm::mat4 result(1.0f);
		for (TransformMenu& menu : m_transforms)
		{
			result = menu.GenerateMatrix() * result;
		}
		*m_load_to = result;
	}
	

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
	for (TransformMenu& tr_menu : m_transforms)
	{
		tr_menu.Draw();
	}

	const char* types[] = { "Translate", "Scale", "Rotate" };
	ImGui::Combo("type", &m_nxt_type, types, IM_ARRAYSIZE(types));
	if (ImGui::Button("Add Transform"))
	{
		static int64 id = 0;
		m_transforms.push_back(TransformMenu((TransformMenu::TransformType)m_nxt_type, id));
		id++;
	}

}
