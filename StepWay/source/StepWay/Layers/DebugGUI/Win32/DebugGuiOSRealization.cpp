#include "StepWayPCH.h"
#include "../DebugGUILayer.h"
#include "Win32/Win32Window.h"
#include "imgui_impl_win32.h"

namespace StepWay
{
	void DebugGUILayer::OS_SetUp()
	{
		ImGui_ImplWin32_Init(((Win32::Win32Window*)m_pWindow)->GetHWND());
	}

	void DebugGUILayer::OS_ShutDown()
	{
		ImGui_ImplWin32_Shutdown();
	}

	void DebugGUILayer::OS_NewFrame()
	{
		ImGui_ImplWin32_NewFrame();
	}
}