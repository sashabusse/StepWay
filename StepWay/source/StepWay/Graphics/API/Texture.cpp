#include "StepWayPCH.h"
#include "Texture.h"
#include "OpenGL/GLTexture.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			//chek for api support for os later but the better way would be to make factory that will know
			Texture* Texture::Create(GAPI_TYPE api)
			{
				Texture* ret;
				switch (api)
				{
				case GAPI_TYPE::OPENGL:
					ret = (Texture*)SW_NEW OpenGL::GLTexture();
					break;
				default:
					SW_CORE_ASSERT(false, "not supported api for VertexBuffer");
					break;
				}
				return ret;
			}


		}
	}
}