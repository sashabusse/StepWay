#pragma once
#include "Core.h"
#include "entt.hpp"
#include "Scene.h"

namespace StepWay
{

	class Entity
	{
	public:
		Entity() :
			m_scene(nullptr),
			m_id(entt::null) {};
		Entity(Scene* sc, entt::entity id) :
			m_scene(sc),
			m_id(id) {};

		Entity(const Entity&) = default;
		Entity(Entity&&) = default;
		
		Entity& operator= (const Entity&) = default;
		Entity& operator= (Entity&&) = default;

		bool IsValid()
		{
			return (m_id != entt::null && m_scene->m_reg.valid(m_id));
		}

		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_reg.has<T>(m_id);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			SW_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
			return m_scene->m_reg.emplace<T>(m_id, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			SW_CORE_ASSERT(HasComponent<T>(), "Entity don't have component");
			m_scene->m_reg.remove<T>(m_id);
		}

		template<typename T>
		T& GetComponent()
		{
			SW_CORE_ASSERT(HasComponent<T>(), "Entity don't have component");
			return m_scene->m_reg.get<T>(m_id);
		}

		void RemoveFrScene();

	private:
	public:
	private:
		Scene* m_scene;
		entt::entity m_id;

	};
}