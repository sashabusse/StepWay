#pragma once



namespace StepWay
{
	namespace graphics
	{

#define SW_DEFAULT_GR_API	::StepWay::graphics::GraphicsAPIType::OPENGL

		enum class GraphicsAPIType : int
		{
			NONE = 0,
			OPENGL,
			DIRECTX11
		};


	}
}

