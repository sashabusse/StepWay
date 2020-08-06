#pragma once


#include "SandboxApp.h"

StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}

#include "Platform/OpenGL/ErrorHandling.h"


std::shared_ptr<VertexBuffer> m_buffer;
std::shared_ptr<IndexBuffer> m_IBO;
std::shared_ptr<VertexArray> m_VAO;
std::shared_ptr<Shader> m_shader;
std::shared_ptr<RenderCommand> m_renderCommands;
std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

std::shared_ptr<Texture> texture_buffer[2];
std::shared_ptr<Shader> compute_shader;

int cur_buf = -1;
int prev_buf = -1;


float intencity = 1.0f;
float dt = 0.0005f;
float h = 0.0005f;
float a = 1e-2;

int m_spd_mul = 0;



float* arr = nullptr;
float* starting_condition()
{
	if (arr != nullptr) return arr;

	int n = 512;
	float* arr = new float[n * n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i * n + j] = j / 512.0 * 100;
		}
	}
	return arr;
}



bool SandboxApp::ImplSetUp()
{
	//Setting Up Dbg Gui------------
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab tabUniform("Uniforms");

	//multiplier in compute shader
	tabUniform.AddWidget(std::make_shared<DbgSliderf>("intencity", &intencity, 0.0, 5.0));
	tabUniform.AddWidget(std::make_shared<DbgSliderf>("dt", &dt, 0.0, 0.002, "%.4f"));
	tabUniform.AddWidget(std::make_shared<DbgSliderf>("h", &h, 0.0, 0.002, "%.4f"));
	tabUniform.AddWidget(std::make_shared<DbgSliderf>("a", &a, 0.0, 4e-2, "%.4f"));
	tabUniform.AddWidget(std::make_shared<DbgSlideri>("spd_mul", &m_spd_mul, 0, 30));
	
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
	m_shader->SetUpFromFile("Resource\\GLShaders\\HeatEquationSolvation\\SingleAxis\\DrawingVertex.hlsl",
		"Resource\\GLShaders\\HeatEquationSolvation\\SingleAxis\\DrawingFragment.hlsl");
	//----------------------------------

	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));

	//buffer for computed data----------------
	for (int i = 0; i < 2; i++)
	{
		texture_buffer[i] = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
		texture_buffer[i]->SetUp(512, 512, Texture::PixelFormat::R32_F, NULL);
		texture_buffer[i]->SetToTexUnit(i + 1);
		texture_buffer[i]->SetToImgUnit(i + 1);
	}
	texture_buffer[0]->LoadData(512, 512, Texture::PixelFormat::R32_F, starting_condition());
	texture_buffer[1]->LoadData(512, 512, Texture::PixelFormat::R32_F, starting_condition());

	compute_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	compute_shader->SetUpAsComputeShader("Resource\\GLShaders\\HeatEquationSolvation\\SingleAxis\\Compute.hlsl");

	compute_shader->SetUniform("intencity", intencity);
	compute_shader->SetUniform("dt", dt);
	compute_shader->SetUniform("h", h);
	compute_shader->SetUniform("a", a);

	cur_buf = 2;
	prev_buf = 1;

	compute_shader->SetUniform("img_input", prev_buf);
	compute_shader->SetUniform("img_output", cur_buf);
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
	texture_buffer[0]->ShutDown();
	texture_buffer[1]->ShutDown();
}

void SandboxApp::ImplOnNewFrameStart()
{
	//------compute shader tests-----
	
	compute_shader->SetUniform("intencity", intencity);
	compute_shader->SetUniform("dt", dt);
	compute_shader->SetUniform("h", h);
	compute_shader->SetUniform("a", a);

	for (int i = 0; i < m_spd_mul; i++)
	{
		compute_shader->SetUniform("img_input", prev_buf);
		compute_shader->SetUniform("img_output", cur_buf);

		compute_shader->Bind();
		glDispatchCompute((GLuint)512, (GLuint)512, 1);
		GL_CHECK_ERRORS();

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		GL_CHECK_ERRORS();

		if(i!=m_spd_mul-1)
			std::swap(cur_buf, prev_buf);
	}
	
	//------compute shader tests-----

	//rendering stuff
	m_shader->SetUniform("ourTexture", cur_buf);
	m_shader->Bind();
	m_renderCommands->Clear();
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);

	std::swap(cur_buf, prev_buf);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}
