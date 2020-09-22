#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include <string>
#include <functional>


namespace StepWay
{

	//Initialization properties of the window
	struct WindowProperties
	{
		std::string title;
		int luX;
		int luY;
		int width;
		int height;
	};


	//Window Interface
	//For example realization check Platform/Win32/Win32Window
	class Window
	{
	public:
		static Window* Create();
		static void Destroy(Window* window) { delete window; };

		virtual ~Window() {};

		virtual bool SetUp(const WindowProperties& prop) = 0;
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

		//Capture may be bool
		virtual void SetInputCapture() = 0;
		virtual void ReleaseInputCapture() = 0;
		virtual bool HaveInputCapture()const = 0;

		//Events related
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		
	protected:
		Window() {};
	};

}
