#pragma once
#include "Event.h"
#include "EntitySystem/Entity.h"


namespace StepWay
{

	class SceneEvent :public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(ECS_CATEGORY)


			explicit SceneEvent(Scene* scene) :
			m_scene(scene)
		{};

		inline Scene* GetScenePtr() { return m_scene; }
	protected:
		Scene* m_scene;
	};


	class SceneDestroyEvent : public SceneEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::SCENE_DESTROYED)


			explicit SceneDestroyEvent(Scene* scene) :
			SceneEvent(scene)
		{};

		~SceneDestroyEvent() override {};
	private:

	};

	class SceneCreateEvent : public SceneEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::SCENE_CREATED)


			explicit SceneCreateEvent(Scene* scene) :
			SceneEvent(scene)
		{};

		~SceneCreateEvent() override {};
	private:

	};


	class EntityEvent :public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(ECS_CATEGORY)


		explicit EntityEvent(Entity& ent) :
			m_entity(ent)
		{};

		inline Entity& GetEntity() { return m_entity; }
	protected:
		Entity m_entity;
	};


	class EntityDestroyEvent : public EntityEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::ENTITY_DESTROYED)


			explicit EntityDestroyEvent(Entity& ent) :
			EntityEvent(ent)
		{};

		~EntityDestroyEvent() override {};
	private:

	};

	class EntityCreateEvent : public EntityEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::ENTITY_CREATED)


			explicit EntityCreateEvent(Entity& ent) :
			EntityEvent(ent)
		{};

		~EntityCreateEvent() override {};
	private:

	};

}
