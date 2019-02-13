#include "StepWayPCH.h"
#include "Context.h"
#include "Memory/Memory.h"
#include "../Platform/Win32/OpenGL/GLContext.h"



namespace StepWay
{
	namespace graphics
	{
		namespace API
		{

			Context* Context::CurrentContext = nullptr;
			GraphicsAPIType Context::CurrentContextType = GraphicsAPIType::NONE;
			

			Context * Context::GetContextPtr()
			{
				return CurrentContext;
			}

			Context & Context::GetContext()
			{
				SW_CORE_ASSERT(CurrentContext != nullptr, "trying to get unitialized singleton");
				return *CurrentContext;
			}

			bool Context::CreateNew(GraphicsAPIType type)
			{

				Context* NewContext = nullptr;
				switch (type)
				{

#ifdef SW_PLATFORM_WINDOWS//gl windows only now
				case StepWay::graphics::GraphicsAPIType::OPENGL:
					NewContext = SW_NEW GLContext;
					break;
#endif

#ifdef SW_PLATFORM_WINDOWS//diret windows only
				case StepWay::graphics::GraphicsAPIType::DIRECTX11:
					SW_CORE_ASSERT(false, "directX not Available yet");
					break;
#endif

				default:
					SW_CORE_ASSERT(false, "wrong API type");
					return false;
					break;
				}
				SW_CORE_ASSERT(NewContext != nullptr, "nullptr failure");
				if (NewContext == nullptr) return false;

				if (CurrentContext != nullptr)
				{
					CurrentContext->Destroy();
					SW_DELETE CurrentContext;
				}

				CurrentContext = NewContext;
				CurrentContextType = type;

				return true;
			}

			void Context::ReleaseGlobal()
			{
				CurrentContextType = GraphicsAPIType::NONE;
				if (CurrentContext == nullptr)
				{
					SW_CORE_WARNING("attemp to Release Context while not exist");
					return;
				}
				CurrentContext->Destroy();
				SW_DELETE CurrentContext;
				CurrentContext = nullptr;
			}

		}
	}
}