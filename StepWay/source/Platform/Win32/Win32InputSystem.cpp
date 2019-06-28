#include "StepWayPCH.h"
#include "Win32InputSystem.h"
#include "Events/MouseEvents.h"


namespace StepWay
{	namespace Input
	{

	InputSystem * InputSystem::Create() 
	{
		return new Win32::Win32InputSystem;
	}



	namespace Win32
		{




	void Win32InputSystem::ImplSetUp()
	{
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
