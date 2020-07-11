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

std::shared_ptr<Texture> texture_buffer;
std::shared_ptr<Shader> compute_shader;
float compute_shader_mul = 0.0f;


//-----------------------compute shader limits check---------------
#include "Platform/OpenGL/ErrorHandling.h"
void go_trace_compute_shader_limits()
{
	int work_grp_cnt[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
	GL_CHECK_ERRORS();

	SW_TRACE("max work group count[0] = {}", work_grp_cnt[0]);
	SW_TRACE("max work group count[1] = {}", work_grp_cnt[1]);
	SW_TRACE("max work group count[2] = {}", work_grp_cnt[2]);

	int work_grp_size[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
	GL_CHECK_ERRORS();

	SW_TRACE("max work group size[0] = {}", work_grp_size[0]);
	SW_TRACE("max work group size[1] = {}", work_grp_size[1]);
	SW_TRACE("max work group size[2] = {}", work_grp_size[2]);
}
//---------------------------------------------------------------------



bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab tabUniform("Uniform");

	//multiplier in compute shader
	tabUniform.AddWidget(std::make_shared<DbgSliderf>("mul", &compute_shader_mul, 0.0, 5.0));

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
	m_shader->SetUpFromFile("Resource\\GLShaders\\SimpleComputeShaderExample\\DrawingVertex.hlsl",
		"Resource\\GLShaders\\SimpleComputeShaderExample\\DrawingFragment.hlsl");
	//----------------------------------

	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));


	//trace_limits---------
	go_trace_compute_shader_limits();

	//buffer for computed data
	texture_buffer = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
	texture_buffer->SetUp(512, 512, Texture::PixelFormat::RGBA32_F);
	texture_buffer->SetToImgUnit(0);
	texture_buffer->SetToTexUnit(1);

	compute_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	compute_shader->SetUpAsComputeShader("Resource\\GLShaders\\SimpleComputeShaderExample\\Compute.hlsl");
	//----------------------------------

	return true;
}

void SandboxApp::ImplShutDown()
{
	m_shader->ShutDown();
	m_VAO->ShutDown();
	m_IBO->ShutDown();
	m_buffer->ShutDown();
	compute_shader->ShutDown();
	texture_buffer->ShutDown();
}

void SandboxApp::ImplOnNewFrameStart()
{
	//------compute shader tests-----

	compute_shader->SetUniform("multiplier", compute_shader_mul);
	compute_shader->Bind();
	glDispatchCompute((GLuint)512, (GLuint)512, 1);
	GL_CHECK_ERRORS();

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	GL_CHECK_ERRORS();

	//------compute shader tests-----

	//rendering stuff
	m_shader->SetUniform("ourTexture", 1);
	m_shader->Bind();
	m_renderCommands->Clear();
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}
