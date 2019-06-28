#pragma once
#include <map>
#include "Input/InputSystem.h"
#include "Events/Event.h"
#include <memory.h>

namespace StepWay
{	namespace Input
	{	namespace Win32
		{


	class Win32InputSystem : public InputSystem
	{
	public:

		Win32InputSystem() {};
		
	private:
		virtual void ImplSetUp() override;
		virtual void ImplShutDown() override;

		void RegisterMouses();
		int a;
	};



}}}