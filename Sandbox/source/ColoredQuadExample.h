#pragma once


#include "SandboxApp.h"

StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}

std::shared_ptr<VertexBuffer> m_buffer;
std::shared_ptr<IndexBuffer> m_IBO;
std::shared_ptr<VertexArray> m_VAO;
std::shared_ptr<Shader> m_shader;
std::shared_ptr<RenderCommand> m_renderCommands;
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

	//preparing vertex data---------
	float data[12] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
	m_buffer->SetUp(data, sizeof(data));
	m_buffer->Bind();
	m_buffer->SetLayout({ ShaderDataType::FLOAT3 });

	//indexes
	m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
	uint16 indices[6] = { 0,1,2, 2,3,0 };
	m_IBO->SetUp(indices, 6);
	m_IBO->Bind();

	m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));
	m_VAO->SetUp();
	m_VAO->Bind();
	m_VAO->SetVertexBuffer(m_buffer);
	//----------------------------------

	//Setting Up Main Drawing Shader----
	m_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	m_shader->SetUpFromFile("Resource\\GLShaders\\ColoredQuadExample\\Vertex.hlsl",
		"Resource\\GLShaders\\ColoredQuadExample\\Fragment.hlsl");
	m_shader->SetUniform("u_color", m_color);
	//----------------------------------

	//------Creating Render Command-----
	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));
	//----------------------------------

	return true;
}

void SandboxApp::ImplShutDown()
{
	m_shader->ShutDown();
	m_VAO->ShutDown();
	m_IBO->ShutDown();
	m_buffer->ShutDown();

}

void SandboxApp::ImplOnNewFrameStart()
{
	//rendering stuff
	m_shader->SetUniform("u_color", m_color);
	m_shader->Bind();
	m_renderCommands->Clear();
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}

