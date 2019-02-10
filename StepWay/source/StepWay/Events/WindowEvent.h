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

		Window* GetWindowPtr() { return m_window; }
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


}