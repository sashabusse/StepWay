#pragma once
#include "Layers/Layer.h"
#include "Core.h"
#include "Win32/Win32Window.h"
#include "Graphics/API/Context.h"

namespace StepWay
{
	using Graphics::API::GraphicsContext;

	class SW_API  DebugGUILayer : public Layer
	{
	public:
		DebugGUILayer(Window* window,GraphicsContext* Context);

		~DebugGUILayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

		std::string ToString() const override;
		std::wstring ToWString() const override;


	private:

		void OnMouseButtonPress(Event& e);
		void OnMouseButtonRelease(Event& e);
		void OnMouseScroll(Event& e);
	private:
		Win32::Win32Window* m_pWindow;
		GraphicsContext* m_Context;


		bool m_show_demo_window;

	};




}