#pragma once
#include <map>
#include "Input/InputSystem.h"
#include "Input/InputDefs.h"
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
		
		static KeyboardKey MapKey(int vk_code);

		virtual glm::ivec2 GetCursorPosition() override;
		virtual void SetCursorPosition(glm::ivec2& pos) override;

		virtual void HideCursor(bool b) override;

	private:
		virtual void ImplSetUp() override;
		virtual void ImplShutDown() override;

		void RegisterMouses();
		int a;

		static KeyboardKey m_sKeyMap[0xFE + 1];
	};



}}}