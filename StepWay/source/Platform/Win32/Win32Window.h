#pragma once

#include <Windows.h>
#include <string>
#include "Window.h"



#define SW_DEFAULT_WND_CLASS_NAME L"StepWayDefaultWindowClass"

namespace StepWay
{	namespace Win32
	{
		
		LRESULT CALLBACK WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);
		
		class Win32Window : public Window
		{
		public:
			friend LRESULT CALLBACK WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);
			
			Win32Window();
			~Win32Window();


			bool SetUp(const WindowProp& prop) override;
			void ShutDown() override;
			bool IsInitialized() override;

			void OnUpdate() override;


			//Position (origin is assumed to be a left upper corner of client area)
			int GetX() const override;
			int GetY() const override;

			//Size of client area
			int GetWidth() const override;
			int GetHeight() const override;
			std::string GetTitle() const override;
			std::wstring GetWTitle() const override;


			//Control
			void Close() override;
			void Resize(int width, int height) override;
			void SetPosition(int x, int y) override;
			void Minimize() override;//-----------------------not overriden-------------
			void Maximize() override;
			void RestoreSize() override;
			void Show() override;
			void Hide() override;


			//Capture
			virtual void SetInputCapture() override;
			virtual void ReleaseInputCapture() override;
			virtual bool HaveInputCapture() const override;

			//Events related
			virtual void SetEventCallback(const EventCallback& callback) override;


			//Windows Specific
			HWND GetHWND() const;
			HDC GetDC() const;


		private:
			
			//WndProc Helper Handlers
			void MouseInputHandler(UINT msg, WPARAM wparam, LPARAM lparam);
			void KeyboardInputHandler(UINT msg, WPARAM wparam, LPARAM lparam);
			void WindowSizeMoveHandler(UINT msg, WPARAM wparam, LPARAM lparam);

		private:
			void PollEvents();

			//remove some of this to Window class
			std::string m_title;
			//Position (origin is assumed to be in upper left corner)
			struct Position { int x, y; } m_position;
			bool m_IsMoving;
			//just working area
			struct Size { int width, height; } m_size;
			struct BorderSize { int width, height; } m_BorderSize;
			bool m_IsResizing;

			//Event Related
			EventCallback m_callback;

			//windows specific
			HWND m_wnd;
			HDC m_DC;

		};

		

}}