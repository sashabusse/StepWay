#pragma once
#include "Graphics/API/Context.h"
#include <Windows.h>

namespace StepWay
{
	namespace Win32
	{

		//forward declaration for Context binding
		class Win32Window;

}}

namespace StepWay
{	namespace graphics
	{	namespace API
		{	namespace platform
			{


				//Win32 Realization of OpenGL context
				class GLContext :public Context
				{
				public:
					SW_DECLARE_CONTEXT_TYPE(GraphicsAPIType::OPENGL);

					GLContext(GraphicsAPIType type);

					bool SetUp() override;
					void ShutDown() override;

					void SetRenderTarget(HDC wndDC);

					const PIXELFORMATDESCRIPTOR& GetPFD() const;
					int GetPixFormat() const;

				private:
					HGLRC m_hGLContext;
					PIXELFORMATDESCRIPTOR m_pfd;
					int m_wndPixFormat;
				};



				//Win32 Realization of OpenGL window binding
				class GLContextBinding : public ContextBinding
				{
				public:
					SW_DECLARE_CONTEXT_BINDING_TYPE(GraphicsAPIType::OPENGL);

					GLContextBinding(Win32::Win32Window* wnd, GLContext* context);

					void Present() override;
					void MakeCurrent() override;
				private:
					HDC m_wndDC;
					GLContext* m_GLContext;
					Win32::Win32Window* m_wnd;
				};


}}}}//closing all namespaces
