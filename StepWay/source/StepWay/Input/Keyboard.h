#pragma once
#include "Core.h"
#include "InputDefs.h"
#include "Events/Event.h"






namespace StepWay
{	namespace Input
	{


	class SW_API KeyboardClientInterface;

	class SW_API Keyboard
	{
	public:
		Keyboard();
		
		KeyboardClientInterface GetInterface();
		//Client interface
		void SetEventCallback(const EventCallback& callback);
		bool IsKeyPressed(KeyboardKey key);


		void OnButtonPress(KeyboardKey key);
		void OnButtonRelease(KeyboardKey key);
		void OnCharInput(wchar_t wch);
	private:
		bool m_KeyPressed[(int)KeyboardKey::KEYBOARD_MAX_BUTTON_VAL];
		EventCallback m_callback;
	};


	class SW_API KeyboardClientInterface
	{

	public:
		KeyboardClientInterface() = delete;
		KeyboardClientInterface(Keyboard& keyboard) :
			m_Keyboard(keyboard) {};
		inline void SetEventCallback(const EventCallback& callback) { m_Keyboard.SetEventCallback(callback); };
		inline bool IsKeyPressed(KeyboardKey key) const { return m_Keyboard.IsKeyPressed(key); };
	private:
		Keyboard& m_Keyboard;
	};


}}