#include "StepWayPCH.h"
#include "RenderingAPI.h"
#include "OpenGL/GLRenderingAPI.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			RenderingAPI* RenderingAPI::Create(GAPI_TYPE api)
			{
				switch (api)
				{
				case StepWay::Graphics::API::GAPI_TYPE::OPENGL:
					return SW_NEW OpenGL::GLRenderingAPI();
					break;
				default:
					SW_CORE_ASSERT(false, "Cant create RenderingAPI for such api");
					break;
				}
				SW_CORE_ASSERT(false, "Cant create RenderCommand for such api");
				return nullptr;
			}

		}
	}
}