#pragma once
#include "Core.h"
#include "Graphics/API/Context.h"
#include "Win32/Win32Window.h"

namespace StepWay
{	namespace Graphics
	{	namespace OpenGL
		{	namespace Win32
			{

	using StepWay::Win32::Win32Window;
			
	class GLContext : public API::GraphicsContext
	{
	public:
		SW_DECLARE_GAPI_TYPE(API::GAPI_TYPE::OPENGL);

		GLContext(Win32Window* winow);

		virtual void SetUp() override;
		virtual void ShutDown() override;
		virtual void SwapBuffers() override;
		virtual void MakeCurrent() override;

	private:
		Win32Window* m_pWindow;
		HGLRC m_GLNativeContext;
	};



}}}}