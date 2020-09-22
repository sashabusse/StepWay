#include "StepWayPCH.h"
#include "Win32Window.h"
#include "Events/WindowEvent.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvent.h"
#include "Win32InputSystem.h"

namespace StepWay
{	namespace Win32
	{

	using Input::Win32::Win32InputSystem;

	LRESULT __stdcall WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{

		if (msg == WM_CREATE)
		{
			//mb store in some other form
			CREATESTRUCT* pStruct = (CREATESTRUCT*)lparam;
			SetWindowLongPtrW(wnd, 0, reinterpret_cast<LONG_PTR>(pStruct->lpCreateParams));
			return 0;
		}

		//may be store in some other form
		Win32Window* pWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtrW(wnd, 0));

		//unroll to if and some delegation later
		switch (msg)
		{
		case WM_DESTROY:
		{
			StepWay::WindowDestroyEvent destrEvent(pWindow);
			pWindow->m_callback(destrEvent);
			break;
		}

		//MouseInput
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN: case WM_LBUTTONUP:
		case WM_RBUTTONDOWN: case WM_RBUTTONUP:
		case WM_MBUTTONDOWN: case WM_MBUTTONUP:
		{
			pWindow->MouseInputHandler(msg, wparam, lparam);
			break;
		}

		//Keyboard input
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		{
			pWindow->KeyboardInputHandler(msg, wparam, lparam);
			break;
		}

		case WM_WINDOWPOSCHANGED://changes in position or size or both
		case WM_EXITSIZEMOVE://END OF MOVE OR RESIZE
		{
			pWindow->WindowSizeMoveHandler(msg, wparam, lparam);
			break;
		}
		default:
		{
			break;
		}
		}

		return DefWindowProc(wnd, msg, wparam, lparam);
	}


	void Win32Window::MouseInputHandler(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			case WM_INPUT:
			{
				HRAWINPUT hInput = (HRAWINPUT)lparam;
				UINT dataSize;
				RAWINPUT inputData;
				GetRawInputData(hInput, RID_INPUT, &inputData, &dataSize, sizeof(RAWINPUTHEADER));
				if (inputData.header.dwType == RIM_TYPEMOUSE)
				{
					const RAWMOUSE& rawMouse = inputData.data.mouse;

					SW_CORE_ASSERT(!(rawMouse.usFlags&MOUSE_MOVE_ABSOLUTE), "raw input intended to be relative");

					//Raw Move
					if (rawMouse.lLastX != 0 || rawMouse.lLastY != 0)
					{
						Input::Mouse::OnRawMouseMove(
							(float)rawMouse.lLastX, (float)rawMouse.lLastY);
					}


					//Now using legacy WM_xxx for handling mouse clicks to make default interface work
					//--------------------------------------------------------------
					//Button Press
					//if (rawMouse.usButtonFlags&RI_MOUSE_LEFT_BUTTON_DOWN)
					//{
					//	m_Mouse.OnMousePress(Input::L_BUTTON);
					//}
					//if (rawMouse.usButtonFlags&RI_MOUSE_RIGHT_BUTTON_DOWN)
					//{
					//	m_Mouse.OnMousePress(Input::R_BUTTON);
					//}
					//if (rawMouse.usButtonFlags&RI_MOUSE_MIDDLE_BUTTON_DOWN)
					//{
					//	m_Mouse.OnMousePress(Input::MID_BUTTON);
					//}

					//BUtton Release
					//if (rawMouse.usButtonFlags&RI_MOUSE_LEFT_BUTTON_UP)
					//{
					//	m_Mouse.OnMouseRelease(Input::L_BUTTON);
					//}
					//if (rawMouse.usButtonFlags&RI_MOUSE_RIGHT_BUTTON_UP)
					//{
					//	m_Mouse.OnMouseRelease(Input::R_BUTTON);
					//}
					//if (rawMouse.usButtonFlags&RI_MOUSE_MIDDLE_BUTTON_UP)
					//{
					//	m_Mouse.OnMouseRelease(Input::MID_BUTTON);
					//}
					//--------------------------------------------------------------------------

					//scroll
					if (rawMouse.usButtonFlags&RI_MOUSE_WHEEL)
					{
						float OneNotch = (float)WHEEL_DELTA;
						float Delta = (float)((short)rawMouse.usButtonData);
						Input::Mouse::OnMouseScroll(Delta / OneNotch);
					}
				}
				break;
			}


			//Legacy messages------------------------------------------
			case WM_MOUSEMOVE:
			{
				//here is relative to client area
				Input::Mouse::OnMouseMove(
					(float)GET_X_LPARAM(lparam), (float)GET_Y_LPARAM(lparam));
				break;
			}

			//Make function for changing mode for handling clicks by raw input with lower latency
			//Button press events
			case WM_LBUTTONDOWN:
			{
				Input::Mouse::OnMousePress(Input::MouseKey::L_BUTTON);
				break;
			}
			case WM_RBUTTONDOWN:
			{
				Input::Mouse::OnMousePress(Input::MouseKey::R_BUTTON);
				break;
			}
			case WM_MBUTTONDOWN:
			{
				Input::Mouse::OnMousePress(Input::MouseKey::MID_BUTTON);
				break;
			}
			//button Release events
			case WM_LBUTTONUP:
			{
				Input::Mouse::OnMouseRelease(Input::MouseKey::L_BUTTON);
				break;
			}
			case WM_RBUTTONUP:
			{
				Input::Mouse::OnMouseRelease(Input::MouseKey::R_BUTTON);
				break;
			}
			case WM_MBUTTONUP:
			{
				Input::Mouse::OnMouseRelease(Input::MouseKey::MID_BUTTON);
				break;
			}
		}
	}

	


	void Win32Window::KeyboardInputHandler(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYDOWN)
		{
			KeyboardKey key = Win32InputSystem::MapKey((int)wparam);
			if (key != KeyboardKey::NONE)
				Input::Keyboard::OnButtonPress(key);
		}
		if (msg == WM_KEYUP)
		{
			KeyboardKey key = Win32InputSystem::MapKey((int)wparam);
			if (key != KeyboardKey::NONE)
				Input::Keyboard::OnButtonRelease(Input::Win32::Win32InputSystem::MapKey((int)wparam));
		}
		if (msg == WM_CHAR)
		{
			Input::Keyboard::OnCharInput((wchar_t)wparam);
		}
	}



	void Win32Window::WindowSizeMoveHandler(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			case WM_WINDOWPOSCHANGED://changes in position or size or both
			{
				WINDOWPOS* pNewPos = reinterpret_cast<WINDOWPOS*>(lparam);
				if (!(SWP_NOMOVE & (pNewPos->flags)))
				{
					m_position = { pNewPos->x + m_BorderSize.width,pNewPos->y + m_BorderSize.height };
					m_callback(WindowMoveEvent(this, m_position.x, m_position.y));
					m_IsMoving = true;
				}
				if (!(SWP_NOSIZE & (pNewPos->flags)))
				{
					m_size = { pNewPos->cx,pNewPos->cy };
					m_callback(WindowResizeEvent(this, m_size.width, m_position.y));
					m_IsResizing = true;
				}
				break;
			}
			case WM_EXITSIZEMOVE://END OF MOVE OR RESIZE
			{
				if (m_IsMoving)
				{
					m_callback(WindowMoveEndEvent(this, GetX(), GetY()));
					m_IsMoving = false;
				}
				if (m_IsResizing)
				{
					m_callback(WindowResizeEndEvent(this, GetWidth(), GetHeight()));
					m_IsResizing = false;
				}
				//need to resize context
				break;
			}
		}
	}



}}