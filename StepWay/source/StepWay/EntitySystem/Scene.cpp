#include "StepWayPCH.h"
#include "Application.h"
#include "Scene.h"
#include "Entity.h"
#include "BasicComponents.h"
#include "Events/ECSEvents.h"




namespace StepWay
{
	Scene::Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		Entity ne(this, m_reg.create());
		ne.AddComponent<TransformComponent>();
		Application::GetInstance().OnEvent(EntityCreateEvent(ne));
		return ne;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity ne(this, m_reg.create());
		ne.AddComponent<TransformComponent>();
		ne.AddComponent<NameComponent>(name);
		Application::GetInstance().OnEvent(EntityCreateEvent(ne));
		return ne;
	}


	void Scene::UpdateScene()
	{
		m_reg.view<NativeScriptComponent>().each(
			[&](entt::entity entity, NativeScriptComponent& script_c)
			{
				script_c.OnUpdate();
			});
	}

	void Scene::RenderScene(Graphics::API::Renderer& renderer, Entity& cam_entt)
	{
		//replace with default cam
		SW_CORE_ASSERT(cam_entt.IsValid() && cam_entt.HasComponent<CameraComponent>(), "not valid entity as cam");

		renderer.Clear();

		CameraComponent& cam_c = cam_entt.GetComponent<CameraComponent>();
		TransformComponent& transform_c = cam_entt.GetComponent<TransformComponent>();

		renderer.BeginScene(cam_c.GenerateProjection(), transform_c.transform);
		m_reg.view<MeshComponent, TransformComponent>().each(
			[&](entt::entity entity, MeshComponent& mesh_c, TransformComponent& transform_c)
			{
				if(mesh_c.visible)
					renderer.DrawIndexed(mesh_c.mesh, transform_c.transform);
			});
	}

	

}
