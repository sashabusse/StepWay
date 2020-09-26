#include "StepWayPCH.h"
#include "Entity.h"


namespace StepWay
{
	LocalUIDGenerator Entity::s_uid_gen;

	Entity::Entity() :
		m_uid(0),
		m_scene(nullptr),
		m_id(entt::null) {}

	Entity::Entity(Scene* sc, entt::entity id):
		m_uid(s_uid_gen.NextID()),
		m_scene(sc),
		m_id(id) {};


	Entity::Entity(const Entity& other):
		m_uid(other.m_uid),
		m_scene(other.m_scene),
		m_id(other.m_id) {};

	Entity& Entity::operator=(const Entity& other)
	{
		m_uid = other.m_uid;
		m_scene = other.m_scene;
		m_id = other.m_id;

		return *this;
	}

	Entity::Entity(Entity&& other):
		m_uid(other.m_uid),
		m_scene(other.m_scene),
		m_id(other.m_id) 
	{
		other.m_id = entt::null;
		other.m_scene = nullptr;
		other.m_uid = 0;
	};

	Entity& Entity::operator=(Entity&& other)
	{
		m_uid = other.m_uid;
		m_scene = other.m_scene;
		m_id = other.m_id;
		
		other.m_id = entt::null;
		other.m_scene = nullptr;
		other.m_uid = 0;

		return *this;
	}

	
	void Entity::RemoveFrScene()
	{
		SW_CORE_ASSERT(IsValid(), "invalid entity on remove");
		m_scene->m_reg.destroy(m_id);
	}
}

