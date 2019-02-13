#pragma once
#include "Core.h"
#include "GraphicsConfig.h"
#include "Window.h"

namespace StepWay
{
	namespace graphics
	{
		namespace API
		{

			class SW_API Context
			{
			private:
				static Context* CurrentContext;
				static GraphicsAPIType CurrentContextType;
			public:
				//Singleton Interface remove later
				static Context* GetContextPtr();
				static Context& GetContext();

				static bool CreateNew(GraphicsAPIType type);
				static void ReleaseGlobal();
				
				virtual void SetRenderTarget(::StepWay::Window* wnd) = 0;
				virtual void Present() = 0;

				virtual bool Init() = 0;
				virtual void Destroy() = 0;

				virtual ~Context() {};

			};

		}

	}
}
