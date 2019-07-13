#include "StepWayPCH.h"
#include "Win32Window.h"
#include "Utility.h"

//overriding platform specific Creation function from Window.h
StepWay::Window* StepWay::Window::Create() { return SW_NEW StepWay::Win32::Win32Window; }

namespace StepWay
{	namespace Win32
	{
		

		Win32Window::Win32Window() :
			m_callback([](Event&) {}),
			m_position({ 0,0 }),
			m_IsMoving(false),
			m_size({ 0,0 }),
			m_IsResizing(false),
			m_wnd(NULL),
			m_DC(NULL)
		{

		}


		Win32Window::~Win32Window()
		{
		}


		bool Win32Window::SetUp(const WindowProp & prop)
		{

			m_title = prop.title;

			WNDCLASSEX wndclass;

			//check if class already exist, if not create it.
			if (!GetClassInfoExW(GetModuleHandle(NULL), SW_DEFAULT_WND_CLASS_NAME, &wndclass))
			{
				SW_CORE_ASSERT(GetLastError() == ERROR_CLASS_DOES_NOT_EXIST, "unexpected error in GetClassInfoExW");

				memset(&wndclass, 0, sizeof(wndclass));

				//filling in
				wndclass.cbSize = sizeof(wndclass);
				wndclass.lpfnWndProc = WindowProcedure;
				wndclass.lpszClassName = SW_DEFAULT_WND_CLASS_NAME;
				wndclass.hInstance = NULL;
				wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);
				wndclass.hIcon = LoadIconW(NULL, IDI_APPLICATION);
				wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

				wndclass.cbWndExtra = sizeof(Win32Window*);
				

				if (!RegisterClassExW(&wndclass))
				{
					SW_CORE_WARNING("Failed to Register Window Class");
					DBG_BREAK();
					return false;
				}
			}

			//setting client area properties of window
			m_size.height = prop.height;
			m_size.width = prop.width;
			m_position.x = prop.luX;
			m_position.y = prop.luY;

			//calculating window rect of area + border
			RECT newRect;
			newRect.left = prop.luX;
			newRect.right = prop.luX + prop.width;
			newRect.top = prop.luY;
			newRect.bottom = prop.luY + prop.height;
			AdjustWindowRectEx(&newRect, WS_OVERLAPPEDWINDOW, NULL, NULL);

			m_BorderSize = { prop.luX - newRect.left,prop.luY - newRect.top };

			m_wnd = CreateWindowExW(NULL, SW_DEFAULT_WND_CLASS_NAME, 
				Utility::StrToWstr(m_title).c_str(), WS_OVERLAPPEDWINDOW,
				newRect.left, newRect.top,//position
				newRect.right - newRect.left,//width
				newRect.bottom - newRect.top,//height
				NULL, NULL, NULL, this);

			SW_CORE_ASSERT(m_wnd != NULL, "failed to create window");

			m_DC = ::GetDC(m_wnd);
			SW_CORE_ASSERT(m_DC != NULL, "failed to retrieve DC");

			ShowWindow(m_wnd, SW_NORMAL);
			UpdateWindow(m_wnd);

			return true;
		}

		
		//Delete binding and destroys window
		void Win32Window::ShutDown()
		{
			ReleaseDC(m_wnd,m_DC);
			Close();
		}

		bool Win32Window::IsInitialized()
		{
			return m_wnd != NULL;
		}



		//PollEvents and then Present new frame
		void Win32Window::OnUpdate()
		{
			PollEvents();
		}


		std::string Win32Window::GetTitle() const
		{
			return m_title;
		}

		std::wstring Win32Window::GetWTitle() const
		{
			return Utility::StrToWstr(m_title);
		}

		int Win32Window::GetX() const
		{
			return m_position.x;
		}

		int Win32Window::GetY() const
		{
			return m_position.y;
		}

		int Win32Window::GetWidth() const
		{
			return m_size.width;
		}

		int Win32Window::GetHeight() const
		{
			return m_size.height;
		}



		//not done yet
		void Win32Window::Resize(int width, int height)
		{
			SW_CORE_ASSERT(false, "Resize is not done yet");
		}


		//pay attention on review
		//position of client area
		void Win32Window::SetPosition(int x, int y)
		{
			m_position.x = x;
			m_position.y = y;

			RECT Rect;
			Rect.top = y;
			Rect.bottom = y + m_size.height;
			Rect.left = x;
			Rect.right = x + m_size.width;

			//AdjustWindowRectEx(&Rect, WS_OVERLAPPEDWINDOW, NULL, NULL);

			SetWindowPos(m_wnd, NULL, Rect.left, Rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}

		void Win32Window::Minimize()
		{
			ShowWindow(m_wnd, SW_MINIMIZE);
		}

		void Win32Window::Maximize()
		{
			ShowWindow(m_wnd, SW_MAXIMIZE);
		}

		void Win32Window::RestoreSize()
		{
			ShowWindow(m_wnd, SW_RESTORE);
		}

		void Win32Window::Show()
		{
			SW_CORE_ASSERT(false, "Show is not done yet");
		}

		void Win32Window::Hide()
		{
			ShowWindow(m_wnd, SW_HIDE);
		}

		void Win32Window::SetInputCapture()
		{
			SetCapture(m_wnd);
		}

		void Win32Window::ReleaseInputCapture()
		{
			ReleaseCapture();
		}


		void Win32Window::Close()
		{
			if (m_wnd != NULL)
			{
				DestroyWindow(m_wnd);
				m_wnd = NULL;
			}
		}



		void Win32Window::SetEventCallback(const EventCallback & callback)
		{
			m_callback = callback;
		}





		HWND Win32Window::GetHWND() const
		{
			return m_wnd;
		}

		HDC Win32Window::GetDC() const
		{
			return m_DC;
		}



		//just poll message que
		void Win32Window::PollEvents()
		{
			MSG msg;
			while (PeekMessageW(&msg, m_wnd, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}


}}