#pragma once


#include "SandboxApp.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <algorithm>

StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}


Scene m_scene;
Entity m_entity;
Entity m_cam_entity;
TransformComponent* m_transform_c;
Renderer m_renderer;

std::shared_ptr<Shader> m_shader;
std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

glm::vec4 m_color{ 1,1,1,1 };
glm::vec3 m_scale{ 0.1,0.1,0.1 };
glm::vec3 m_translation{ 0,0,-0.5 };
glm::vec3 m_rotation{ 0,0,0 };


class CameraControlScript : public NativeScript
{
public:
	CameraControlScript(Entity& ent) :
		NativeScript(ent),
		keyboard(SandboxApp::GetInstance()->GetMainWindow()->GetKeyboard()),
		mouse(SandboxApp::GetInstance()->GetMainWindow()->GetMouse()),
		pos({0,0,0}),
		angle({0,0})
	{};
	virtual void OnCreate() override
	{
	}
	virtual void OnUpdate() override
	{
		glm::vec2 offset({ 0,0 });
		if (keyboard.IsKeyPressed(StepWay::Input::KeyboardKey::KEY_W))
		{
			offset.x += 1.0 / 1000.0;
		}
		if (keyboard.IsKeyPressed(StepWay::Input::KeyboardKey::KEY_S))
		{
			offset.x -= 1.0 / 1000.0;
		}
		if (keyboard.IsKeyPressed(StepWay::Input::KeyboardKey::KEY_A))
		{
			offset.y -= 1.0 / 1000.0;
		}
		if (keyboard.IsKeyPressed(StepWay::Input::KeyboardKey::KEY_D))
		{
			offset.y += 1.0 / 1000.0;
		}


		
		glm::vec2 mouse_cur({ mouse.GetX(), mouse.GetY() });
		glm::vec2 rot({ 0,0 });
		if (mp)
		{
			rot = mouse_cur - mouse_prev;
			rot.x /= -100;
			rot.y /= 100;
		}
		angle += rot;
		if (angle.x < 0) angle.x += 360;
		if (angle.x >= 360) angle.x -= 360;

		angle.y = std::max(-180.0f, std::min(180.0f, angle.y));
		
		mp = true;
		mouse_prev = mouse_cur;
		
		glm::mat4 rot_mat = glm::eulerAngleYXZ(-angle.x, -angle.y, 0.0f);

		glm::vec3 forward = glm::normalize(glm::vec3(rot_mat * glm::vec4({ 0,0,-1,0 })));
		glm::vec3 right = glm::normalize(glm::vec3(rot_mat * glm::vec4({ 1,0,0,0 })));

		pos += forward * offset.x + right * offset.y;

		glm::mat4& tr = GetComponent<TransformComponent>().transform;
		
		if(mouse.IsButtonDown(StepWay::Input::MouseKey::L_BUTTON))
			tr = glm::translate(pos) * glm::eulerAngleYXZ(-angle.x, -angle.y, 0.0f);
	}
private:
	glm::vec3 pos;
	glm::vec2 angle;
	glm::vec2 mouse_prev;
	bool mp = false;
	KeyboardClientInterface keyboard;
	MouseClientInterface mouse;
};

bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab color_tab("Color Uniform");
	//color uniform in drawing shader
	color_tab.AddWidget(std::make_shared<DbgColor4f>("color", &m_color.x));

	DbgTab transform_tab("transform");
	
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("translation", &m_translation.x, -1.0, 1.0));
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("scale", &m_scale.x, 0.0, 1.0));
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("rotate", &m_rotation.x, -180.0, 180.0));

	m_dbgGUILayer->AddTab(transform_tab);
	m_dbgGUILayer->AddTab(color_tab);

	PushLayer(m_dbgGUILayer);
	//------------------------------
	m_cam_entity = m_scene.CreateEntity();
	m_cam_entity.AddComponent<CameraComponent>(glm::perspective(45.0f, (GLfloat)1920 / (GLfloat)1080, 0.1f, 150.0f));
	m_cam_entity.AddComponent<NativeScriptComponent>(new CameraControlScript(m_cam_entity));


	m_entity = m_scene.CreateEntity();
	m_entity.AddComponent<MeshComponent>();
	MeshComponent& mesh_c = m_entity.GetComponent<MeshComponent>();
	m_transform_c = &(m_entity.GetComponent<TransformComponent>());

	//preparing vertex data---------
	std::vector<Mesh> meshes = Load3DModel("Resource\\3d_objects\\RenderingExample\\suzanne.obj");
	mesh_c.mesh = meshes[0];
	mesh_c.mesh.make_flat_normals();
	mesh_c.mesh.SetUpBuffers();
	//----------------------------------

	//Setting Up Main Drawing Shader----
	m_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	m_shader->SetUpFromFile("Resource\\GLShaders\\RenderingExample\\Vertex.hlsl",
		"Resource\\GLShaders\\RenderingExample\\Fragment.hlsl");
	m_shader->SetUniform("u_color", m_color);
	//----------------------------------
	m_renderer.SetShader(m_shader);

	return true;
}

void SandboxApp::ImplShutDown()
{
	m_shader->ShutDown();
	m_entity.RemoveFrScene();
}

void SandboxApp::ImplOnNewFrameStart()
{
	//rendering stuff
	glm::mat4 translation_mat = glm::translate(m_translation);
	glm::mat4 scale_mat = glm::scale(m_scale);
	glm::mat4 rotation_mat = glm::eulerAngleXYZ(m_rotation.x * 3.14 / 180, m_rotation.y * 3.14 / 180, m_rotation.z * 3.14 / 180);
	m_transform_c->transform = translation_mat * rotation_mat * scale_mat;

	m_shader->SetUniform("u_color", m_color);
	m_scene.UpdateScene();
	m_scene.RenderScene(m_renderer, m_cam_entity);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}

