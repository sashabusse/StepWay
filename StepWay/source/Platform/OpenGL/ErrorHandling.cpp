#include "StepWayPCH.h"
#include "ErrorHandling.h"
#include "glad/glad.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			std::string GLErrCodeToString(uint32 ErrCode)
			{
				switch (ErrCode)
				{
				case GL_NO_ERROR:  return "GL_NO_ERROR";
				case GL_INVALID_ENUM:  return "GL_INVALID_ENUM";
				case GL_INVALID_VALUE:  return "GL_INVALID_VALUE";
				case GL_INVALID_OPERATION:  return "GL_INVALID_OPERATION";
				case GL_OUT_OF_MEMORY:  return "GL_OUT_OF_MEMORY";
				}
				SW_CORE_ASSERT(false, "Unknown GL error");
				return std::string();
			}
			

		}
	}
}