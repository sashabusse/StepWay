#pragma once
#include "Graphics/API/Mesh.h"

namespace StepWay
{
	namespace ResourceLoaders
	{
		std::vector<Graphics::API::Mesh> Load3DModel(const std::string& filename);
	}
}