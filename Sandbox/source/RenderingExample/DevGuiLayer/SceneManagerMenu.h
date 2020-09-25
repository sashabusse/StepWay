#pragma once
#include "../../usings.h"
#include "TransformGeneratorMenu.h"



class EntityMenu
{
public:
	EntityMenu(Entity& ent, int64 id) :
		m_entity(ent),
		m_id(id)
	{
		memset(m_load_path, 0, sizeof(m_load_path));
	};

	bool IsValid() { return m_entity.IsValid(); }

	void Show();
private:
	TransfofmGeneratorMenu m_tr_gen_menu;
	Entity m_entity;
	int64 m_id;

	char m_load_path[512];
};

class SceneManagerMenu
{
public:
	SceneManagerMenu(Scene& scene) :
		m_scene(scene),
		m_cur_ind(0) {};

	void OnEntityCreate(Entity& ent);
	//void OnEntityDestroy(Entity& ent); not neded just use validate
	void Draw();

	bool m_scene_manager_opened = false;
private:
	std::list<EntityMenu> m_menus;
	Scene& m_scene;
	int64 m_cur_ind;

};
