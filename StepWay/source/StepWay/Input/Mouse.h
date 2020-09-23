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
			static inline float GetDX() { return m_dx; };
			static inline float GetDY() { return m_dy; };
			
			static void SetPosition(float x, float y);
			static void SetCursorMode(CursorMode mode);

			static void OnMouseMove(float x, float y);
			static void OnRawMouseMove(float dx, float dy);

			static void OnMousePress(MouseKey KeyCode);
			static void OnMouseRelease(MouseKey KeyCode);
			static void OnMouseScroll(float offset);
			

			static void OnUpdate() { m_dx = 0; m_dy = 0; };
			static EventCallback GetEventCallback() { return m_callback; };
		private:
			static void SetToWndCenter();
		protected:
			static EventCallback m_callback;
			static CursorMode m_cursor_mode;
			//mb glm::vec?
			static float m_x, m_y;
			static float m_dx, m_dy;
			static bool m_ButtonPressed[(int)MouseKey::MOUSE_MAX_BUTTON_VAL];
		};


	}
}

