#pragma once
#include "Graphics/API/RenderingCommands.h"
#include "entt.hpp"

namespace StepWay
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		Entity CreateEntity();

		void RenderScene(Graphics::API::Renderer& renderer);

	private:
	public:
	private:
		entt::registry m_reg;

		friend Entity;
	};

}