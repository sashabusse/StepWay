#pragma once


#include "SandboxApp.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"

StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}


Scene m_scene;
Entity m_entity;
TransformComponent* m_transform_c;
Renderer m_renderer;

std::shared_ptr<Shader> m_shader;
std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

glm::vec4 m_color{ 1,1,1,1 };
glm::vec3 m_scale{ 1,1,1 };
glm::vec3 m_translation{ 0,0,0 };
glm::vec3 m_rotation{ 0,0,0 };


bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab color_tab("Color Uniform");
	//color uniform in drawing shader
	color_tab.AddWidget(std::make_shared<DbgColor4f>("color", &m_color.x));

	DbgTab transform_tab("transform");
	
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("translation", &m_translation.x, -1.0, 1.0));
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("scale", &m_scale.x, 0.0, 2.0));
	transform_tab.AddWidget(std::make_shared<DbgSlider3f>("rotate", &m_rotation.x, -180.0, 180.0));

	m_dbgGUILayer->AddTab(transform_tab);
	m_dbgGUILayer->AddTab(color_tab);

	PushLayer(m_dbgGUILayer);
	//------------------------------


	m_entity = m_scene.CreateEntity();
	m_entity.AddComponent<MeshComponent>();
	MeshComponent& mesh_c = m_entity.GetComponent<MeshComponent>();
	m_transform_c = &(m_entity.GetComponent<TransformComponent>());

	//preparing vertex data---------
	mesh_c.mesh.m_vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	mesh_c.mesh.m_indices = {
		0,1,2, 2,3,0
	};
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
	m_scene.RenderScene(m_renderer);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}

