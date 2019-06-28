#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Input/Mouse.h"
#include <string>
#include <functional>


namespace StepWay
{


	//Initialization properties of the window
	struct SW_API WindowProp
	{
		std::string title;
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
		static void Destroy(Window* window) { delete window; };

		virtual ~Window() {};

		virtual bool SetUp(const WindowProp& prop) = 0;
		virtual void ShutDown() = 0;
		virtual bool IsInitialized() = 0;

		virtual void OnUpdate() = 0;

		//getters
		//Position (origin is assumed to be in upper left corner)
		virtual int GetX() const = 0;
		virtual int GetY() const = 0;
		//just working zone no borders
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual std::string GetTitle() const = 0;
		virtual std::wstring GetWTitle() const = 0;


		//Control functions
		virtual void Close() = 0;
		virtual void Resize(int width, int height) = 0;
		virtual void SetPosition(int x, int y) = 0;
		virtual void Minimize() = 0;
		virtual void Maximize() = 0;
		virtual void RestoreSize() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;


		//Events related
		virtual void SetEventCallback(const EventCallback& callback) = 0;

		Input::MouseClientInterface GetMouse() { return m_Mouse.GetClientInterface(); }
		
	protected:
		Window() {};

		Input::Mouse m_Mouse;
	};

}
