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
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<RenderCommand> m_renderCommands;
	std::shared_ptr<DebugGUILayer> m_dbgGUILayer;
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


bool SandboxApp::ImplSetUp()
{
	m_dbgGUILayer = std::make_shared<DebugGUILayer>(GetMainWindow(), GetMainContex());

	DbgTab tab1("int sliders");
	tab1.AddWidgets({
		std::make_shared<DbgSlideri>("int slider",&i1,100,1000),
		std::make_shared<DbgSlider2i>("int2 slider",&(ivec2.x),0,100),
		std::make_shared<DbgSlider3i>("int3 slider",&(ivec3.x),0,100),
		std::make_shared<DbgSlider4i>("int4 slider",&(ivec4.x),0,100)
		});
	m_dbgGUILayer->AddTab(tab1);
	
	DbgTab tab2("float sliders");
	tab2.AddWidgets({
		std::make_shared<DbgSliderf>("float slider",&f1,100.0f,1000.0f),
		std::make_shared<DbgSlider2f>("float2 slider",&(fvec2.x),0.0f,100.0f),
		std::make_shared<DbgSlider3f>("float3 slider",&(fvec3.x),0.0f,100.0f),
		std::make_shared<DbgSlider4f>("float4 slider",&(fvec4.x),0.0f,100.0f)
		});
	m_dbgGUILayer->AddTab(tab2);
	
	DbgTab tab3("checkboxes");
	tab3.AddWidgets({
		std::make_shared<DbgCheckBox>("check box",&m_b)
		});
	m_dbgGUILayer->AddTab(tab3);
	
	DbgTab tab4("Float Inputs");
	tab4.AddWidgets({
		std::make_shared<DbgInputf>("float input",&f1),
		std::make_shared<DbgInput2f>("float2 inpt",&fvec2.x),
		std::make_shared<DbgInput3f>("float3 input",&fvec3.x),
		std::make_shared<DbgInput4f>("float4 input",&fvec4.x)
		});
	m_dbgGUILayer->AddTab(tab4);
	
	DbgTab tabUniform("Uniform");
	tabUniform.AddWidget(std::make_shared<DbgColor4f>("color", &m_color.x));
	m_dbgGUILayer->AddTab(tabUniform);

	PushLayer(m_dbgGUILayer);

	float data[9] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
	m_buffer->SetUp(data, 9 * sizeof(float));
	m_buffer->Bind();
	m_buffer->SetLayout({ ShaderDataType::FLOAT3 });

	m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
	uint16 indices[3] = { 0,1,2 };
	m_IBO->SetUp(indices, 3);
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
	m_renderCommands = std::shared_ptr<RenderCommand>(RenderCommand::Create(GAPI_TYPE::OPENGL));
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
	m_renderCommands->Clear();
	m_shader->SetUniform("u_color", m_color);
	m_renderCommands->DrawIndexed(m_VAO, m_IBO);
}

void SandboxApp::ImplOnNewFrameEnd()
{
}
