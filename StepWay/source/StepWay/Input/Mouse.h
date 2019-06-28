#pragma once
#include "Core.h"
#include "InputDefs.h"
#include "Events/Event.h"
#include <queue>
#include <memory>





namespace StepWay
{	namespace Input
	{
	
	enum MouseInputMode : int
	{
		NORMAL=0,
		CAMERA=1 //Disable cursor
	};

	class MouseClientInterface;




	class SW_API Mouse
	{
	public:
		Mouse();
		Mouse(float x, float y);
		
		MouseClientInterface GetClientInterface();
		//ClientInterface
		void SetEventCallback(const EventCallback& callback);
		inline bool IsButtonDown(MouseKeyCode code) const { return m_ButtonPressed[code]; };
		inline float GetX() const { return m_x; };
		inline float GetY() const { return m_y; };
		
		void OnMouseMove(float x, float y);
		void OnRawMouseMove(float dx, float dy);

		void OnMousePress(MouseKeyCode KeyCode);
		void OnMouseRelease(MouseKeyCode KeyCode);

		void SetPosition(float x, float y);

		void OnMouseScroll(float offset);
		
	protected:
		EventCallback m_callback;
		float m_x, m_y;
		bool m_ButtonPressed[MOUSE_MAX_BUTTON_VAL];
	};


	class MouseClientInterface
	{
	public:
		MouseClientInterface() = delete;
		MouseClientInterface(Mouse& mouse) :
			m_Mouse(mouse) {};
		inline void SetEventCallback(const EventCallback& callback) { m_Mouse.SetEventCallback(callback); };
		inline bool IsButtonDown(MouseKeyCode code) const { return m_Mouse.IsButtonDown(code); };
		inline float GetX() const { return m_Mouse.GetX(); };
		inline float GetY() const { return m_Mouse.GetY(); };
	private:
		Mouse& m_Mouse;
	};

}}