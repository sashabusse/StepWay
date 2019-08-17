#include "StepWayPCH.h"
#include "RenderingCommands.h"
#include "OpenGL/GLRenderingCommands.h"


#include "glad/glad.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			RenderCommand * RenderCommand::Create(GAPI_TYPE api)
			{
				switch (api)
				{
				case StepWay::Graphics::API::GAPI_TYPE::OPENGL:
					return SW_NEW OpenGL::GLRenderCommand();
					break;
				default:
					SW_CORE_ASSERT(false, "Cant create RenderCommand for suc api");
					break;
				}
				SW_CORE_ASSERT(false, "Cant create RenderCommand for suc api");
				return nullptr;
			}

		}
	}
}