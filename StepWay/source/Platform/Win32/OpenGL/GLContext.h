#pragma once
#include "Graphics/API/Context.h"

#ifdef SW_PLATFORM_WINDOWS
#include <Windows.h>
#include "../Win32Common.h"
#else
#error opengl is only for windows now
#endif


namespace StepWay
{
	namespace graphics
	{
		namespace API
		{

			class GLContext : public Context
			{
			public:

				bool Init() override;
				void Destroy() override;


				void SetRenderTarget(::StepWay::Window* wnd) override;
				void Present() override;


				~GLContext() override;

			private:
				HGLRC m_hGLContext;

				HDC m_CurTarget;
			};

		}

	}
}
