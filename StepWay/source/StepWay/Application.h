#pragma once
#include "Core.h"
#include "Memory/MemoryManager.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "Layers/LayerStack.h"


namespace StepWay
{
	using graphics::LayerStack;
	using graphics::Layer;
	class SW_API Application
	{
	public:
	private:
		MemoryManager m_MemoryManager;
	public:
		bool Init();
		virtual bool ImplInit() = 0;
		void ShutDown();
		virtual void ImplShutDown() = 0;
		void Run();

		void OnEvent(Event& e);

		//find an better way to pop layers
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		virtual ~Application();
	private:
		void OnMainWindowClose(WindowDestroyEvent& e);

		bool m_IsRunning;

		Window* m_MainWindow;

		LayerStack m_layers;
		LayerStack m_overlays;
	};

	Application* CreateApplication();
};
