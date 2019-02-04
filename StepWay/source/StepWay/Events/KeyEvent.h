#pragma once
#include "Core.h"
#include "Event.h"

namespace StepWay
{



	class KeyEvent : public Event
	{
	public:

		SW_DECLARE_EVENT_CATEGORY(KEYBOARD_CATEGORY|INPUT_CATEGORY)

		inline int GetKeyCode() const { return m_keyCode; } ;
		inline int GetFlags() const { return m_flags; } ;

		virtual std::string ToString() const
		{
			return GetTypeString() + " scanCode: " + std::to_string(m_keyCode)
									+ "  flags: " + std::to_string(m_flags);
		};

	protected:
		KeyEvent(int key,int flags) :
			m_keyCode(key),
			m_flags(flags)
		{};
		int m_keyCode;
		int m_flags;
		//may be some other data later
	};


	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int key, int flags) :
			KeyEvent(key ,flags)
		{};

		SW_DECLARE_EVENT_TYPE(EventType::KEY_PRESS)
		//may be some data later
	};


	class KeyReleaseEvent: public KeyEvent
	{
	public:
		KeyReleaseEvent(int key, int flags) :
			KeyEvent(key, flags)
		{};
		SW_DECLARE_EVENT_TYPE(EventType::KEY_RELEASE)
		//may be some data later
	};


}