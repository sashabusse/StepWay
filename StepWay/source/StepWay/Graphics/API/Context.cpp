#include "StepWayPCH.h"
#include "Context.h"

//WinHeaders
#ifdef SW_PLATFORM_WINDOWS
#include "../Platform/Win32/OpenGL/GLContext.h"
#endif



namespace StepWay
{
	namespace graphics
	{
		namespace API
		{


			Context::Context(GraphicsAPIType type) :
				m_type(type)
			{
			}


			Context * StepWay::graphics::API::Context::Create(GraphicsAPIType type)
			{
				switch (type)
				{
#ifdef SW_PLATFORM_WINDOWS //gl windows only for now
				case StepWay::graphics::API::GraphicsAPIType::OPENGL:	return new platform::GLContext(type);
#endif // DEBUG
				}

				SW_CORE_WARNING("wrong API type in RenderingAPI::Create");
				SW_CORE_ASSERT(false, "wrong API type");
				return nullptr;
			}

			GraphicsAPIType Context::GetType() const
			{
				return m_type;
			}

			ContextBinding::ContextBinding(GraphicsAPIType type) :
				m_type(type)
			{
			}

		}
	}
}