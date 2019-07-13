#pragma once
#include "Events/Event.h"


namespace StepWay
{


	class SW_API Layer
	{
	public:

		Layer();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual std::string ToString() const = 0;
		virtual std::wstring ToWString() const = 0;

		//TODO:
		void Disable() { IsEnabled = false; };
		void Enable() { IsEnabled = true; };
		bool Enabled() const { return IsEnabled; };
		bool Disabled() const { return !Enabled(); };


		virtual ~Layer() {};
	protected:
		bool IsEnabled;
	};

}
