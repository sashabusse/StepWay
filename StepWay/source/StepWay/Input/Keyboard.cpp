#include "StepWayPCH.h"
#include "Keyboard.h"
#include "Events/KeyEvent.h"

namespace StepWay
{	
	namespace Input
	{

		bool Keyboard::m_KeyPressed[(int)KeyboardKey::KEYBOARD_MAX_BUTTON_VAL];
		EventCallback Keyboard::m_callback;

		void Keyboard::SetUp()		
		{
			m_callback = [](Event& e) {};
			memset(m_KeyPressed, 0, sizeof(bool)*(int)KeyboardKey::KEYBOARD_MAX_BUTTON_VAL);
		}

		void Keyboard::SetEventCallback(const EventCallback & callback)
		{
			m_callback = callback;
		}

		bool Keyboard::IsKeyPressed(KeyboardKey key)
		{
			return m_KeyPressed[(int)key];
		}

		void Keyboard::OnButtonPress(KeyboardKey key)
		{
			m_KeyPressed[(int)key] = true;
			m_callback(KeyPressEvent(key, NULL));
		}

		void Keyboard::OnButtonRelease(KeyboardKey key)
		{
			m_KeyPressed[(int)key] = false;
			m_callback(KeyReleaseEvent(key, NULL));
		}

		void Keyboard::OnCharInput(wchar_t wch)
		{
			m_callback(CharInputEvent(wch));
		}


	}
}