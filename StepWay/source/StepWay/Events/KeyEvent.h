#pragma once
#include "Core.h"
#include "Event.h"
#include "Input/InputDefs.h"
#include "Utility.h"


namespace StepWay
{
	using Input::KeyboardKey;



	class KeyEvent : public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(KEYBOARD_CATEGORY | INPUT_CATEGORY)

		//Overrides
		virtual std::string ToString() const override
		{
			return GetTypeString() + "(KeyCode=" + std::to_string((int)m_keyCode) + ")";
		};
		virtual std::wstring ToWString() const override
		{
			return GetTypeWString() + L"(KeyCode=" + std::to_wstring((int)m_keyCode) + L")";
		};

		//special
		inline KeyboardKey GetKeyCode() const { return m_keyCode; } ;
		inline int GetFlags() const { return m_flags; } ;

	protected:
		KeyEvent(KeyboardKey key,int flags) :
			m_keyCode(key),
			m_flags(flags)
		{};
		KeyboardKey m_keyCode;
		int m_flags;
		//may be some other data later
	};



	class KeyPressEvent : public KeyEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::KEY_PRESS)


		KeyPressEvent(KeyboardKey key, int flags) :
			KeyEvent(key ,flags)
		{};
		

		~KeyPressEvent()override {};
	};




	class KeyReleaseEvent: public KeyEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::KEY_RELEASE)


		KeyReleaseEvent(KeyboardKey key, int flags) :
			KeyEvent(key, flags)
		{};


		~KeyReleaseEvent()override {};
	};



	class CharInputEvent: public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(INPUT_CATEGORY | KEYBOARD_CATEGORY);
		SW_DECLARE_EVENT_TYPE(EventType::CHAR_INPUT);


		CharInputEvent(wchar_t wch) :
			m_wch(wch)
		{};


		virtual std::string ToString()const override 
		{ 
			if (Utility::IsASCII(m_wch))
			{
				return GetTypeString() + "( not ASCII symbol )";
			}
			return GetTypeString() + "( " + (char)m_wch + " )";
		};
		virtual std::wstring ToWString()const override { return GetTypeWString() + L"( " + m_wch + L" )"; };


		inline wchar_t GetWChar()const { return m_wch; }
		//may be incorrect in case of not ASCII symbols
		inline char GetChar()const { return Utility::WChToCh(m_wch); }

		~CharInputEvent() override {};
	private:
		wchar_t m_wch;
	};

}