#pragma once
#include "Core.h"
#include "glad/glad.h"

#ifdef SW_DEBUG
#define GL_CHECK_ERRORS()\
{\
GLenum err = glGetError();\
 SW_CORE_ASSERT(err==GL_NO_ERROR,"gl failed error code: {0}(0x{1:x})",\
				 StepWay::Graphics::OpenGL::GLErrCodeToString(err),err);\
}
#else
#define GL_CHECK_ERRORS()
#endif

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			std::string GLErrCodeToString(uint32 ErrCode);

		}
	}
}