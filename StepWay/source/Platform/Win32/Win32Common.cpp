#include "StepWayPCH.h"
#include "Win32Common.h"


namespace StepWay
{
	namespace  Utility
	{


		HWND DummyWindow()
		{
#define SW_DUMMY_WINDOW_CLASS_NAME L"MyDummyClass"

			WNDCLASSEX wndclass;
			if (!GetClassInfoExW(GetModuleHandle(NULL), SW_DUMMY_WINDOW_CLASS_NAME, &wndclass))
			{
				SW_CORE_ASSERT(GetLastError() == ERROR_CLASS_DOES_NOT_EXIST, "unexpected error in GetClassInfoExW");
				if (GetLastError() != ERROR_CLASS_DOES_NOT_EXIST)
				{
					SW_CORE_WARNING("GetClassInfoExW Set unexpected error");
				}


				memset(&wndclass, 0, sizeof(wndclass));
				//filling in
				wndclass.cbSize = sizeof(wndclass);
				wndclass.lpfnWndProc = DefWindowProc;
				wndclass.lpszClassName = SW_DUMMY_WINDOW_CLASS_NAME;
				wndclass.hInstance = NULL;
				wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);
				wndclass.hIcon = LoadIconW(NULL, IDI_APPLICATION);


				if (!RegisterClassExW(&wndclass))
				{
					SW_CORE_WARNING("Failed to Register Window Class");
					DBG_BREAK();
					return NULL;
				}
			}

			HWND wnd = CreateWindowExW(NULL, SW_DUMMY_WINDOW_CLASS_NAME, L"title", NULL,
				0, 0,//position
				100,//width
				100,//height
				NULL, NULL, NULL, NULL);

			if (wnd == NULL)
			{
				SW_CORE_WARNING("failed to create window");
				DBG_BREAK();
				return NULL;
			}
			return wnd;
		}

		void DeleteDummyWindow(HWND hwnd)
		{

			DestroyWindow(hwnd);
			//may be poll events to get quit event
			UnregisterClassW(SW_DUMMY_WINDOW_CLASS_NAME, NULL);
		}


	}
}