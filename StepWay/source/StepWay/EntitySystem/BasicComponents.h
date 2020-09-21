#pragma once
#include "Core.h"
#include "entt.hpp"
#include "glm/glm.hpp"
#include "Graphics/API/Mesh.h"


namespace StepWay
{
	class TransformComponent
	{
	public:
		TransformComponent() :
			transform(glm::mat4(1.0f)) {};
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(TransformComponent&&) = default;
		
		TransformComponent& operator= (const TransformComponent&) = default;
		TransformComponent& operator= (TransformComponent&&) = default;

		TransformComponent(const glm::mat4& _transform) :
			transform(_transform) {};

		glm::mat4 transform = glm::mat4(1.0f);
	};


	using Graphics::API::Mesh;
	class MeshComponent
	{
	public:
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(MeshComponent&&) = default;

		MeshComponent& operator= (const MeshComponent&) = default;
		MeshComponent& operator= (MeshComponent&&) = default;

		//should be move instead of copy
		MeshComponent(const Mesh & _mesh) :
			mesh(_mesh) {};
		MeshComponent(Mesh&& _mesh) :
			mesh(std::move(_mesh)) {};

		Mesh mesh;
	};


	class CameraComponent
	{
	public:
		CameraComponent() :
			projection(glm::mat4(1.0f)) {};

		CameraComponent(const CameraComponent&) = default;
		CameraComponent(CameraComponent&&) = default;

		CameraComponent& operator= (const CameraComponent&) = default;
		CameraComponent& operator= (CameraComponent&&) = default;


		CameraComponent(const glm::mat4& _proj) :
			projection(_proj) {};

		CameraComponent(glm::mat4&& _proj) :
			projection(std::move(_proj)) {};

		glm::mat4 projection;
	};

	class NativeScript
	{
	public:
		NativeScript(Entity& parent) :
			m_entity(parent) {};

		virtual ~NativeScript() {};

		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
	protected:
		template<typename T>
		T& GetComponent()
		{
			return m_entity.GetComponent<T>();
		}
	private:
		Entity m_entity;
	};

	class NativeScriptComponent
	{
	public:
		NativeScriptComponent(NativeScript* script) :
			m_instance(script) 
		{
			m_instance->OnCreate();
		};

		NativeScriptComponent(const NativeScriptComponent&) = default;
		NativeScriptComponent(NativeScriptComponent&&) = default;

		NativeScriptComponent& operator= (const NativeScriptComponent&) = default;
		NativeScriptComponent& operator= (NativeScriptComponent&&) = default;

		void OnUpdate() { m_instance->OnUpdate(); };
		
	private:
		std::unique_ptr<NativeScript> m_instance;
	};

}