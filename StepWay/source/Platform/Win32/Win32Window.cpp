#include "StepWayPCH.h"
#include "Memory/Memory.h"
#include "Win32Window.h"
#include "Win32Common.h"
#include "Events/WindowEvent.h"


//TODO create resize method


StepWay::Window* StepWay::Window::Create() { return new Win32Window; }


LRESULT WindowProcedure(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_CREATE)
	{
		CREATESTRUCT* pStruct = (CREATESTRUCT*)lparam;
		SetWindowLongPtrW(wnd, 0,reinterpret_cast<LONG_PTR>(pStruct->lpCreateParams));
		return 0;
	}

	StepWay::Win32Window* pWindow = reinterpret_cast<StepWay::Win32Window*>(GetWindowLongPtrW(wnd, 0));

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


StepWay::Win32Window::Win32Window():
	m_callback([](Event&) {}),
	m_position({0,0}),
	m_size({0,0}),
	m_wnd(NULL)
{
}

StepWay::Win32Window::~Win32Window()
{
}

bool StepWay::Win32Window::Init(WindowProp & prop)
{

	m_title = prop.title;

	WNDCLASSEX wndclass;
	if (!GetClassInfoExW(GetModuleHandle(NULL), SW_MAIN_APP_WND_CLASS_NAME, &wndclass))
	{
		SW_CORE_ASSERT(GetLastError() == ERROR_CLASS_DOES_NOT_EXIST, "unexpected error in GetClassInfoExW");
		if (GetLastError() != ERROR_CLASS_DOES_NOT_EXIST)
		{
			SW_CORE_WARNING("GetClassInfoExW Set unexpected error");
		}
		

		memset(&wndclass, 0, sizeof(wndclass));
		//filling in
		wndclass.cbSize = sizeof(wndclass);
		wndclass.lpfnWndProc = WindowProcedure;
		wndclass.lpszClassName = SW_MAIN_APP_WND_CLASS_NAME;
		wndclass.hInstance = NULL;
		wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIconW(NULL, IDI_APPLICATION);

		wndclass.cbWndExtra = sizeof(Win32Window*);

		if (!RegisterClassExW(&wndclass))
		{
			SW_CORE_WARNING("Failed to Register Window Class");
			DBG_BREAK();
			return false;
		}
	}
	//client rectangle calculation
	m_size.height = prop.height;
	m_size.width = prop.width;
	m_position.x = prop.luX;
	m_position.y = prop.luY;


	RECT newRect;
	newRect.left = prop.luX;
	newRect.right = prop.luX + prop.width;
	newRect.top = prop.luY;
	newRect.bottom = prop.luY + prop.height;
	AdjustWindowRectEx(&newRect, WS_OVERLAPPEDWINDOW, NULL, NULL);

	m_wnd = CreateWindowExW(NULL, SW_MAIN_APP_WND_CLASS_NAME, prop.title.c_str(), WS_OVERLAPPEDWINDOW,
							newRect.left, newRect.top,//position
							newRect.right - newRect.left,//width
							newRect.bottom - newRect.top,//height
							NULL, NULL, NULL, this);

	if (m_wnd == NULL)
	{
		SW_CORE_WARNING("failed to create window");
		DBG_BREAK();
		return false;
	}
	
	ShowWindow(m_wnd, SW_NORMAL);
	UpdateWindow(m_wnd);

	return true;
}

void StepWay::Win32Window::Destroy()
{
	DestroyWindow(m_wnd);
}

void StepWay::Win32Window::OnUpdate()
{
	PollEvents();
}

std::wstring StepWay::Win32Window::GetTitle() const
{
	return m_title;
}

int StepWay::Win32Window::GetX() const
{
	return m_position.x;
}

int StepWay::Win32Window::GetY() const
{
	return m_position.y;
}

int StepWay::Win32Window::GetWidth() const
{
	return m_size.width;
}

int StepWay::Win32Window::GetHeight() const
{
	return m_size.height;
}

void StepWay::Win32Window::Resize(int width, int height)
{
	SW_ERROR("Resize is not done yet");
}

void StepWay::Win32Window::SetPosition(int x, int y)
{
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

void StepWay::Win32Window::Close()
{
	DestroyWindow(m_wnd);
}

void StepWay::Win32Window::SetEventCallback(const EventCallback & callback)
{
	m_callback = callback;
}

void StepWay::Win32Window::PollEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, m_wnd, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

