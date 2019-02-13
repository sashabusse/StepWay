#include "StepWayPCH.h"
#include "GLContext.h"
#include "../Win32Window.h"
#include "../../vendor/glad/include/glad/glad.h"


//for now just for windows
bool StepWay::graphics::API::GLContext::Init()
{
	HWND wnd = StepWay::Utility::DummyWindow();

	SW_CORE_ASSERT(wnd != NULL, "invalid HWND");

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC wdc = GetDC(wnd);

	int  wndPixFormat = ChoosePixelFormat(wdc, &pfd);
	SW_CORE_ASSERT(wndPixFormat != 0, "wrong pixel format index");

	SetPixelFormat(wdc, wndPixFormat, &pfd);

	m_hGLContext = wglCreateContext(wdc);

	SW_CORE_ASSERT(m_hGLContext != NULL, "failed to create context");

	//just for now text without it later
	wglMakeCurrent(wdc, m_hGLContext);


	//unbinding window from context
	wglMakeCurrent(NULL, m_hGLContext);

	StepWay::Utility::DeleteDummyWindow(wnd);

	return true;
}

void StepWay::graphics::API::GLContext::Destroy()
{
	if (m_hGLContext == NULL)
	{
		SW_WARNING("attemp to destroy NULL context");
		return;
	}
	wglMakeCurrent(NULL, m_hGLContext);
	wglDeleteContext(m_hGLContext);
}

void StepWay::graphics::API::GLContext::SetRenderTarget(::StepWay::Window * wnd)
{
	SW_CORE_ASSERT(wnd != nullptr, "invalid ptr");
	Win32Window* winWND = reinterpret_cast<Win32Window*>(wnd);
	m_CurTarget = GetDC(winWND->GetHWND());
	bool res = wglMakeCurrent(m_CurTarget, m_hGLContext);
	//HRESULT tmp = HRESULT_FROM_WIN32(GetLastError());
	//SW_CORE_ASSERT(res == TRUE, "failed make current");
}

void StepWay::graphics::API::GLContext::Present()
{
	SW_CORE_ASSERT(m_CurTarget != NULL, "no actual render target");
}

StepWay::graphics::API::GLContext::~GLContext()
{
}
