#include "StepWay.h"
//shouldnt be here but it is
#include "glad/glad.h"
#include <iostream>
#include <filesystem>


using StepWay::Graphics::API::GAPI_TYPE;
using StepWay::Graphics::API::GraphicsContext;
using StepWay::Graphics::API::VertexBuffer;
using StepWay::Graphics::API::IndexBuffer;
using StepWay::Graphics::API::VertexArray;
using StepWay::Graphics::API::ShaderDataType;
using StepWay::Graphics::API::Shader;
using StepWay::Graphics::API::RenderCommand;
using StepWay::Graphics::API::Texture;
using StepWay::DbgTab;
using StepWay::DbgWidget;
using StepWay::DbgSliderf;
using StepWay::DbgSlider2f;
using StepWay::DbgSlider3f;
using StepWay::DbgSlider4f;
using StepWay::DbgSlideri;
using StepWay::DbgSlider2i;
using StepWay::DbgSlider3i;
using StepWay::DbgSlider4i;
using StepWay::DbgInputf;
using StepWay::DbgInput2f;
using StepWay::DbgInput3f;
using StepWay::DbgInput4f;
using StepWay::DbgCheckBox;
using StepWay::DbgColor4f;



using StepWay::Layer;
using StepWay::DebugGUILayer;


class SandboxApp :public StepWay::Application
{
public:
	SandboxApp() {};

	bool ImplSetUp() override;
	void ImplShutDown() override;
	void ImplOnNewFrameStart() override;
	void ImplOnNewFrameEnd() override;
	StepWay::Layer* layer;

private:
	std::shared_ptr<VertexBuffer> m_buffer;
	std::shared_ptr<IndexBuffer> m_IBO;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<Texture> m_Texture;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<RenderCommand> m_renderCommands;
	std::shared_ptr<DebugGUILayer> m_dbgGUILayer;

	//was used for test of interface
	float f1 = 0.0;
	int i1 = 100;
	glm::ivec2 ivec2{0,0};
	glm::ivec3 ivec3{ 0,0,0 };
	glm::ivec4 ivec4{ 0,0,0,0 };
	glm::vec2 fvec2{ 0.0,0.0 };
	glm::vec3 fvec3{ 0.0,0.0,0.0 };
	glm::vec4 fvec4{ 0.0,0.0,0.0,0.0 };

	bool m_b;


	glm::vec4 m_color{ 1,1,1,1 };

};


StepWay::Application* StepWay::CreateApplication()
{
	SW_TRACE("Creating Application");
	SandboxApp* sandboxApp = SW_NEW SandboxApp;

	return sandboxApp;
}

//-----------------------compute shader---------------
#include "Platform/OpenGL/ErrorHandling.h"
void go_compute_shader()
{
	int work_grp_cnt[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

	SW_TRACE("max work group count[0] = {}", work_grp_cnt[0]);
	SW_TRACE("max work group count[1] = {}", work_grp_cnt[1]);
	SW_TRACE("max work group count[2] = {}", work_grp_cnt[2]);

	int work_grp_size[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

	SW_TRACE("max work group size[0] = {}", work_grp_size[0]);
	SW_TRACE("max work group size[1] = {}", work_grp_size[1]);
	SW_TRACE("max work group size[2] = {}", work_grp_size[2]);
	
	std::shared_ptr<Texture> tex = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
	tex->SetUp(512, 512);

	std::string compute_shader_string = std::string(
"#version 430\n\
layout(local_size_x = 1, local_size_y = 1) in;\n\
layout(rgba32f, binding = 0) uniform image2D img_output;\n\
\n\
void main() {\n\
vec4 pixel = vec4(0.0, 1.0, 1.0, 1.0);\n\
ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);\n\
pixel.r = pixel_coords.x*1.0/512.0;\n\
imageStore(img_output, pixel_coords, pixel);\n\
}"
);
	const char* string_p = compute_shader_string.c_str();
	GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
	
	glShaderSource(compute_shader, 1, &string_p, NULL);
	glCompileShader(compute_shader);

	GLint result;
	glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(compute_shader, GL_INFO_LOG_LENGTH, &length);
		char* error = new char[length + 1];
		glGetShaderInfoLog(compute_shader, length, &length, &error[0]);
		glDeleteShader(compute_shader);
		SW_CORE_ASSERT(false, error);
	}
	GL_CHECK_ERRORS();
	// check for compilation errors as per normal here

	GLuint compute_program = glCreateProgram();
	glAttachShader(compute_program, compute_shader);
	glLinkProgram(compute_program);
	GL_CHECK_ERRORS();

	glUseProgram(compute_program);
	glDispatchCompute((GLuint)512, (GLuint)512, 1);
	GL_CHECK_ERRORS();

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	GL_CHECK_ERRORS();
}
//-----------------------compute shader---------------



bool SandboxApp::ImplSetUp()
{
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab tabUniform("Uniform");
	tabUniform.AddWidget(std::make_shared<DbgColor4f>("color", &m_color.x));
	m_dbgGUILayer->AddTab(tabUniform);

	PushLayer(m_dbgGUILayer);

	//------compute shader tests-----

	go_compute_shader();

	//------compute shader tests-----

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

	m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
	uint16 indices[6] = { 0,1,2, 2,3,0 };
	m_IBO->SetUp(indices, 6);
	m_IBO->Bind();

	m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));
	m_VAO->SetUp();
	m_VAO->Bind();
	m_VAO->SetVertexBuffer(m_buffer);

	m_shader = std::shared_ptr<Shader>(Shader::Create(GAPI_TYPE::OPENGL));
	m_shader->SetUpFromFile("Resource\\GLShaders\\SimpleVertexShader.hlsl",
		"Resource\\GLShaders\\SimpleFragmentShader.hlsl");
	m_shader->Bind();
	m_shader->SetUniform("u_color", m_color);

	m_Texture = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
	m_Texture->SetUp("Resource\\Images\\container.jpg");
	m_Texture->SetToUnit(1);
	m_shader->SetUniform("ourTexture", 1);

	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));

	

	return true;
}

void SandboxApp::ImplShutDown()
{
	m_shader->ShutDown();
	m_Texture->ShutDown();
	m_VAO->ShutDown();
	m_IBO->ShutDown();
	m_buffer->ShutDown();
}

void SandboxApp::ImplOnNewFrameStart()
{
	m_renderCommands->Clear();
	m_shader->SetUniform("u_color", m_color);
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}
