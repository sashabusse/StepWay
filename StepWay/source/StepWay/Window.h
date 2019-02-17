#pragma once
#include "Core.h"
#include "Events/Event.h"
#include <string>
#include <functional>
#include "Graphics/API/Context.h"


namespace StepWay
{


	//Initialization properties of the window
	struct SW_API WindowProp
	{
		std::wstring title;
		int luX;
		int luY;
		int width;
		int height;
	};


	//Window Interface
	//For example realization check Platform/Win32/Win32Window
	class SW_API Window
	{
	public:
		static Window* Create();


		virtual bool SetUp(const WindowProp& prop) = 0;
		virtual void ShutDown() = 0;

		virtual void OnUpdate() = 0;

		//Gettera
		//Position (origin is assumed to be in upper left corner)
		virtual int GetX() const = 0;
		virtual int GetY() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual std::wstring GetTitle() const = 0;


		//Control functions
		virtual void Close() = 0;
		virtual void Resize(int width, int height) = 0;
		virtual void SetPosition(int x, int y) = 0;
		virtual void Minimize() = 0;
		virtual void Maximize() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;


		//Events related
		typedef std::function<void(Event&)> EventCallback;

		virtual void SetEventCallback(const EventCallback& callback) = 0;
		//TODO:
		//virtual void PollQuedEvents()const = 0;


		//graphics context
		virtual void BindContext(graphics::API::Context* context) = 0;
		virtual void MakeContextCurrent() = 0;
		virtual void Present() = 0;


	protected:
		Window() {};

	};

}
