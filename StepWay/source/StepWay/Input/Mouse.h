#pragma once
#include "Core.h"
#include "InputDefs.h"
#include "Events/Event.h"
#include <queue>
#include <memory>





namespace StepWay
{	
	namespace Input
	{
	
		enum class CursorMode : int
		{
			NORMAL=0,
			CAMERA=1 //Disable cursor
		};


		class Mouse
		{
		public:
			static void SetUp();
			
			//ClientInterface
			static void SetEventCallback(const EventCallback& callback);
			static inline bool IsButtonDown(MouseKey code) { return m_ButtonPressed[(int)code]; };
			static inline float GetX() { return m_x; };
			static inline float GetY() { return m_y; };
			
			static void SetPosition(float x, float y);
			static void SetCursorMode(CursorMode mode);

			static void OnMouseMove(float x, float y);
			static void OnRawMouseMove(float dx, float dy);

			static void OnMousePress(MouseKey KeyCode);
			static void OnMouseRelease(MouseKey KeyCode);
			static void OnMouseScroll(float offset);
			

			static EventCallback GetEventCallback() { return m_callback; };
		private:
			static void SetToWndCenter();
		protected:
			static EventCallback m_callback;
			static CursorMode m_cursor_mode;
			static float m_x, m_y;
			static bool m_ButtonPressed[(int)MouseKey::MOUSE_MAX_BUTTON_VAL];
		};


	}
}

