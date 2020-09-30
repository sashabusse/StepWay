#pragma once
#include "Core.h"
#include <string>
#include <functional>


namespace StepWay
{

	enum class EventType
	{
		EMPTY = 0,
		KEY_PRESS, KEY_RELEASE,CHAR_INPUT,
		MOUSE_MOVE,MOUSE_RAW_MOVE, MOUSE_SCROLL, MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE,
		WINDOW_DESTROY, WINDOW_MOVE, WINDOW_MOVE_END, WINDOW_RESIZE, WINDOW_RESIZE_END,
		SCENE_CREATED, SCENE_DESTROYED,//just definitions no realization
		ENTITY_CREATED, ENTITY_DESTROYED,
		DRAGNDROP_ENTER, DRAGNDROP_LEAVE, DRAGNDROP_OVER, DRAGNDROP_DROP
		//Add here window events later
	};

	enum EventCategory : int
	{
		WINDOW_CONTROL_CATEGORY	= BIT(0),
		INPUT_CATEGORY			= BIT(1),
		KEYBOARD_CATEGORY		= BIT(2),
		MOUSE_CATEGORY			= BIT(3),
		WINDOW_CATEGORY			= BIT(4),
		ECS_CATEGORY			= BIT(5),
		DRAGNDROP_CATEGORY		= BIT(6)
	};




#define SW_DECLARE_EVENT_CATEGORY(category)\
			virtual int GetEventCategory() const override {return category;}		

//static is needed cause we needn't an instance of Event to find out its type
#define SW_DECLARE_EVENT_TYPE(type)\
		static EventType GetStaticEventType(){return type;}\
		virtual EventType GetEventType() const override { return GetStaticEventType(); }\
		virtual std::string GetTypeString() const override { return #type; }\
		virtual std::wstring GetTypeWString() const override { return L#type; }


	//base class for events
	class Event
	{
	public:
		//define with SW_DECLARE_EVENT_TYPE
		virtual EventType GetEventType() const = 0;
		virtual std::string GetTypeString() const = 0;
		virtual std::wstring GetTypeWString() const = 0;
		
		//define with SW_DECLARE_EVENT_CATEGORY
		virtual int GetEventCategory() const = 0;

		//category checks
		inline bool IsOfCategoriesAny(EventCategory OredCategories) const { return GetEventCategory()&OredCategories; };
		inline bool IsOfCategoriesAll(EventCategory OredCategories) const { return (GetEventCategory()&OredCategories) == OredCategories; }
		inline bool IsOfCategoriesFullMatch(EventCategory OredCategories) const { return GetEventCategory() == OredCategories; }

		//redefine if want to reporn something else
		virtual std::string ToString() const { return GetTypeString(); };
		virtual std::wstring ToWString() const { return GetTypeWString(); };

		virtual ~Event() {};
	protected:
	};

	//use for event callbacks
	typedef std::function<void(Event&)> EventCallback;





	//Danger reference storage
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e):
			m_event(e)
		{
		}

		template<typename EventTypeArg>
		void Dispatch(const std::function<void(EventTypeArg&)>& fun)
		{
			if (m_event.GetEventType() == EventTypeArg::GetStaticEventType())
				fun(static_cast<EventTypeArg&>(m_event));
		}
		
	private:
		Event& m_event;
	};

}
inline std::ostream& operator<<(std::ostream& ost, const StepWay::Event& e) { ost << e.ToString(); return ost; }

