#pragma once


#include "SandboxApp.h"

StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}


Scene m_scene;
Entity m_entity;
Renderer m_renderer;

std::shared_ptr<Shader> m_shader;
std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

glm::vec4 m_color{ 1,1,1,1 };


bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab tabUniform("Color Uniform");
	//color uniform in drawing shader
	tabUniform.AddWidget(std::make_shared<DbgColor4f>("color", &m_color.x));

	m_dbgGUILayer->AddTab(tabUniform);

	PushLayer(m_dbgGUILayer);
	//------------------------------

	m_entity = m_scene.CreateEntity();
	m_entity.AddComponent<MeshComponent>();
	MeshComponent& mesh_c = m_entity.GetComponent<MeshComponent>();
	
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
	m_shader->SetUpFromFile("Resource\\GLShaders\\ColoredQuadExample\\Vertex.hlsl",
		"Resource\\GLShaders\\ColoredQuadExample\\Fragment.hlsl");
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
	m_shader->SetUniform("u_color", m_color);
	m_scene.RenderScene(m_renderer);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}

