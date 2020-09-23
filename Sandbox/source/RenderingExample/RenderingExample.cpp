#include "RenderingExample.h"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include <memory>





class CameraControlScript : public NativeScript
{
public:
	CameraControlScript(Entity& ent) :
		NativeScript(ent),
		pos({ 0,0,0.37f }),
		angle({ 0,0 })
	{};
	virtual void OnCreate() override
	{
		//Mouse::SetCursorMode(StepWay::Input::CursorMode::CAMERA);
	}
	virtual void OnUpdate() override
	{
		glm::vec2 offset({ 0,0 });
		if (Keyboard::IsKeyPressed(KeyboardKey::KEY_W))
		{
			offset.x += 1.0 / 1000.0;
		}
		if (Keyboard::IsKeyPressed(KeyboardKey::KEY_S))
		{
			offset.x -= 1.0 / 1000.0;
		}
		if (Keyboard::IsKeyPressed(KeyboardKey::KEY_A))
		{
			offset.y -= 1.0 / 1000.0;
		}
		if (Keyboard::IsKeyPressed(KeyboardKey::KEY_D))
		{
			offset.y += 1.0 / 1000.0;
		}

		glm::vec2 mouse_delt({ 0,0 });

		if (Mouse::IsButtonDown(MouseKey::L_BUTTON))
			mouse_delt = glm::vec2({ Mouse::GetDX(), Mouse::GetDY() });
		glm::vec2 rot;
		rot.x = -mouse_delt.x/200;
		rot.y = -mouse_delt.y/200;

		glm::mat4 old_rod_mat = glm::rotate(angle.x, glm::vec3({ 0,1,0 })) * glm::rotate(angle.y, glm::vec3({ 1,0,0 }));

		glm::vec3 forward = glm::normalize(glm::vec3(old_rod_mat * glm::vec4({ 0,0,-1,0 })));
		glm::vec3 right = glm::normalize(glm::vec3(old_rod_mat * glm::vec4({ 1,0,0,0 })));

		pos += forward * offset.x + right * offset.y;
		
		angle += rot;
		if (angle.x < 0) 
			angle.x += 2*glm::pi<float>();
		if (angle.x >= 2 * glm::pi<float>())
			angle.x -= 2 * glm::pi<float>();
		
		angle.y = glm::clamp<float>(angle.y, -glm::pi<float>() / 2, glm::pi<float>() / 2);

		glm::mat4 new_rot_mat = glm::rotate(angle.x, glm::vec3({ 0,1,0 })) * glm::rotate(angle.y, glm::vec3({ 1,0,0 }));
		glm::mat4 new_transl_mat = glm::translate(pos);

		

		glm::mat4& tr = GetComponent<TransformComponent>().transform;
		tr = new_transl_mat * new_rot_mat;
	}
private:
	glm::vec3 pos;
	glm::vec2 angle;
};



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
	m_suzzane = m_scene.CreateEntity("suzzane");
	m_suzzane.AddComponent<MeshComponent>();
	MeshComponent& mesh_c = m_suzzane.GetComponent<MeshComponent>();
	glm::mat4& suz_transform = m_suzzane.GetComponent<TransformComponent>().transform;
	suz_transform = glm::mat4(0.1f);
	suz_transform[3][3] = 1.0f;
	suz_transform[3][2] = -0.2f;
	//preparing vertex data---------
	std::vector<Mesh> meshes = Load3DModel("Resource\\3d_objects\\RenderingExample\\suzanne.obj");
	mesh_c.mesh = meshes[0];
	mesh_c.mesh.make_flat_normals();
	mesh_c.mesh.SetUpBuffers();
	//----------------------------------

	//setting up ground plane
	m_ground_ent = m_scene.CreateEntity("ground plane");
	Mesh& ground_mesh = m_ground_ent.AddComponent<MeshComponent>().mesh;
	ground_mesh.m_vertices = {
		Vertex({ -1,0,-1 }, { 0,1,0 }),
		Vertex({  1,0,-1 }, { 0,1,0 }),
		Vertex({  1,0, 1 }, { 0,1,0 }),
		Vertex({ -1,0,1 }, { 0,1,0 })
	};
	ground_mesh.m_indices = { 0, 1, 2, 2, 3, 0 };
	ground_mesh.SetUpBuffers();

	glm::mat4& ground_transform = m_ground_ent.GetComponent<TransformComponent>().transform;
	ground_transform = glm::translate(glm::mat4(1.0f), {0, -0.3, 0});

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
	m_suzzane.RemoveFrScene();
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
