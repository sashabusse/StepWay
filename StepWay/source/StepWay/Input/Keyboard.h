#pragma once
#include "Core.h"
#include "InputDefs.h"
#include "Events/Event.h"







namespace StepWay
{	
	namespace Input
	{

		class Keyboard
		{
		public:
			static void SetUp();
			
			static void SetEventCallback(const EventCallback& callback);
			static bool IsKeyPressed(KeyboardKey key);

			static void OnButtonPress(KeyboardKey key);
			static void OnButtonRelease(KeyboardKey key);
			static void OnCharInput(wchar_t wch);

		private:
			static bool m_KeyPressed[(int)KeyboardKey::KEYBOARD_MAX_BUTTON_VAL];
			static EventCallback m_callback;
		};


	}
}

