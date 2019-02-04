#pragma once
#include "Core.h"
#include <string>


namespace StepWay
{

	enum class EventType
	{
		EMPTY = 0,
		KEY_PRESS, KEY_RELEASE,
		MOUSE_MOVE, MOUSE_SCROLL, MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE
		//Add here window events later
	};

	enum EventCategory
	{
		WINDOW_CONTROL_CATEGORY	= BIT(0),
		INPUT_CATEGORY			= BIT(1),
		KEYBOARD_CATEGORY		= BIT(2),
		MOUSE_CATEGORY			= BIT(3),
		MOUSE_BUTTON			= BIT(4)
	};




#define SW_DECLARE_EVENT_CATEGORY(category)\
			virtual int GetEventCategory() const override {return category;}		

//static is needed cause we needn't an instance of Event to find out its type
#define SW_DECLARE_EVENT_TYPE(type)\
		static EventType GetStaticEventType(){return type;}\
		virtual EventType GetEventType() const override { return GetStaticEventType(); }\
		virtual std::string GetTypeString() const override { return #type; }



	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual std::string GetTypeString() const = 0;

		virtual std::string ToString() const { return GetTypeString(); };
		virtual ~Event() {};

		inline bool IsOfCategories(EventCategory OredCategories) const { return GetEventCategory()&OredCategories; };

	protected:
	};

	std::ostream& operator<<(std::ostream& ost,const Event& e) { ost << e.ToString(); return ost; }

}
