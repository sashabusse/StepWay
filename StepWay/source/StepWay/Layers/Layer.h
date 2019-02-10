#pragma once
#include "Events/Event.h"


namespace StepWay
{
	namespace graphics
	{


		class SW_API Layer
		{
		public:
			virtual ~Layer() {};

			virtual void OnAttach() = 0;
			virtual void OnDetach() = 0;
			virtual void OnUpdate() = 0;
			virtual void OnEvent(Event& e) = 0;

			virtual std::string ToString() const = 0;
			virtual std::wstring ToWString() const = 0;

			//TODO:
			//virtual void Disable() = 0;
			//virtual void Enable() = 0;
		protected:
		};


	}
}
