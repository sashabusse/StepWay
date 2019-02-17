#include "StepWayPCH.h"
#include "Memory/Memory.h"
#include "Win32Window.h"
#include "Win32Common.h"
#include "Events/WindowEvent.h"
#include "glad/glad.h"


//overriding platform specific Creation function from Window.h
StepWay::Window* StepWay::Window::Create() { return new StepWay::Win32::Win32Window; }

namespace StepWay
{	namespace Win32
	{


		LRESULT WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			if (msg == WM_CREATE)
			{
				//may be store in some other form
				CREATESTRUCT* pStruct = (CREATESTRUCT*)lparam;
				SetWindowLongPtrW(wnd, 0, reinterpret_cast<LONG_PTR>(pStruct->lpCreateParams));
				return 0;
			}


			//may be store in some other form
			Win32Window* pWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtrW(wnd, 0));


			//unroll to if later
			switch (msg)
			{
				case WM_DESTROY:
				{
					StepWay::WindowDestroyEvent destrEvent(pWindow);
					pWindow->m_callback(destrEvent);
					break;
				}

				default:
				{
					break;
				}
			}

			return DefWindowProc(wnd, msg, wparam, lparam);
		}



		Win32Window::Win32Window() :
			m_callback([](Event&) {}),
			m_position({ 0,0 }),
			m_size({ 0,0 }),
			m_wnd(NULL),
			m_contextBinding(nullptr)
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

			//calculating window area
			RECT newRect;
			newRect.left = prop.luX;
			newRect.right = prop.luX + prop.width;
			newRect.top = prop.luY;
			newRect.bottom = prop.luY + prop.height;
			AdjustWindowRectEx(&newRect, WS_OVERLAPPEDWINDOW, NULL, NULL);


			m_wnd = CreateWindowExW(NULL, SW_DEFAULT_WND_CLASS_NAME, prop.title.c_str(), WS_OVERLAPPEDWINDOW,
				newRect.left, newRect.top,//position
				newRect.right - newRect.left,//width
				newRect.bottom - newRect.top,//height
				NULL, NULL, NULL, this);

			SW_CORE_ASSERT(m_wnd != NULL, "failed to create window");

			ShowWindow(m_wnd, SW_NORMAL);
			UpdateWindow(m_wnd);

			return true;
		}

		
		//Delete binding and destroys window
		void Win32Window::ShutDown()
		{
			if(m_contextBinding!=nullptr)
				SW_DELETE m_contextBinding;

			Close();
		}



		//PollEvents and then Present new frame
		void Win32Window::OnUpdate()
		{
			PollEvents();
			Present();
		}



		std::wstring Win32Window::GetTitle() const
		{
			return m_title;
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



		void Win32Window::SetPosition(int x, int y)//pay attention on review
		{
			SW_CORE_ASSERT(false, "Resize is not done yet");
			//TODO:
			//drop window move event here
			m_position.x = x;
			m_position.y = y;

			RECT Rect;
			Rect.top = y;
			Rect.bottom = y + m_size.height;
			Rect.left = x;
			Rect.right = x + m_size.width;

			AdjustWindowRectEx(&Rect, WS_OVERLAPPEDWINDOW, NULL, NULL);

			SetWindowPos(m_wnd, NULL, Rect.left, Rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}



		void Win32Window::Close()
		{
			if (m_wnd != NULL)
			{
				DestroyWindow(m_wnd);
				m_wnd = NULL;
				//need unbinding on destroy
			}
		}



		void Win32Window::SetEventCallback(const EventCallback & callback)
		{
			m_callback = callback;
		}



		void Win32Window::BindContext(graphics::API::Context * context)
		{

			if (m_contextBinding != nullptr)
			{
				SW_DELETE m_contextBinding;
				m_contextBinding = nullptr;
			}

#define SW_APISpace graphics::API::platform

			switch (context->GetType())
			{

			case graphics::API::GraphicsAPIType::OPENGL:
				m_contextBinding = SW_NEW SW_APISpace::GLContextBinding(this, reinterpret_cast<SW_APISpace::GLContext*>(context));
				return;

			}
			SW_CORE_ERROR("failed to create ContextBinding for window");
			SW_CORE_ASSERT(false, "wrong type or return missing");
		}



		void Win32Window::MakeContextCurrent()
		{
			SW_CORE_ASSERT(m_contextBinding != nullptr, "cant make current without context");
			m_contextBinding->MakeCurrent();
		}



		void Win32Window::Present()
		{

			if (m_contextBinding == nullptr)
			{
				SW_CORE_WARNING("swapping without context {default SwapBuffers}");
				SwapBuffers(GetDC(m_wnd));
				return;
			}
			m_contextBinding->Present();
		}



		HWND Win32Window::GetHWND() const
		{
			return m_wnd;
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