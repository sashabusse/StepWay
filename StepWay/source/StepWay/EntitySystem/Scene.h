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
		Entity CreateEntity(const std::string& name);
		
		template<typename Args>
		inline void ForEach(std::function<void(Entity&, Args&)> func)
		{
			m_reg.view<Args>().each(
				[&](entt::entity entity, Args& args)
				{
					func(Entity(this, entity), args);
				}
			);
		}

		void UpdateScene();
		void RenderScene(Graphics::API::Renderer& renderer, Entity& cam_entt);


	private:
	public:
	private:
		entt::registry m_reg;
		friend Entity;
	};


}