#include "StepWayPCH.h"
#include "InputSystem.h"
namespace StepWay
{	namespace Input
	{


	InputSystem::InputSystem()
	{
	}


	InputSystem::~InputSystem()
	{
	}


	void InputSystem::SetUp()
	{
		Mouse::SetUp();
		Keyboard::SetUp();
		ImplSetUp();
	}

	void InputSystem::ShutDown()
	{

		ImplShutDown();
	}

	int InputSystem::MakeID() const
	{
		static int last = 0;
		SW_CORE_ASSERT(last < 10000, "WTF!!? Why so much devices!?");
		return ++last;
	}


}}