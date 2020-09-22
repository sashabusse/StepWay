#include "StepWayPCH.h"
#include "GLContext.h"
#include "glad/glad.h"
#include "OpenGL/ErrorHandling.h"

namespace StepWay
{	namespace Graphics
	{

	API::GraphicsContext* API::GraphicsContext::CreateGLContext(Window* window)
	{
		return SW_NEW OpenGL::Win32::GLContext((Win32::Win32Window*)window);
	}

	namespace OpenGL
	{	namespace Win32
		{


		using StepWay::Win32::Win32Window;
		GLContext::GLContext(Win32Window* window):
			m_pWindow(window),
			m_GLNativeContext(NULL)
		{
		}

		void GLContext::ResizeViewport(int x, int y, int width, int height)
		{
			glViewport(x, y, width, height);
			GL_CHECK_ERRORS();
		}

		void GLContext::SetUp()
		{
			SW_CORE_ASSERT(m_pWindow != NULL && m_pWindow->IsInitialized(), "invalid Window");
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
			HDC windowDC = m_pWindow->GetDC();
			SW_CORE_ASSERT(windowDC != NULL, "Window returned NULL DC");
			int pixFormatNum = ChoosePixelFormat(windowDC, &pfd);
			SW_CORE_ASSERT(pixFormatNum != 0, "wrong pixel format");
			bool spf_ret = SetPixelFormat(windowDC, pixFormatNum, &pfd);
			SW_CORE_ASSERT(spf_ret, "failed set pixel format");

			m_GLNativeContext = wglCreateContext(windowDC);
			SW_CORE_ASSERT(m_GLNativeContext != NULL, "failed create context");
			MakeCurrent();
			int glad_load_res = gladLoadGL();
			SW_CORE_ASSERT(glad_load_res != 0, "failed to load glad");

			//some settings here
			glEnable(GL_DEPTH_TEST);

		}

		void GLContext::ShutDown()
		{
			if (wglGetCurrentContext() == m_GLNativeContext)
				wglMakeCurrent(m_pWindow->GetDC(), NULL);
			wglDeleteContext(m_GLNativeContext);
			m_GLNativeContext = NULL;
		}

		//May be save a bit of time caching DC
		void GLContext::SwapBuffers()
		{
			bool success = ::SwapBuffers(m_pWindow->GetDC());
			if (!success)
			{
				DWORD err = GetLastError();
				DBG_BREAK();
			}
			SW_CORE_ASSERT(success, "failed swap buffer");
		}

		//May be a save bit of time caching DC
		void GLContext::MakeCurrent()
		{
			bool success = wglMakeCurrent(m_pWindow->GetDC(), m_GLNativeContext);
			SW_CORE_ASSERT(success, "failed to make context current");
		}


}}}}