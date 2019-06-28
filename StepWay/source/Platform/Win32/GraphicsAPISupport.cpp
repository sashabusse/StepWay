#pragma once
#include "StepWayPCH.h"
#include "Graphics/API/Context.h"


namespace StepWay
{	namespace Graphics
	{	namespace API
		{
		

	bool GraphicsContext::IsAPISupportedByOS(GAPI_TYPE type)
	{
		if (type == GAPI_TYPE::OPENGL)return true;
		return false;
	}


}}}