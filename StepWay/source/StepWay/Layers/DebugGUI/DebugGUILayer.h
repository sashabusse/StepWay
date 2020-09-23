#pragma once
#include "Layers/Layer.h"
#include "Core.h"
#include "Window.h"
#include "Graphics/API/Context.h"
#include "imgui.h"
#include "DebugTab.h"
#include <functional>

namespace StepWay
{
	using Graphics::API::GraphicsContext;

	class  DebugGUILayer : public Layer
	{
	public:
		DebugGUILayer(Window* window,GraphicsContext* Context);

		~DebugGUILayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void BeginFrame();
		void EndFrame();
		void OnEvent(Event& e) override;

		std::string ToString() const override;
		std::wstring ToWString() const override;

		void AddTab(const DbgTab& tab);
		

	private:
		void OS_SetUp();
		void OS_ShutDown();
		void OS_NewFrame();

		void OnMouseButtonPress(Event& e);
		void OnMouseButtonRelease(Event& e);
		void OnMouseScroll(Event& e);
		void OnKeyPress(Event& e);
		void OnKeyRelease(Event& e);
		void OnCharInput(Event& e);

		void ShowDebugWindow(bool* p_opened);
	private:
		Window* m_pWindow;
		GraphicsContext* m_Context;


		bool m_ShowDebugWindow;
		ImGuiWindowFlags m_window_flags;
		struct MainMenuState
		{
			bool ShowAppStatistics;
			bool ShowStyleEditor;
		} m_MainMenuState;

		std::vector<DbgTab> m_Tabs;
	};




}