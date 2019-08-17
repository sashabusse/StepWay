#include "StepWayPCH.h"
#include "Shader.h"
#include "OpenGL/GLShader.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			Shader * Shader::Create(GAPI_TYPE api)
			{
				switch (api)
				{
				case GAPI_TYPE::OPENGL:
					return SW_NEW OpenGL::GLShader();
					break;
				default:
					SW_CORE_ASSERT(false, "no shader creator for such api");
					break;
				}
				return nullptr;
			}

		}
	}
}

