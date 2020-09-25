#include "../../usings.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"



class TransformMenu
{
public:
	enum class TransformType : int
	{
		TRANSLATE = 0, 
		SCALE,
		ROTATE
	};

	static std::string TypeToString(TransformType type)
	{
		if (type == TransformType::TRANSLATE) return "Translate";
		if (type == TransformType::SCALE) return "Scale";
		if (type == TransformType::ROTATE) return "Rotate";
	}

	TransformMenu(TransformType type, int64 id) :
		m_type(type), m_id(id) 
	{
		if (type == TransformType::TRANSLATE || type == TransformType::ROTATE)
			m_data = glm::vec3({ 0,0,0 });
		else if (type == TransformType::SCALE)
			m_data = glm::vec3({ 1,1,1 });
	};
	
	void Draw();
	
	void SetType(TransformType type) { m_type = type; };
	glm::mat4 GenerateMatrix()
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
	}


private:
	TransformType m_type;
	glm::vec3 m_data;
	int64 m_id;
	bool m_enable = true;
};


class TransfofmGeneratorMenu
{
public:

	TransfofmGeneratorMenu() :
		m_visible(false),
		m_load_to(nullptr) {};

	TransfofmGeneratorMenu(glm::mat4* load_to) :
		m_visible(true),
		m_load_to(load_to) {};

	void Draw();
	
	void LoadCurrent();
	

	void SetLoad(glm::mat4* load_to) { m_load_to = load_to; }

	bool m_visible;
private:
	void DrawMode0();
	void DrawMode1();

	glm::mat4* m_load_to;
	bool m_en_tr = true;
	bool m_en_sc = true;
	bool m_en_rot = true;
	bool m_continuous_gen = false;
	glm::vec3 m_transl = {0,0,0};
	glm::vec3 m_scale = { 1,1,1 };
	glm::vec3 m_rot = { 0,0,0 };

	std::list<TransformMenu> m_transforms;

	int m_nxt_type = 0;
	int m_mode = 0;
};