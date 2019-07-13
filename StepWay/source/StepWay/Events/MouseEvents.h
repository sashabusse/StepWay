#pragma once
#include "Event.h"
#include "Input/InputDefs.h"


namespace StepWay
{


	

	class MouseEvent : public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(INPUT_CATEGORY | MOUSE_CATEGORY)
		

		virtual std::string ToString() const
		{
			return GetTypeString() + " x: " + std::to_string(GetX()) + "  y: " + std::to_string(GetY());
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString() + L" x: " + std::to_wstring(GetX()) + L"  y: " + std::to_wstring(GetY());
		};


		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }

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


		virtual std::string ToString() const
		{
			return GetTypeString() + "(offset=" + std::to_string(GetOffset()) + ")";
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString() + L"(x=" + std::to_wstring(GetOffset()) + L")";
		};


		MouseScrollEvent(float x, float y, float offset) :
			MouseEvent(x, y),
			m_offset(offset)
		{};

		inline float GetOffset()const { return m_offset; };

		~MouseScrollEvent() override {};
	private:
		float m_offset;
	};


	class MouseMoveEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_MOVE)


		virtual std::string ToString() const
		{
			return GetTypeString() + "(x=" + std::to_string(GetX()) + " , y=" + std::to_string(GetY()) + ")";
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString() + L"(x=" + std::to_wstring(GetX()) + L" , y=" + std::to_wstring(GetY()) + L")";
		};

		MouseMoveEvent(float x, float y) :
			MouseEvent(x, y)
		{};

		~MouseMoveEvent() override {};
	};

	class MouseRawMoveEvent : public MouseEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_RAW_MOVE)


		virtual std::string ToString() const
		{
			return GetTypeString() + "(dx=" + std::to_string(GetDX()) + " , dy=" + std::to_string(GetDY()) + ")";
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString() + L"(dx=" + std::to_wstring(GetDX()) + L" , dy=" + std::to_wstring(GetDY()) + L")";
		};


		MouseRawMoveEvent(float dx, float dy) :
			m_dx(dx),
			m_dy(dy),
			MouseEvent(0,0)
		{
		}


		inline float GetDX()const { return m_dx; }
		inline float GetDY()const { return m_dy; }

		~MouseRawMoveEvent() override {};
	private:
		float m_dx, m_dy;
	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(Input::MouseKey keyCode, int flags, float x, float y) :
			MouseEvent(x, y),
			m_keyCode(keyCode),
			m_flags(flags)
		{};

		inline Input::MouseKey GetKeyCode() const { return m_keyCode; }
		inline int GetFlags() const { return m_flags; }
	protected:
		Input::MouseKey m_keyCode;
		int m_flags;
	};
	

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_PRESS)

		MouseButtonPressEvent(Input::MouseKey keyCode,int flags,float x, float y) :
			MouseButtonEvent(keyCode,flags,x, y)
		{};

		~MouseButtonPressEvent() override {};
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::MOUSE_BUTTON_RELEASE)

		MouseButtonReleaseEvent(Input::MouseKey keyCode, int flags, float x, float y) :
			MouseButtonEvent(keyCode, flags, x, y)
		{};

		~MouseButtonReleaseEvent() override {};
	};

}