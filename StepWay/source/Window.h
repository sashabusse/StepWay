#pragma once
#include <string>


namespace StepWay
{

	struct WindowProp
	{
		std::string title;
		int width;
		int heigh;
	};


	class Window
	{
	public:
		virtual bool Create(WindowProp& prop) = 0;
		virtual void Destroy() = 0;

		virtual 

	};

}
