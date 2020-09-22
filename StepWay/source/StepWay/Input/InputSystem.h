#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "glm/glm.hpp"
#include <memory>

namespace StepWay
{	namespace Input
	{
	

	//Add support of configuration files later
	class InputSystem
	{
	public:
		static InputSystem* Create();
		static void Destroy(InputSystem* inpSys) { delete inpSys; };

		virtual ~InputSystem();
	
		void SetUp();
		void ShutDown();

		virtual glm::ivec2 GetCursorPosition() = 0;
		virtual void SetCursorPosition(glm::ivec2& pos) = 0;

		virtual void HideCursor(bool b) = 0;

	protected:
		virtual void ImplSetUp() = 0;//should register all devices and fill in devices
		virtual void ImplShutDown() = 0;//clean up if needed

		virtual int MakeID() const;
		//Add some info functions like print devices or to string
		InputSystem();
	private:
	};

}}
