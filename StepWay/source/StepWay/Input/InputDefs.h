#pragma once


namespace StepWay
{	namespace Input
	{

	enum class SW_API MouseKey : int
	{
		NONE = 0,
		L_BUTTON,
		R_BUTTON,
		MID_BUTTON,
		SCROLL_BUTTON,
		MOUSE_MAX_BUTTON_VAL
	};


	enum class SW_API KeyboardKey : int
	{
		NONE = 0,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_MINUS,
		KEY_EQUAL,//not done yet
		KEY_SPACE,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_INSERT,
		KEY_DELETE,
		KEY_ENTER,
		KEY_ESCAPE,
		KEYBOARD_MAX_BUTTON_VAL
	};

}}