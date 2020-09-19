#pragma once
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
using StepWay::Graphics::API::Renderer;
using StepWay::Graphics::API::RenderingCommands;
using StepWay::Graphics::API::Texture;
using StepWay::Graphics::API::Mesh;
using StepWay::Scene;
using StepWay::Entity;
using StepWay::TransformComponent;
using StepWay::MeshComponent;
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

};