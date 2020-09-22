#pragma once
#include "StepWayPCH.h"
#include "Mouse.h"
#include "Events/MouseEvents.h"
#include "Application.h"




namespace StepWay
{	
	namespace Input
	{

		CursorMode Mouse::m_cursor_mode;
		EventCallback Mouse::m_callback;
		float Mouse::m_x, Mouse::m_y;
		bool Mouse::m_ButtonPressed[(int)MouseKey::MOUSE_MAX_BUTTON_VAL];

		void Mouse::SetUp()
		{
			m_x = 0;
			m_y = 0;
			m_callback = [](Event&) {};
			memset(m_ButtonPressed, 0, sizeof(bool) * (int)MouseKey::MOUSE_MAX_BUTTON_VAL);
		}
		

		void Mouse::OnMouseMove(float x, float y)
		{
			if (m_cursor_mode == CursorMode::CAMERA)
			{
				SetToWndCenter();
			}
			else
			{
				m_x = x;
				m_y = y;
				m_callback(MouseMoveEvent(m_x, m_y));
			}
		}

		void Mouse::SetToWndCenter()
		{
			Window& wnd = Application::GetWindow();
			glm::ivec2 center({ wnd.GetX() + wnd.GetWidth() / 2,wnd.GetY() + wnd.GetHeight() / 2 });
			Application::GetInputSystem().SetCursorPosition(center);
			m_x = center.x;
			m_y = center.y;
		}


		void Mouse::OnRawMouseMove(float dx, float dy)
		{
			m_callback(MouseRawMoveEvent(dx, dy));
		}

		void Mouse::OnMousePress(MouseKey KeyCode)
		{
			m_ButtonPressed[(int)KeyCode] = true;
			m_callback(MouseButtonPressEvent(KeyCode, 0, m_x, m_y));
		}

		void Mouse::OnMouseRelease(MouseKey KeyCode)
		{
			m_ButtonPressed[(int)KeyCode] = false;
			m_callback(MouseButtonReleaseEvent(KeyCode, 0, m_x, m_y));
		}

		void Mouse::SetPosition(float x, float y)
		{
			m_x = x;
			m_y = y;
			Application::GetInputSystem().SetCursorPosition(glm::ivec2({ x, y }));
		}

		void Mouse::SetCursorMode(CursorMode mode)
		{
			m_cursor_mode = mode;
			if (m_cursor_mode == CursorMode::CAMERA)
			{
				Application::GetInputSystem().HideCursor(true);
				SetToWndCenter();
			}
			else
			{
				Application::GetInputSystem().HideCursor(false);
			}
		}

		

		void Mouse::OnMouseScroll(float offset)
		{
			m_callback(MouseScrollEvent(m_x, m_y, offset));
		}


		void Mouse::SetEventCallback(const EventCallback & callback)
		{
			m_callback = callback;
		}

	
	}
}