#pragma once
#include "Core.h"
#include "Memory/MemoryManager.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "Events/WindowEvent.h"
#include "Layers/LayerStack.h"
#include "Graphics/API/Context.h"
#include "Input/InputSystem.h"


namespace StepWay
{


	class Application
	{
	private:
		static Application* m_Instance;
	public:
		static Application* GetInstance() { return m_Instance; }

	public:
		Application();
		bool SetUp();
		virtual bool ImplSetUp() = 0;
		void ShutDown();
		virtual void ImplShutDown() = 0;
		void Run();
		virtual void ImplOnNewFrameStart() {};
		virtual void ImplOnNewFrameEnd() {};

		void OnEvent(Event& e);

		//find an better way to pop layers
		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PushOverLay(std::shared_ptr<Layer> overlay);
		void PopOverlay(std::shared_ptr<Layer> overlay);

		//Getters
		inline Window* GetMainWindow()const { return m_MainWindow; }
		inline Graphics::API::GraphicsContext* GetMainContex()const { return m_MainContext; }

		//Setters

		virtual ~Application();
	private:
		void OnMainWindowClose(WindowDestroyEvent& e);

		bool m_IsRunning;

		Window* m_MainWindow;
		Graphics::API::GraphicsContext* m_MainContext;
		Input::InputSystem* m_InputSystem;
		MemoryManager m_MemoryManager;

		LayerStack m_layers;
		LayerStack m_overlays;
	};

	Application* CreateApplication();
};
