#pragma once
#include "StepWayPCH.h"
#include "Mouse.h"
#include "Events/MouseEvents.h"



namespace StepWay
{	namespace Input
	{
	Mouse::Mouse():
		Mouse(0,0)
	{
	}
	Mouse::Mouse(float x, float y):
		m_x(x),
		m_y(y),
		m_callback([](Event&) {})
	{
		memset(m_ButtonPressed, 0, sizeof(bool)*(int)MouseKey::MOUSE_MAX_BUTTON_VAL);
	}

	MouseClientInterface Mouse::GetClientInterface()
	{
		return MouseClientInterface(*this); 
	}
	

	void Mouse::OnMouseMove(float x, float y)
	{
		m_x = x;
		m_y = y;
		m_callback(MouseMoveEvent(m_x, m_y));
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
	}

	void Mouse::OnMouseScroll(float offset)
	{
		m_callback(MouseScrollEvent(m_x, m_y, offset));
	}



	void Mouse::SetEventCallback(const EventCallback & callback)
	{
		m_callback = callback;
	}

	
}}