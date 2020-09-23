#pragma once
#include "Core.h"
#include "entt.hpp"
#include "glm/glm.hpp"
#include "Graphics/API/Mesh.h"
#include "glm/gtc/matrix_transform.hpp"


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

	class NameComponent
	{
	public:
		NameComponent() :
			name("No name") {};
		NameComponent(const std::string& _name) :
			name(_name) {};
		NameComponent(std::string&& _name) :
			name(_name) {};

		NameComponent(const NameComponent&) = default;
		NameComponent(NameComponent&&) = default;

		NameComponent& operator= (const NameComponent&) = default;
		NameComponent& operator= (NameComponent&&) = default;


		std::string name;
	};


	using Graphics::API::Mesh;
	class MeshComponent
	{
	public:
		MeshComponent() :
			mesh(),
			visible(true) {};
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(MeshComponent&&) = default;

		MeshComponent& operator= (const MeshComponent&) = default;
		MeshComponent& operator= (MeshComponent&&) = default;

		//should be move instead of copy
		MeshComponent(const Mesh & _mesh) :
			mesh(_mesh) {};
		MeshComponent(Mesh&& _mesh) :
			mesh(std::move(_mesh)) {};

		bool visible;
		Mesh mesh;
	};


	class CameraComponent
	{
	public:
		CameraComponent():
			m_FOV(60),
			m_near(0.1),
			m_far(100),
			m_AspectRatio(1)
		{};
		CameraComponent(float AspectRatio, float FOV, float n, float f) :
			m_FOV(FOV),
			m_near(n),
			m_far(f),
			m_AspectRatio(AspectRatio)
		{};

		CameraComponent(const CameraComponent&) = default;
		CameraComponent(CameraComponent&&) = default;

		CameraComponent& operator= (const CameraComponent&) = default;
		CameraComponent& operator= (CameraComponent&&) = default;

		void SetAspectRatio(float AspectRatio) { m_AspectRatio = AspectRatio; };
		void SetFOV(float FOV) { m_FOV = FOV; };
		void SetNear(float n) { m_near = n; };
		void SetFar(float f) { m_far = f; };
		glm::mat4 GenerateProjection() { return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_near, m_far); };
	public:
		float m_AspectRatio;
		float m_FOV;
		float m_near, m_far;
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