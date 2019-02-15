#pragma once
#include "Graphics/API/Context.h"
#include <Windows.h>

namespace StepWay
{
	//forward declaration for Context binding
	class Win32Window;

	namespace graphics
	{
		namespace platform
		{

			class GLContext :public API::Context
			{
			public:
				GLContext(API::GraphicsAPIType type);

				bool SetUp() override;
				void ShutDown() override;
				
				void SetRenderTarget(HDC wndDC);

				PIXELFORMATDESCRIPTOR GetPFD() const;//may be return const reference
				int GetPixFormat() const;//rework this two methods

			private:
				HGLRC m_hGLContext;
				PIXELFORMATDESCRIPTOR m_pfd;
				int m_wndPixFormat;
			};

			

			class GLContextBinding : public API::ContextBinding
			{
			public:
				GLContextBinding(Win32Window* wnd, GLContext* context);

				void Present() override;
				void MakeCurrent() override;
			private:
				HDC m_wndDC;
				GLContext* m_GLContext;
				Win32Window* m_wnd;
			};
		}
	}
}
