#pragma once
#include "../../usings.h"
#include "TransformGeneratorMenu.h"



class EntityMenu
{
public:
	EntityMenu(Entity& ent);

	bool IsValid() { return m_entity.IsValid(); }

	void Draw();
private:
	void DrawTransform();
	void DrawMesh();
	void DrawCamera();
	void DrawNativeScript();
private:
	Entity m_entity;

	//Transform Menu
	TransfofmGeneratorMenu m_tr_gen_menu;

	//Mesh
	char m_load_path[512];
	int m_primitive_type;
	glm::vec3 m_cube_pos;
	glm::vec3 m_cube_size;
	int m_plane_axes;
	glm::vec3 m_plane_pos;
	glm::vec2 m_plane_size;

};

class SceneManagerMenu
{
public:
	SceneManagerMenu(Scene& scene) :
		m_scene(scene) {};

	Scene& GetScen() { return m_scene; };
	void Draw();
	void OnEvent(StepWay::Event& e);

	//why it's still here
	bool m_scene_manager_opened = false;
private:
	void OnEntityCreate(Entity& ent);
	//void OnEntityDestroy(Entity& ent); not neded just use validate
private:
	std::list<EntityMenu> m_menus;
	Scene& m_scene;

};
