#pragma once
#include "Graphics/API/Mesh.h"

namespace StepWay
{
	namespace ResourceLoaders
	{
		std::vector<std::shared_ptr<Graphics::API::Mesh>> Load3DModel(const std::string& filename);

		//Primitives
		std::shared_ptr<Graphics::API::Mesh> LoadCube(const glm::vec3& pos, const glm::vec3& size);
		std::shared_ptr<Graphics::API::Mesh> LoadPlaneXY(const glm::vec3& pos, const glm::vec2& size);
		std::shared_ptr<Graphics::API::Mesh> LoadPlaneXZ(const glm::vec3& pos, const glm::vec2& size);
		std::shared_ptr<Graphics::API::Mesh> LoadPlaneYZ(const glm::vec3& pos, const glm::vec2& size);
		
	}
}