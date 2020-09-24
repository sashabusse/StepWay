#include "../../usings.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"

class TransfofmGeneratorMenu
{
public:

	TransfofmGeneratorMenu() :
		m_visible(false),
		m_load_to(nullptr) {};

	TransfofmGeneratorMenu(glm::mat4* load_to) :
		m_visible(true),
		m_load_to(load_to) {};

	void Draw()
	{
		if (!m_visible) return;

		if (!ImGui::Begin("Transform Generator", &m_visible))
		{
			ImGui::End();
			return;
		}

		ImGui::Checkbox("##en_scale", &m_en_sc); ImGui::SameLine();
		ImGui::InputFloat3("scale", &m_scale.x, 2);

		ImGui::Checkbox("##en_rotation", &m_en_rot); ImGui::SameLine();
		ImGui::SliderFloat3("rotation", &m_rot.x, -180, 180, "%.2f");

		ImGui::Checkbox("##en_translation", &m_en_tr); ImGui::SameLine();
		ImGui::InputFloat3("translation", &m_transl.x, 2);

		ImGui::Checkbox("Continuous Generation", &m_continuous_gen);
		if(m_continuous_gen)
		{
			LoadCurrent();
		}

		if (ImGui::Button("Generate"))
		{
			LoadCurrent();
			m_visible = false;
		}

		ImGui::End();
	}
	void LoadCurrent()
	{
		SW_ASSERT(m_load_to != nullptr, "nullptr load");

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

	void SetLoad(glm::mat4* load_to) { m_load_to = load_to; }

	bool m_visible;
private:
	glm::mat4* m_load_to;
	bool m_en_tr = true;
	bool m_en_sc = true;
	bool m_en_rot = true;
	bool m_continuous_gen = false;
	glm::vec3 m_transl = {0,0,0};
	glm::vec3 m_scale = { 1,1,1 };
	glm::vec3 m_rot = { 0,0,0 };
};