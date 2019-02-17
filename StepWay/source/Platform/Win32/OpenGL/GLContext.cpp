#include "StepWayPCH.h"
#include "GLContext.h"
#include "Win32/Win32Window.h"
#include "Win32/Win32Common.h"
#include "glad/glad.h"


namespace StepWay
{	namespace graphics
	{	namespace API
		{	namespace platform
			{


				GLContext::GLContext(API::GraphicsAPIType type) :
					Context(),
					m_hGLContext(NULL)
				{
					SW_CORE_ASSERT(type == API::GraphicsAPIType::OPENGL, "creating opengl with wrong type");
				}


				//add error checking
				bool GLContext::SetUp()
				{

					HWND wnd = Win32::Util::DummyWindow();

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

					bool setResult = SetPixelFormat(wdc, m_wndPixFormat, &m_pfd);
					SW_CORE_ASSERT(setResult == TRUE, "failed set pixel format");

					m_hGLContext = wglCreateContext(wdc);
					SW_CORE_ASSERT(m_hGLContext != NULL, "failed to create context");

					bool mkCurResult = wglMakeCurrent(wdc, m_hGLContext);
					SW_CORE_ASSERT(mkCurResult == TRUE, "failed make current dummy wnd");

					int gladResult = gladLoadGL();
					SW_CORE_ASSERT(gladResult != 0, "failed intialize glad");

					wglMakeCurrent(NULL, m_hGLContext);

					//Clearing
					Win32::Util::DeleteDummyWindow(wnd);

					return true;
				}


				void GLContext::ShutDown()
				{
					wglMakeCurrent(NULL, m_hGLContext);
					wglDeleteContext(m_hGLContext);

					m_hGLContext = NULL;
					m_wndPixFormat = 0;
				}

				void GLContext::SetRenderTarget(HDC wndDC)
				{
					SW_CORE_ASSERT(m_hGLContext != NULL, "unitialized context");

					bool mkCureResult = wglMakeCurrent(wndDC, m_hGLContext);
					SW_CORE_ASSERT(mkCureResult == TRUE, "failed to make current");
				}

				const PIXELFORMATDESCRIPTOR& GLContext::GetPFD() const
				{
					return m_pfd;
				}

				int GLContext::GetPixFormat() const
				{
					return m_wndPixFormat;
				}


				GLContextBinding::GLContextBinding(Win32::Win32Window * wnd, GLContext * context) :
					ContextBinding(),
					m_GLContext(context),
					m_wnd(wnd)
				{
					//param assert
					SW_CORE_ASSERT(m_wnd != nullptr, "null wnd");
					SW_CORE_ASSERT(m_GLContext != nullptr, "null context");

					m_wndDC = GetDC(wnd->GetHWND());
					SW_CORE_ASSERT(m_wndDC != NULL, "failed get DC");

					PIXELFORMATDESCRIPTOR tmpPFD = context->GetPFD();

					bool setResult = SetPixelFormat(m_wndDC, context->GetPixFormat(), &tmpPFD);
					SW_CORE_ASSERT(setResult == TRUE, "failed set Pixel format");
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

}}}}//closing namespaces