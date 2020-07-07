#pragma once
#include "Core.h"
#include "Context.h"
#include "glm/glm.hpp"

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			class Texture
			{
			public:
				enum class PixelFormat : int
				{
					R8_I = 0,
					RG8_I,
					RGB8_I,
					RGBA8_I,

					R16_I,
					RG16_I,
					RGBA16_I,

					R16_F,
					RG16_F,
					RGB16_F,
					RGBA16_F,

					R32_F,
					RG32_F,
					RGB32_F,
					RGBA32_F

					//add more if needed later
				};
				virtual void SetUp(std::string filename) = 0;//PixelFormat??
				virtual void SetUp(int width, int height, PixelFormat format) = 0;
				//should be done later
				//virtual void SetUp(int width, int height, glm::vec4 col) = 0;
				virtual void ShutDown() = 0;

				virtual void Bind() = 0;
				virtual void Unbind() = 0;
				
				virtual void SetToTexUnit(int num) = 0;
				virtual void SetToImgUnit(int num) = 0;

				//different settings
				enum class Filter : int
				{
					NEAREST = 0,
					LINEAR
				};
				virtual void SetMagFilter(Filter filter) = 0;
				virtual void SetMinFilter(Filter filter) = 0;

				enum class WrapMode : int
				{
					CLAMP_TO_EDGE = 0,
					REPEAT,
					MIRRORED_REPEAT
				};
				virtual void SetWrapModeS(WrapMode mode) = 0;
				virtual void SetWrapModeT(WrapMode mode) = 0;

				static Texture* Create(GAPI_TYPE api);
				virtual ~Texture() {};
			private:
			public:
				
			private:
			};
		}
	}
}