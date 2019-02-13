#pragma once
#include <Windows.h>
#include "Window.h"
#include <string>



#define SW_MAIN_APP_WND_CLASS_NAME L"StepWayMainWindowClass"

LRESULT CALLBACK WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace StepWay
{
	class SW_API Win32Window : public StepWay::Window
	{
	public:
		friend LRESULT CALLBACK ::WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

		Win32Window();
		//TODO:
		//May bee destroy here if still not
		~Win32Window();

		virtual bool Init(WindowProp& prop);
		virtual void Destroy();

		virtual void OnUpdate() override;

		virtual std::wstring GetTitle() const override;

		//Position
		virtual int GetX() const override;
		virtual int GetY() const override;
		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
		virtual void Resize(int width, int height) override;
		virtual void SetPosition(int x, int y) override;


		//Control
		virtual void Close() override;


		//Events related
		virtual void SetEventCallback(const EventCallback& callback) override;

		//graphics context
		void MakeContextCurrent() override;
		void Present() override;

		HWND GetHWND() const;

	private:
		void PollEvents();

		//Event Related
		EventCallback m_callback;
		//-------------


		HWND m_wnd;

		std::wstring m_title;

		struct Position
		{
			int x, y;
		} m_position;

		struct Size
		{
			int width, height;
		} m_size;
	};




}