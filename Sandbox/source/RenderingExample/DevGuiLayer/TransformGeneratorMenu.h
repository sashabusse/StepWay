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
		m_type(type), m_id(id), m_data({ 0,0,0 }), m_enable(true), m_delete(false)
	{
		if (type == TransformType::TRANSLATE || type == TransformType::ROTATE)
			m_data = glm::vec3({ 0,0,0 });
		else if (type == TransformType::SCALE)
			m_data = glm::vec3({ 1,1,1 });
	};
	
	void Draw();
	void SetType(TransformType type) { m_type = type; };
	bool ShouldDelete() { return m_delete; };
	glm::mat4 GenerateMatrix();

private:
	glm::vec3 m_data;
	TransformType m_type;
	int64 m_id;
	bool m_enable = true;
	bool m_delete = false;
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

	void SetLoad(glm::mat4* load_to) { m_load_to = load_to; }
	void LoadCurrent();

	bool m_visible;
private:
	void LoadCurrentMode0();
	void LoadCurrentMode1();
	void DrawMode0();
	void DrawMode1();
private:
	//common variables
	glm::mat4* m_load_to;
	bool m_continuous_gen = false;
	int m_mode = 0;
	//mode 0 variables
	bool m_en_tr = true;
	bool m_en_sc = true;
	bool m_en_rot = true;
	glm::vec3 m_transl = { 0,0,0 };
	glm::vec3 m_scale = { 1,1,1 };
	glm::vec3 m_rot = { 0,0,0 };
	//mode 1 variables
	std::list<TransformMenu> m_transforms;
	int m_nxt_type = 0;
};