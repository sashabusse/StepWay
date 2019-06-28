#pragma once
#include "Event.h"
#include "Window.h"


namespace StepWay
{

	class SW_API WindowEvent :public Event
	{
	public:
		explicit WindowEvent(Window* window) :
			m_window(window)
		{};
		SW_DECLARE_EVENT_CATEGORY(WINDOW_CATEGORY)

		inline Window* GetWindowPtr() { return m_window; }
	protected:
		Window* m_window;
	};


	class SW_API WindowDestroyEvent : public WindowEvent
	{
	public:
		explicit WindowDestroyEvent(Window* window) :
			WindowEvent(window)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_DESTROY)
	private:

	};


	class SW_API WindowResizeEvent : public WindowEvent
	{
	public:
		explicit WindowResizeEvent(Window* window, int width, int height) :
			WindowEvent(window),
			m_width(width),
			m_height(height)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_RESIZE);
		inline int GetWidth()const { return m_width; }
		inline int GetHeight()const { return m_height; }
	private:
		int m_width, m_height;
	};
	
	class SW_API WindowResizeEndEvent : public WindowResizeEvent
	{
	public:
		explicit WindowResizeEndEvent(Window* window, int width, int height) :
			WindowResizeEvent(window,width,height)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_RESIZE_END);
	private:
	};

	class SW_API WindowMoveEvent : public WindowEvent
	{
	public:
		explicit WindowMoveEvent(Window* window, int x, int y):
			WindowEvent(window),
			m_x(x),
			m_y(y)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_MOVE);
		inline int GetX()const{return m_x;}
		inline int GetY()const{return m_y;}

		virtual std::string ToString() const { return GetTypeString() + "(dx=" + std::to_string(GetX()) + " , dy=" + std::to_string(GetY()) + ")"; };
		virtual std::wstring ToWString() const { return GetTypeWString() + L"(dx=" + std::to_wstring(GetX()) + L" , dy=" + std::to_wstring(GetY()) + L")"; };

	private:
		int m_x, m_y;
	};

	class SW_API WindowMoveEndEvent : public WindowMoveEvent
	{
	public:
		explicit WindowMoveEndEvent(Window* window, int x, int y) :
			WindowMoveEvent(window, x, y)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_MOVE_END);
	private:
	};


}