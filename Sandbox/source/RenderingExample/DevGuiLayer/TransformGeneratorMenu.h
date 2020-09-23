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

		ImGui::InputFloat3("scale", &m_scale.x, 2);
		ImGui::InputFloat3("rotation", &m_rot.x, 2);
		ImGui::InputFloat3("translation", &m_transl.x, 2);

		if (ImGui::Button("Generate"))
		{
			SW_ASSERT(m_load_to != nullptr, "nullptr load");

			glm::vec3 rot_rad = glm::radians(m_rot);
			*m_load_to = glm::translate(m_transl) * glm::eulerAngleXYZ(rot_rad.x, rot_rad.y, rot_rad.z) * glm::scale(m_scale);
			m_visible = false;
		}

		ImGui::End();
	}
	void SetLoad(glm::mat4* load_to) { m_load_to = load_to; }

	bool m_visible;
private:
	glm::mat4* m_load_to;
	glm::vec3 m_transl = {0,0,0};
	glm::vec3 m_scale = { 1,1,1 };
	glm::vec3 m_rot = { 0,0,0 };
};