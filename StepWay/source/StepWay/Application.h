#pragma once
#include "Core.h"

namespace StepWay
{
	class SW_API Application
	{
	public:
	private:
	public:
		void Run();
		virtual ~Application();
	private:
	};

	Application* CreateApplication();
}