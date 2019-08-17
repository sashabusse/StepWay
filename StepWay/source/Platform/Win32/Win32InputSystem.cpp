#include "StepWayPCH.h"
#include "Win32InputSystem.h"
#include "Events/MouseEvents.h"


namespace StepWay
{	namespace Input
	{

	InputSystem * InputSystem::Create() 
	{
		return SW_NEW Win32::Win32InputSystem;
	}



	namespace Win32
		{

		KeyboardKey Win32InputSystem::m_sKeyMap[0xFE + 1];


		KeyboardKey Win32InputSystem::MapKey(int vk_code)
		{
			SW_CORE_ASSERT(vk_code <= 0xFE && vk_code >= 0x01, "invalid vk code");
			return m_sKeyMap[vk_code];
		}

		void Win32InputSystem::ImplSetUp()
		{
		//RegisterMouses();

		for (int i = 0; i < 0xFE + 1; i++)
		{
			m_sKeyMap[i] = KeyboardKey::NONE;
		}

		//numbers (0-9) initialization
		int vk_0 = 0x30;
		int vk_9 = 0x39;
		KeyboardKey num_key = KeyboardKey::KEY_0;
		for (int vk = vk_0 ; vk <= vk_9; vk++, num_key = (KeyboardKey)((int)num_key + 1))
		{
			m_sKeyMap[vk] = num_key;
		}

		//Charters (A-Z) initialization
		int vk_a = 0x41;
		int vk_z = 0x5A;
		KeyboardKey ch_key = KeyboardKey::KEY_A;
		for (int vk = vk_a; vk <= vk_z; vk++, ch_key = (KeyboardKey)((int)ch_key + 1))
		{
			m_sKeyMap[vk] = ch_key;
		}

		m_sKeyMap[VK_OEM_MINUS] = KeyboardKey::KEY_MINUS;
		m_sKeyMap[VK_SPACE] = KeyboardKey::KEY_SPACE;
		m_sKeyMap[VK_TAB] = KeyboardKey::KEY_TAB;
		m_sKeyMap[VK_BACK] = KeyboardKey::KEY_BACKSPACE;
		m_sKeyMap[VK_UP] = KeyboardKey::KEY_UP;
		m_sKeyMap[VK_DOWN] = KeyboardKey::KEY_DOWN;
		m_sKeyMap[VK_LEFT] = KeyboardKey::KEY_LEFT;
		m_sKeyMap[VK_RIGHT] = KeyboardKey::KEY_RIGHT;
		m_sKeyMap[VK_NEXT] = KeyboardKey::KEY_PAGE_DOWN;
		m_sKeyMap[VK_PRIOR] = KeyboardKey::KEY_PAGE_UP;
		m_sKeyMap[VK_HOME] = KeyboardKey::KEY_HOME;
		m_sKeyMap[VK_END] = KeyboardKey::KEY_END;
		m_sKeyMap[VK_INSERT] = KeyboardKey::KEY_INSERT;
		m_sKeyMap[VK_DELETE] = KeyboardKey::KEY_DELETE;
		m_sKeyMap[VK_RETURN] = KeyboardKey::KEY_ENTER;
		m_sKeyMap[VK_ESCAPE] = KeyboardKey::KEY_ESCAPE;

		RegisterMouses();
	}


	void Win32InputSystem::ImplShutDown()
	{

	}

	void Win32InputSystem::RegisterMouses()
	{
		RAWINPUTDEVICE mouse;
		mouse.usUsagePage = 0x01;
		mouse.usUsage = 0x02;
		mouse.hwndTarget = NULL;
		mouse.dwFlags = RIDEV_DEVNOTIFY;
		RegisterRawInputDevices(&mouse, 1, sizeof(RAWINPUTDEVICE));
	}

}}}
