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
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		//TransformComponent(TransformComponent&&) = default;
		//TransformComponent& TransformComponent::operator= (TransformComponent&&) = default;
		

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
		//MeshComponent(MeshComponent&&) = default;
		//MeshComponent& MeshComponent::operator= (MeshComponent&&) = default;

		//should be move instead of copy
		MeshComponent(const Mesh & _mesh) :
			mesh(_mesh) {};

		Mesh mesh;
	};

}