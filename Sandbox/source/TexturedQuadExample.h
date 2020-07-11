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
std::shared_ptr<Texture> m_Texture;
std::shared_ptr<Shader> m_shader;
std::shared_ptr<RenderCommand> m_renderCommands;
std::shared_ptr<DebugGUILayer> m_dbgGUILayer;


bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());
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
	m_shader->SetUpFromFile("Resource\\GLShaders\\TextureQuadExample\\Vertex.hlsl",
		"Resource\\GLShaders\\TextureQuadExample\\Fragment.hlsl");
	//----------------------------------

	//------Creating Render Command-----
	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));
	//----------------------------------

	//---Creating and setting up texture----
	m_Texture = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
	m_Texture->SetUp("Resource\\Images\\container.jpg");
	m_Texture->SetToTexUnit(1);
	m_shader->SetUniform("ourTexture", 1);
	//--------------------------------------

	return true;
}

void SandboxApp::ImplShutDown()
{
	m_shader->ShutDown();
	m_VAO->ShutDown();
	m_IBO->ShutDown();
	m_buffer->ShutDown();
	m_Texture->ShutDown();
	
}

void SandboxApp::ImplOnNewFrameStart()
{
	//rendering stuff
	m_shader->SetUniform("ourTexture", 1);
	m_shader->Bind();
	m_renderCommands->Clear();
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}

