#pragma once
#include "Core.h"
#include "Memory/MemoryManager.h"
#include "Window.h"
#include "Events/WindowEvent.h"


namespace StepWay
{
	class SW_API Application
	{
	public:
	private:
		MemoryManager m_MemoryManager;
	public:
		bool Init();
		void Destroy();
		void Run();

		void OnEvent(Event& e);

		virtual ~Application();
	private:
		void OnMainWindowClose(WindowDestroyEvent& e);
		bool m_IsRunning;
		Window* m_MainWindow;
	};

	Application* CreateApplication();
}