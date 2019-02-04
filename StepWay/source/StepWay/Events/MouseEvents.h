#pragma once
#include "Event.h"


namespace StepWay
{


	class MouseEvent : public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(INPUT_CATEGORY | MOUSE_CATEGORY)
		
		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }

		virtual std::string ToString() const 
		{
			return GetTypeString() + " x: " + std::to_string(GetX()) + "  y: " + std::to_string(GetY());
		};

	protected:
		MouseEvent(float x, float y) :
			m_x(x),
			m_y(y)
		{};

		float m_x, m_y;
	};


	class MouseScrollEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_SCROLL)

		MouseScrollEvent(float x, float y) :
			MouseEvent(x, y)
		{};
	
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_MOVE)

		MouseMoveEvent(float x, float y) :
			MouseEvent(x, y)
		{};
	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(float keyCode, float flags, float x, float y) :
			MouseEvent(x, y),
			m_keyCode(keyCode),
			m_flags(flags)
		{};

		inline int GetKeyCode() const { return m_keyCode; }
		inline int GetFlags() const { return m_flags; }
	protected:
		int m_keyCode;
		int m_flags;
	};
	

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_PRESS)

		MouseButtonPressEvent(float keyCode,float flags,float x, float y) :
			MouseButtonEvent(keyCode,flags,x, y)
		{};
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_RELEASE)

		MouseButtonReleaseEvent(int keyCode, int flags, int x, int y) :
			MouseButtonEvent(keyCode, flags, x, y)
		{};
	};

}