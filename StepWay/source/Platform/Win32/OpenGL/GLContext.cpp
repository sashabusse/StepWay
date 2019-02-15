#include "StepWayPCH.h"
#include "GLContext.h"
#include "../Win32Window.h"
#include "../Win32Common.h"
#include "../../vendor/glad/include/glad/glad.h"


namespace StepWay
{
	namespace graphics
	{
		namespace platform
		{

			GLContext::GLContext(API::GraphicsAPIType type) :
				Context(type),
				m_hGLContext(NULL)
			{
				SW_CORE_ASSERT(type == API::GraphicsAPIType::OPENGL, "creating opengl with wrong type");
			}


			//add error checking
			bool GLContext::SetUp()
			{

				HWND wnd = Utility::DummyWindow();

				m_pfd =
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

				m_wndPixFormat = ChoosePixelFormat(wdc, &m_pfd);
				SW_CORE_ASSERT(m_wndPixFormat != 0, "wrong pixel format index");

				SetPixelFormat(wdc, m_wndPixFormat, &m_pfd);

				m_hGLContext = wglCreateContext(wdc);

				SW_CORE_ASSERT(m_hGLContext != NULL, "failed to create context");

				//just for now text without it later
				wglMakeCurrent(wdc, m_hGLContext);

				int gladResult = gladLoadGL();
				SW_CORE_ASSERT(gladResult != 0, "failed intialize glad");

				wglMakeCurrent(NULL, m_hGLContext);

				Utility::DeleteDummyWindow(wnd);

				return true;
			}

			void GLContext::ShutDown()
			{
				wglMakeCurrent(NULL, m_hGLContext);
				wglDeleteContext(m_hGLContext);
				m_hGLContext = NULL;
			}

			void GLContext::SetRenderTarget(HDC wndDC)
			{
				SW_CORE_ASSERT(m_hGLContext != NULL, "unitialized context");
				wglMakeCurrent(wndDC, m_hGLContext);//check for success here
			}

			PIXELFORMATDESCRIPTOR GLContext::GetPFD() const//may be const ref as return
			{
				return m_pfd;
			}

			int GLContext::GetPixFormat() const
			{
				return m_wndPixFormat;
			}


			GLContextBinding::GLContextBinding(Win32Window * wnd, GLContext * context):
				ContextBinding(context->GetType()),//may be dereferencing nullptr
				m_GLContext(context),
				m_wndDC(GetDC(wnd->GetHWND())),//may be add GetDC later but consider Win32 api GetDC and better name
				m_wnd(wnd)
			{
				PIXELFORMATDESCRIPTOR tmpPFD = context->GetPFD();
				SetPixelFormat(m_wndDC, context->GetPixFormat(), &tmpPFD);
			}

			void GLContextBinding::Present()
			{
				SwapBuffers(m_wndDC);
			}

			void GLContextBinding::MakeCurrent()
			{
				m_GLContext->SetRenderTarget(m_wndDC);
				glViewport(0, 0, m_wnd->GetWidth(), m_wnd->GetHeight());
			}

		}
	}
}