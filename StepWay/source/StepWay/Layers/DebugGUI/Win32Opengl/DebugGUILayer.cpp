#include "StepWayPCH.h"
#include "DebugGUILayer.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvent.h"
#include "imgui.h"
#include "ImGuiImpl/imgui_impl_win32.h"
#include "ImGuiImpl/imgui_impl_opengl3.h"
#include "glad/glad.h"

const char* glsl_version = "#version 130";

namespace StepWay
{
	using Input::MouseKey;

	DebugGUILayer::DebugGUILayer(Window * window, GraphicsContext* Context):
		m_Context(Context),
		m_show_demo_window(true)
	{
		m_pWindow = (Win32::Win32Window*) window;
	}

	DebugGUILayer::~DebugGUILayer()
	{
	}

	void DebugGUILayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(m_pWindow->GetHWND());
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void DebugGUILayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

	}

	void DebugGUILayer::OnUpdate()
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (m_show_demo_window)
			ImGui::ShowDemoWindow(&m_show_demo_window);

		ImGui::Render();
		
		int display_w, display_h;

		m_Context->MakeCurrent();
		
		//glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void DebugGUILayer::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressEvent>(SW_BIND_METH_1(DebugGUILayer::OnMouseButtonPress));

		dispatcher.Dispatch<MouseButtonReleaseEvent>(SW_BIND_METH_1(DebugGUILayer::OnMouseButtonRelease));

		dispatcher.Dispatch<MouseScrollEvent>(SW_BIND_METH_1(DebugGUILayer::OnMouseScroll));

		dispatcher.Dispatch<KeyPressEvent>(SW_BIND_METH_1(DebugGUILayer::OnKeyPress));

		dispatcher.Dispatch<KeyReleaseEvent>(SW_BIND_METH_1(DebugGUILayer::OnKeyRelease));

		dispatcher.Dispatch<CharInputEvent>(SW_BIND_METH_1(DebugGUILayer::OnCharInput));
	}


	void DebugGUILayer::OnMouseButtonPress(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		MouseButtonPressEvent* pPressEvent = (MouseButtonPressEvent*)(&e);
		Input::MouseKey keyCode = pPressEvent->GetKeyCode();
		int button = 0;
		if (keyCode == MouseKey::L_BUTTON) { button = 0; }
		if (keyCode == MouseKey::R_BUTTON) { button = 1; }
		if (keyCode == MouseKey::MID_BUTTON) { button = 2; }
		//if (keyCode == WM_XBUTTONDOWN || keyCode == WM_XBUTTONDBLCLK) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
		io.MouseDown[button] = true;
		if (::GetCapture() == NULL)
			m_pWindow->SetInputCapture();
	}


	void DebugGUILayer::OnMouseButtonRelease(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		MouseButtonReleaseEvent* pReleaseEvent = (MouseButtonReleaseEvent*)(&e);
		Input::MouseKey keyCode = pReleaseEvent->GetKeyCode();
		
		int button = 0;
		if (keyCode == MouseKey::L_BUTTON) { button = 0; }
		if (keyCode == MouseKey::R_BUTTON) { button = 1; }
		if (keyCode == MouseKey::MID_BUTTON) { button = 2; }
		//if (keyCode == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
		io.MouseDown[button] = false;
		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == m_pWindow->GetHWND())
			m_pWindow->ReleaseInputCapture();
	}


	void DebugGUILayer::OnMouseScroll(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		MouseScrollEvent* ScrollEvent = (MouseScrollEvent*)&e;
		io.MouseWheel += ScrollEvent->GetOffset();
	}


	void DebugGUILayer::OnKeyPress(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		KeyPressEvent* PressEvent = (KeyPressEvent*)&e;
		
		io.KeysDown[(int)PressEvent->GetKeyCode()] = 1;

	}

	void DebugGUILayer::OnKeyRelease(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		KeyReleaseEvent* ReleaseEvent = (KeyReleaseEvent*)&e;
		io.KeysDown[(int)ReleaseEvent->GetKeyCode()] = 0;
	}


	void DebugGUILayer::OnCharInput(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		CharInputEvent* ChEvent = (CharInputEvent*)&e;
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		if (ChEvent->GetWChar() > 0 && ChEvent->GetWChar() < 0x10000)
			io.AddInputCharacter(ChEvent->GetWChar());
	}


	// not replicated part
	//
	//-----------------------------------------------------------------------------------------------------
	// Process Win32 mouse/keyboard inputs.
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	// PS: In this Win32 handler, we use the capture API (GetCapture/SetCapture/ReleaseCapture) to be able to read mouse coordinations when dragging mouse outside of our window bounds.
	// PS: We treat DBLCLK messages as regular mouse down messages, so this code will work on windows classes that have the CS_DBLCLKS flag set. Our own example app code doesn't set this flag.
	
	
	//IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	//{
	//	if (ImGui::GetCurrentContext() == NULL)
	//		return 0;
	//
	//	ImGuiIO& io = ImGui::GetIO();
	//	switch (msg)
	//	{
	//	case WM_SETCURSOR:
	//		if (LOWORD(lParam) == HTCLIENT && ImGui_ImplWin32_UpdateMouseCursor())
	//			return 1;
	//		return 0;
	//	case WM_DEVICECHANGE:
	//		if ((UINT)wParam == DBT_DEVNODES_CHANGED)
	//			g_WantUpdateHasGamepad = true;
	//		return 0;
	//	}
	//	return 0;
	//}
	//-----------------------------------------------------------------------------------------------------


	std::string DebugGUILayer::ToString() const
	{
		return "DebugGUILayer(by imgui)";
	}

	std::wstring DebugGUILayer::ToWString() const
	{
		return L"DebugGUILayer(by imgui)";
	}

}