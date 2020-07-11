#pragma once
#include "Core.h"
#include "Graphics/API/Texture.h"
#include "glad/glad.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{
			//for now it's supposed to be only 2D texture
			class GLTexture : public Graphics::API::Texture
			{
			public:
				GLTexture();

				void SetUp(std::string filename) override;
				void SetUp(int width, int height, PixelFormat format, void* data) override;
				void SetUp(int width, int height, PixelFormat format) override;
				void ShutDown() override;
				
				void Bind() override;
				void Unbind() override;

				void LoadData(int width, int height, PixelFormat format, void* data) override;

				void SetToTexUnit(int num) override;
				void SetToImgUnit(int num) override;

				void SetMagFilter(Filter filter) override;
				void SetMinFilter(Filter filter) override;

				void SetWrapModeS(WrapMode mode) override;
				void SetWrapModeT(WrapMode mode) override;

				virtual ~GLTexture() {};
			private:
				void loadImageByName(std::string filename);
				GLenum UnitNumToGLenum(int num);
				void PixFormatToGLFormats(PixelFormat format, GLenum& gl_internal_format, GLenum& gl_pixel_format, GLenum& gl_data_type);
			private:
				uint m_id;
				PixelFormat m_format;
			};


		}
	}
}
