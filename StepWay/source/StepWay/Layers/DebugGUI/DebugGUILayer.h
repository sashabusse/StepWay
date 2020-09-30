#pragma once
#include "Layers/Layer.h"
#include "Window.h"
#include "Graphics/API/Context.h"
#include "Input/InputDefs.h"

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
		
	private:
		void OS_SetUp();
		void OS_ShutDown();
		void OS_NewFrame();
		
		void OnMouseButtonPress(Event& e);
		void SetMouseButtonPress(Input::MouseKey keyCode);
		void OnMouseButtonRelease(Event& e);
		void SetMouseButtonRelease(Input::MouseKey keyCode);
		void OnMouseScroll(Event& e);

		void OnKeyPress(Event& e);
		void OnKeyRelease(Event& e);
		void OnCharInput(Event& e);

		void OnDragEnter(Event& e);
		void OnDragLeave(Event& e);
		void OnDragOver(Event& e);
		void OnDrop(Event& e);

	private:
		Window* m_pWindow;
		GraphicsContext* m_Context;
		
		//drag and drop
		bool m_external_dragging;
		std::vector<std::wstring> m_dragged_filenames;
		std::vector<std::wstring>* m_p_dragged_filenames;
	};




}