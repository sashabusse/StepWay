#pragma once
#include "Core.h"
#include "Memory/MemoryManager.h"

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
		virtual ~Application();
	private:
	};

	Application* CreateApplication();
}