#include "StepWayPCH.h"
#include "DebugGUILayer.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvent.h"
#include "Events/DragNDropEvents.h"
#include "OpenGL/imgui_impl_opengl3.h"
#include "imgui.h"
#include <algorithm>

static char* glsl_version = "#version 130";

namespace StepWay
{
	using Input::MouseKey;

	DebugGUILayer::DebugGUILayer(Window * window, GraphicsContext* Context) :
		m_Context(Context),
		m_pWindow(window),
		m_external_dragging(false),
		m_p_dragged_filenames(&m_dragged_filenames)
	{
	}

	DebugGUILayer::~DebugGUILayer()
	{
	}

	void DebugGUILayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

		//Load font
		io.Fonts->AddFontFromFileTTF("..\\Resource\\fonts\\Roboto-Regular.ttf", 13, NULL, io.Fonts->GetGlyphRangesCyrillic());
		io.Fonts->Build();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		
		// Setup Platform/Renderer bindings
		OS_SetUp();
		if (m_Context->GetGAPI_TYPE() == Graphics::API::GAPI_TYPE::OPENGL)
		{
			ImGui_ImplOpenGL3_Init(glsl_version);
		}
		else
		{
			SW_CORE_ASSERT(false, "no realization of debug gui for such GAPI type");
		}
		
	}

	void DebugGUILayer::OnDetach()
	{
		if (m_Context->GetGAPI_TYPE() == Graphics::API::GAPI_TYPE::OPENGL)
		{
			ImGui_ImplOpenGL3_Shutdown();
		}
		else
		{
			SW_CORE_ASSERT(false, "something wrong with gui Detaching");
		}
		ImGui::DestroyContext();

	}

	void DebugGUILayer::BeginFrame()
	{
		if (m_Context->GetGAPI_TYPE() == Graphics::API::GAPI_TYPE::OPENGL)
		{
			ImGui_ImplOpenGL3_NewFrame();
		}
		else
		{
			SW_CORE_ASSERT(false, "something wrong with NewFrame");
		}
		OS_NewFrame();
		ImGui::NewFrame();

		//sourcing external drag and drop
		if (m_external_dragging)
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
			{
				ImGui::SetDragDropPayload("FILES", &m_p_dragged_filenames, sizeof(m_p_dragged_filenames));
				ImGui::BeginTooltip();
				ImGui::Text("FILES");
				ImGui::EndTooltip();
				ImGui::EndDragDropSource();
			}
		}
	}

	void DebugGUILayer::EndFrame()
	{
		ImGui::Render();
		m_Context->MakeCurrent();

		if (m_Context->GetGAPI_TYPE() == Graphics::API::GAPI_TYPE::OPENGL)
		{
			//glViewport(0, 0, display_w, display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		else
		{
			SW_CORE_ASSERT(false, "something wrong with gui render");
		}
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

		//dragNdrop
		dispatcher.Dispatch<DragEnterEvent>(SW_BIND_METH_1(DebugGUILayer::OnDragEnter));
		dispatcher.Dispatch<DragLeaveEvent>(SW_BIND_METH_1(DebugGUILayer::OnDragLeave));
		dispatcher.Dispatch<DragOverEvent>(SW_BIND_METH_1(DebugGUILayer::OnDragOver));
		dispatcher.Dispatch<DropEvent>(SW_BIND_METH_1(DebugGUILayer::OnDrop));
	}


	void DebugGUILayer::OnMouseButtonPress(Event& e)
	{
		MouseButtonPressEvent* pPressEvent = (MouseButtonPressEvent*)(&e);
		SetMouseButtonPress(pPressEvent->GetKeyCode());
	}

	void DebugGUILayer::SetMouseButtonPress(MouseKey keyCode)
	{
		ImGuiIO& io = ImGui::GetIO();
		
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
		MouseButtonReleaseEvent* pReleaseEvent = (MouseButtonReleaseEvent*)(&e);
		SetMouseButtonRelease(pReleaseEvent->GetKeyCode());
	}

	void DebugGUILayer::SetMouseButtonRelease(MouseKey keyCode)
	{
		ImGuiIO& io = ImGui::GetIO();

		int button = 0;
		if (keyCode == MouseKey::L_BUTTON) { button = 0; }
		if (keyCode == MouseKey::R_BUTTON) { button = 1; }
		if (keyCode == MouseKey::MID_BUTTON) { button = 2; }
		//if (keyCode == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
		io.MouseDown[button] = false;
		if (!ImGui::IsAnyMouseDown() && m_pWindow->HaveInputCapture())
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

	void DebugGUILayer::OnDragEnter(Event& e)
	{
		//saying about click happened
		SetMouseButtonPress(MouseKey::L_BUTTON);
		m_external_dragging = true;
	}

	void DebugGUILayer::OnDragLeave(Event& e)
	{
		//here may be error and drop occur when leaving the area
		//saying about click released
		SetMouseButtonRelease(MouseKey::L_BUTTON);
		m_external_dragging = false;
	}

	void DebugGUILayer::OnDragOver(Event& e)
	{
		DragOverEvent* doe = (DragOverEvent*)&e;
		//make change pos
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(doe->GetX(), doe->GetY());
	}

	void DebugGUILayer::OnDrop(Event& e)
	{
		DropEvent* de = (DropEvent*)&e;
		m_dragged_filenames = (de->GetFilenames());
		//saying about click released
		SetMouseButtonRelease(MouseKey::L_BUTTON);
		m_external_dragging = false;
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