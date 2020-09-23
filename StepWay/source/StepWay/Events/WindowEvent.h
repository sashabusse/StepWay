#pragma once
#include "Event.h"
#include "Window.h"


namespace StepWay
{

	class WindowEvent :public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(WINDOW_CATEGORY)


		explicit WindowEvent(Window* window) :
			m_window(window)
		{};

		inline Window* GetWindowPtr() { return m_window; }
	protected:
		Window* m_window;
	};


	class WindowDestroyEvent : public WindowEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_DESTROY)


		explicit WindowDestroyEvent(Window* window) :
			WindowEvent(window)
		{};

		~WindowDestroyEvent() override {};
	private:

	};


	class WindowResizeEvent : public WindowEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_RESIZE);


		explicit WindowResizeEvent(Window* window, int width, int height) :
			WindowEvent(window),
			m_width(width),
			m_height(height)
		{};
		inline int GetWidth()const { return m_width; }
		inline int GetHeight()const { return m_height; }
		inline float GetAspectRatio()const { return m_width * 1.0 / m_height; }

		~WindowResizeEvent() override {};
	private:
		int m_width, m_height;
	};
	
	class WindowResizeEndEvent : public WindowResizeEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_RESIZE_END);


		explicit WindowResizeEndEvent(Window* window, int width, int height) :
			WindowResizeEvent(window,width,height)
		{};

		~WindowResizeEndEvent() override {};
	private:
	};

	class WindowMoveEvent : public WindowEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_MOVE);


		virtual std::string ToString() const
		{
			return GetTypeString() + "(dx=" + std::to_string(GetX()) + " , dy=" + std::to_string(GetY()) + ")";
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString() + L"(dx=" + std::to_wstring(GetX()) + L" , dy=" + std::to_wstring(GetY()) + L")";
		};


		explicit WindowMoveEvent(Window* window, int x, int y):
			WindowEvent(window),
			m_x(x),
			m_y(y)
		{};

		inline int GetX()const{return m_x;}
		inline int GetY()const{return m_y;}

		~WindowMoveEvent() override {};
	private:
		int m_x, m_y;
	};

	class WindowMoveEndEvent : public WindowMoveEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::WINDOW_MOVE_END);


		explicit WindowMoveEndEvent(Window* window, int x, int y) :
			WindowMoveEvent(window, x, y)
		{};

		~WindowMoveEndEvent() override {};
	private:
	};


}