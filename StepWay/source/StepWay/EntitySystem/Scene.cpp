#include "StepWayPCH.h"
#include "Scene.h"
#include "Entity.h"
#include "BasicComponents.h"




namespace StepWay
{
	Scene::Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		Entity ne(this, m_reg.create());
		ne.AddComponent<TransformComponent>();

		return ne;
	}


	void Scene::RenderScene(Graphics::API::Renderer& renderer)
	{
		renderer.Clear();
		renderer.BeginScene();
		m_reg.view<MeshComponent, TransformComponent>().each(
			[&](entt::entity entity, MeshComponent& mesh_c, TransformComponent& transform_c)
			{
				renderer.DrawIndexed(mesh_c.mesh, transform_c.transform);
			});
	}

	

}
