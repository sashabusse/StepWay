#pragma once
#include "Core.h"
#include "glad/glad.h"

#define GL_CHECK_ERRORS()\
{\
GLenum err = glGetError();\
 SW_CORE_ASSERT(err==GL_NO_ERROR,"gl failed at {0}:{1}\n\t{2}\n\terror code: {3}(0x{4:x})",\
				 __FILE__, __LINE__, __FUNCTION__, GLErrCodeToString(err),err);\
}

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