#pragma once
#include "Core.h"
#include "InputDefs.h"
#include "Events/Event.h"
#include <queue>
#include <memory>





namespace StepWay
{	namespace Input
	{
	
	enum SW_API MouseInputMode : int
	{
		NORMAL=0,
		CAMERA=1 //Disable cursor
	};

	class SW_API MouseClientInterface;




	class SW_API Mouse
	{
	public:
		Mouse();
		Mouse(float x, float y);
		
		MouseClientInterface GetClientInterface();
		//ClientInterface
		void SetEventCallback(const EventCallback& callback);
		inline bool IsButtonDown(MouseKey code) const { return m_ButtonPressed[(int)code]; };
		inline float GetX() const { return m_x; };
		inline float GetY() const { return m_y; };
		
		void OnMouseMove(float x, float y);
		void OnRawMouseMove(float dx, float dy);

		void OnMousePress(MouseKey KeyCode);
		void OnMouseRelease(MouseKey KeyCode);

		void SetPosition(float x, float y);

		void OnMouseScroll(float offset);
		
	protected:
		EventCallback m_callback;
		float m_x, m_y;
		bool m_ButtonPressed[(int)MouseKey::MOUSE_MAX_BUTTON_VAL];
	};


	class SW_API MouseClientInterface
	{
	public:
		MouseClientInterface() = delete;
		MouseClientInterface(Mouse& mouse) :
			m_Mouse(mouse) {};
		inline void SetEventCallback(const EventCallback& callback) { m_Mouse.SetEventCallback(callback); };
		inline bool IsButtonDown(MouseKey code) const { return m_Mouse.IsButtonDown(code); };
		inline float GetX() const { return m_Mouse.GetX(); };
		inline float GetY() const { return m_Mouse.GetY(); };
	private:
		Mouse& m_Mouse;
	};

}}