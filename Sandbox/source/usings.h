#pragma once

#include "StepWay.h"

//Core
using StepWay::Application;
using StepWay::Layer;

//Graphics
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
using StepWay::Graphics::API::Vertex;

//Entity Component System
using StepWay::Scene;
using StepWay::Entity;
using StepWay::NameComponent;
using StepWay::TransformComponent;
using StepWay::MeshComponent;
using StepWay::CameraComponent;
using StepWay::NativeScriptComponent;
using StepWay::NativeScript;

//Input System
using StepWay::Input::Mouse;
using StepWay::Input::MouseKey;
using StepWay::Input::Keyboard;
using StepWay::Input::KeyboardKey;

using StepWay::ResourceLoaders::Load3DModel;


using StepWay::Event;
using StepWay::EventType;
using StepWay::EntityCreateEvent;
using StepWay::SceneCreateEvent;

//DBG should be deleted
using StepWay::DebugGUILayer;
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


