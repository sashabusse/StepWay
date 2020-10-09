#include "RenderingExample.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

#include "CameraControlScript.h"



RenderingExample::RenderingExample()
{
}

void RenderingExample::OnAttach()
{
	Application::GetInstance().OnEvent(SceneCreateEvent(&m_scene));
	//setting up camera
	m_cam_entity = m_scene.CreateEntity("camera");
	m_cam_entity.AddComponent<CameraComponent>();
	m_cam_entity.AddComponent<NativeScriptComponent>(new CameraControlScript(m_cam_entity));


	//setting up suzzane
	Entity suzzane = m_scene.CreateEntity("suzzane");
	suzzane.AddComponent<MeshComponent>();
	//preparing vertex data---------
	MeshComponent& mesh_c = suzzane.GetComponent<MeshComponent>();
	mesh_c.SetMesh(Load3DModel("Resource\\3d_objects\\RenderingExample\\suzanne.obj")[0]);
	mesh_c.GetMesh().MakeFlatNormals();
	mesh_c.GetMesh().SetUpBuffers();
	//----------------------------------

	//setting up ground plane
	Entity ground_ent = m_scene.CreateEntity("ground plane");
	MeshComponent& ground_mesh_c = ground_ent.AddComponent<MeshComponent>();
	ground_mesh_c.SetMesh(LoadPlaneXZ(glm::vec3(0, -4, 0), glm::vec2(100, 100)));
	ground_mesh_c.GetMesh().SetUpBuffers();

	ground_ent.GetComponent<TransformComponent>().transform = glm::translate(glm::mat4(1.0f), { 0, -4, 0 });

	//Setting Up Main Drawing Shader----
	m_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	m_shader->SetUpFromFile("Resource\\GLShaders\\RenderingExample\\Vertex.hlsl",
		"Resource\\GLShaders\\RenderingExample\\Fragment.hlsl");
	m_shader->SetUniform("u_color", m_color);
	//----------------------------------
	m_renderer.SetShader(m_shader);
}

void RenderingExample::OnDetach()
{
	m_shader->ShutDown();
}

void RenderingExample::OnUpdate()
{
	//rendering stuff
	m_shader->SetUniform("u_color", m_color);
	m_scene.UpdateScene();
	m_scene.RenderScene(m_renderer, m_cam_entity);
}

void RenderingExample::OnEvent(StepWay::Event& e)
{
	if (e.GetEventType() == StepWay::EventType::WINDOW_RESIZE_END)
	{
		StepWay::WindowResizeEndEvent& wre = static_cast<StepWay::WindowResizeEndEvent&>(e);
		m_cam_entity.GetComponent<CameraComponent>().SetAspectRatio(wre.GetAspectRatio());
	}
}

std::string RenderingExample::ToString() const
{
	return std::string("Rendering Example");
}

std::wstring RenderingExample::ToWString() const
{
	return std::wstring(L"Rendering Example");
}
