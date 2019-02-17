#pragma once

#include <Windows.h>
#include <string>

#include "Window.h"
#include "OpenGL/GLContext.h"



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


			bool SetUp(const WindowProp& prop);
			void ShutDown();

			void OnUpdate() override;


			//Position (origin is assumed to be a left upper corner of client area)
			int GetX() const override;
			int GetY() const override;

			//Size of client area
			int GetWidth() const override;
			int GetHeight() const override;
			std::wstring GetTitle() const override;


			//Control
			void Close() override;
			void Resize(int width, int height) override;
			void SetPosition(int x, int y) override;
			void Minimize() override;//-----------------------not overriden-------------
			void Maximize() override;
			void Show() override;
			void Hide() override;



			//Events related
			virtual void SetEventCallback(const EventCallback& callback) override;



			//graphics context
			virtual void BindContext(graphics::API::Context* context) override;
			void MakeContextCurrent() override;
			void Present() override;



			//Windows Specific
			HWND GetHWND() const;

		private:
			void PollEvents();

			graphics::API::ContextBinding* m_contextBinding;


			std::wstring m_title;

			//left upper corner of client area
			struct Position
			{
				int x;
				int	y;
			}m_position;

			//size of client area
			struct Size
			{
				int width;
				int height;
			} m_size;

			//Event Related
			EventCallback m_callback;

			//windows specific
			HWND m_wnd;

		};



}}