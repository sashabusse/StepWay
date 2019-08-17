#include "StepWayPCH.h"
#include "VertexArray.h"
#include "OpenGL/GLVertexArray.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			VertexArray * StepWay::Graphics::API::VertexArray::Create(GAPI_TYPE type)
			{
				switch (type)
				{
				case GAPI_TYPE::OPENGL: return SW_NEW OpenGL::GLVertexArray();
				}
				SW_CORE_ASSERT(false, "VertexArray cant be created for this GAPI");
				return nullptr;
			}



		}
	}
}
