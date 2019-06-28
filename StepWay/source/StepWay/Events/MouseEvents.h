#pragma once
#include "Event.h"
#include "Input/InputDefs.h"


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

	//Not Implemented yet
	class MouseScrollEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_SCROLL)

		MouseScrollEvent(float x, float y, float offset) :
			MouseEvent(x, y),
			m_offset(offset)
		{};

		inline float GetOffset()const { return m_offset; };


		virtual std::string ToString() const { return GetTypeString() + "(offset=" + std::to_string(GetOffset()) + ")"; };
		virtual std::wstring ToWString() const { return GetTypeWString() + L"(x=" + std::to_wstring(GetOffset()) + L")"; };

	private:
		float m_offset;
	};


	class MouseMoveEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_MOVE)

		MouseMoveEvent(float x, float y) :
			MouseEvent(x, y)
		{};

		virtual std::string ToString() const { return GetTypeString() + "(x=" + std::to_string(GetX()) + " , y=" + std::to_string(GetY()) + ")"; };
		virtual std::wstring ToWString() const { return GetTypeWString() + L"(x=" + std::to_wstring(GetX()) + L" , y=" + std::to_wstring(GetY()) + L")"; };
	};

	class MouseRawMoveEvent : public MouseEvent
	{
	public:
		MouseRawMoveEvent(float dx, float dy) :
			m_dx(dx),
			m_dy(dy),
			MouseEvent(0,0)
		{
		}

		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_RAW_MOVE)

		inline float GetDX()const { return m_dx; }
		inline float GetDY()const { return m_dy; }

		virtual std::string ToString() const { return GetTypeString() + "(dx=" + std::to_string(GetDX()) + " , dy=" + std::to_string(GetDY()) + ")"; };
		virtual std::wstring ToWString() const { return GetTypeWString() + L"(dx=" + std::to_wstring(GetDX()) + L" , dy=" + std::to_wstring(GetDY()) + L")"; };


	private:
		float m_dx, m_dy;
	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(Input::MouseKeyCode keyCode, int flags, float x, float y) :
			MouseEvent(x, y),
			m_keyCode(keyCode),
			m_flags(flags)
		{};

		inline Input::MouseKeyCode GetKeyCode() const { return m_keyCode; }
		inline int GetFlags() const { return m_flags; }
	protected:
		Input::MouseKeyCode m_keyCode;
		int m_flags;
	};
	

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_PRESS)

		MouseButtonPressEvent(Input::MouseKeyCode keyCode,int flags,float x, float y) :
			MouseButtonEvent(keyCode,flags,x, y)
		{};
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_RELEASE)

		MouseButtonReleaseEvent(Input::MouseKeyCode keyCode, int flags, float x, float y) :
			MouseButtonEvent(keyCode, flags, x, y)
		{};
	};

}