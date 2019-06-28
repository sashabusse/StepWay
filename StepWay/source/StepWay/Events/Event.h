#pragma once
#include "Core.h"
#include <string>
#include <functional>


namespace StepWay
{

	enum class EventType
	{
		EMPTY = 0,
		KEY_PRESS, KEY_RELEASE,
		MOUSE_MOVE,MOUSE_RAW_MOVE, MOUSE_SCROLL, MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE,
		WINDOW_DESTROY, WINDOW_MOVE, WINDOW_MOVE_END, WINDOW_RESIZE, WINDOW_RESIZE_END
		//Add here window events later
	};

	enum EventCategory : int
	{
		WINDOW_CONTROL_CATEGORY	= BIT(0),
		INPUT_CATEGORY			= BIT(1),
		KEYBOARD_CATEGORY		= BIT(2),
		MOUSE_CATEGORY			= BIT(3),
		WINDOW_CATEGORY			= BIT(4)
	};




#define SW_DECLARE_EVENT_CATEGORY(category)\
			virtual int GetEventCategory() const override {return category;}		

//static is needed cause we needn't an instance of Event to find out its type
#define SW_DECLARE_EVENT_TYPE(type)\
		static EventType GetStaticEventType(){return type;}\
		virtual EventType GetEventType() const override { return GetStaticEventType(); }\
		virtual std::string GetTypeString() const override { return #type; }\
		virtual std::wstring GetTypeWString() const override { return L#type; }



	class Event
	{
	public:
		virtual int GetEventCategory() const = 0;

		virtual EventType GetEventType() const = 0;
		virtual std::string GetTypeString() const = 0;
		virtual std::wstring GetTypeWString() const = 0;

		virtual std::string ToString() const { return GetTypeString(); };
		virtual std::wstring ToWString() const { return GetTypeWString(); };

		virtual ~Event() {};

		inline bool IsOfCategories(EventCategory OredCategories) const { return GetEventCategory()&OredCategories; };

		bool IsHandled() const { return m_isHandled; }
		void MarkHandled() { m_isHandled = true; }
	protected:
		bool m_isHandled = false;
	};

	typedef std::function<void(Event&)> EventCallback;

	//Danger reference storage
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e):
			m_event(e)
		{
		}
		template<typename EventArg>
		void Dispatch(const std::function<void(EventArg&)>& fun)
		{
			if (m_event.GetEventType() == EventArg::GetStaticEventType())
				fun(static_cast<EventArg&>(m_event));
		}
	private:
		Event& m_event;
	};

}
inline std::ostream& operator<<(std::ostream& ost, const StepWay::Event& e) { ost << e.ToString(); return ost; }

