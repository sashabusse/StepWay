#include "StepWayPCH.h"
#include "Context.h"


namespace StepWay
{	namespace Graphics
	{	namespace API
		{



	GraphicsContext * StepWay::Graphics::API::GraphicsContext::Create(GAPI_TYPE type, Window* window)
	{
		if (type == GAPI_TYPE::OPENGL)
		{
			return CreateGLContext(window);
		}
		return nullptr;
	}

	void GraphicsContext::Destroy(GraphicsContext* context)
	{
		delete context;
	}

}}}
