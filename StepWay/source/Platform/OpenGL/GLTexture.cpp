#include "StepWayPCH.h"
#include "GLTexture.h"
#include "glad/glad.h"
#include "ErrorHandling.h"
#include "stb_image.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{
			GLTexture::GLTexture():
				m_id(0)
			{
			}

			void GLTexture::SetUp(std::string filename)
			{
				glActiveTexture(GL_TEXTURE0);

				glGenTextures(1, &m_id);
				Bind();

				SetWrapModeS(WrapMode::REPEAT);
				SetWrapModeT(WrapMode::REPEAT);
				SetMinFilter(Filter::LINEAR);
				SetMagFilter(Filter::LINEAR);

				loadImageByName(filename);
				//glGenerateMipmap(GL_TEXTURE_2D);

			}

			//use data = NULL for empty array
			void GLTexture::SetUp(int width, int height, PixelFormat format, void* data)
			{
				glActiveTexture(GL_TEXTURE0);

				glGenTextures(1, &m_id);
				Bind();

				SetWrapModeS(WrapMode::REPEAT);
				SetWrapModeT(WrapMode::REPEAT);
				SetMinFilter(Filter::LINEAR);
				SetMagFilter(Filter::LINEAR);

				LoadData(width, height, format, data);
			}

			void GLTexture::SetUp(int width, int height, PixelFormat format)
			{
				SetUp(width, height, format, NULL);
			}

			void GLTexture::ShutDown()
			{
				glDeleteTextures(1, &m_id);
				GL_CHECK_ERRORS();
			}

			void GLTexture::Bind()
			{
				glBindTexture(GL_TEXTURE_2D, m_id);
				GL_CHECK_ERRORS()
			}

			void GLTexture::Unbind()
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				GL_CHECK_ERRORS();
			}

			void GLTexture::LoadData(int width, int height, PixelFormat format, void* data)
			{
				m_format = format;

				GLenum gl_int_format = 0;
				GLenum gl_pix_format = 0;
				GLenum gl_data_type = 0;

				PixFormatToGLFormats(format, gl_int_format, gl_pix_format, gl_data_type);

				Bind();
				glTexImage2D(GL_TEXTURE_2D, 0, gl_int_format, width, height, 0, gl_pix_format, gl_data_type, data);
				GL_CHECK_ERRORS();
			}

			//0 is reserved for common temporal purposes
			//all the temporal textures are set to the 0 as default
			void GLTexture::SetToTexUnit(int num)
			{
				glActiveTexture(UnitNumToGLenum(num));
				Bind();
			}

			void GLTexture::SetToImgUnit(int num)
			{

				GLenum gl_int_format = 0;
				GLenum gl_pix_format = 0;
				GLenum gl_data_type = 0;

				PixFormatToGLFormats(m_format, gl_int_format, gl_pix_format, gl_data_type);

				//custom formats should be involved for the last 2 arguments
				glBindImageTexture(num, m_id, 0, GL_FALSE, 0, GL_READ_WRITE, gl_int_format);
				GL_CHECK_ERRORS();
			}

			void GLTexture::SetMagFilter(Filter filter)
			{
				switch (filter)
				{
				case Filter::NEAREST:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					break;
				case Filter::LINEAR:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					break;
				default:
					SW_ASSERT(false, "INVALID MAG FILTER");
					break;
				}
				GL_CHECK_ERRORS();
				return;
			}

			void GLTexture::SetMinFilter(Filter filter)
			{
				switch (filter)
				{
				case Filter::NEAREST:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					break;
				case Filter::LINEAR:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					break;
				default:
					SW_ASSERT(false, "INVALID MIN FILTER");
					break;
				}
				GL_CHECK_ERRORS();
				return;
			}

			void GLTexture::SetWrapModeS(WrapMode mode)
			{
				switch (mode)
				{
				case WrapMode::CLAMP_TO_EDGE:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					break;
				case WrapMode::REPEAT:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					break;
				case WrapMode::MIRRORED_REPEAT:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					break;
				default:
					SW_ASSERT(false, "INVALID WRAP MODE");
					break;
				}
				GL_CHECK_ERRORS();
				return;
			}

			void GLTexture::SetWrapModeT(WrapMode mode)
			{
				switch (mode)
				{
				case WrapMode::CLAMP_TO_EDGE:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					break;
				case WrapMode::REPEAT:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					break;
				case WrapMode::MIRRORED_REPEAT:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
					break;
				default:
					SW_ASSERT(false, "INVALID WRAP MODE");
					break;
				}
				GL_CHECK_ERRORS();
				return;
			}

			void GLTexture::loadImageByName(std::string filename)
			{
				int width, height, nrChannels;
				unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

				SW_ASSERT(data != 0, "can't load image");

				PixelFormat format = PixelFormat::RGB8_I;

				LoadData(width, height, format, data);
				//Bind();
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//GL_CHECK_ERRORS();

				stbi_image_free(data);
			}

			GLenum GLTexture::UnitNumToGLenum(int num)
			{
				switch (num)
				{
				case 0: return GL_TEXTURE0;
				case 1: return GL_TEXTURE1;
				case 2: return GL_TEXTURE2;
				case 3: return GL_TEXTURE3;
				case 4: return GL_TEXTURE4;
				case 5: return GL_TEXTURE5;
				case 6: return GL_TEXTURE6;
				case 7: return GL_TEXTURE7;
				case 8: return GL_TEXTURE8;
				case 9: return GL_TEXTURE9;

				default:
					return GL_TEXTURE0;
				}
				
				GL_CHECK_ERRORS();
				DBG_BREAK();
				return GL_TEXTURE0;
			}

			void GLTexture::PixFormatToGLFormats(PixelFormat format, GLenum& gl_internal_format, GLenum& gl_pixel_format, GLenum& gl_data_type)
			{
				switch (format)
				{
				case StepWay::Graphics::API::Texture::PixelFormat::R8_I:
					gl_internal_format = GL_R8;
					gl_pixel_format = GL_RED;
					gl_data_type = GL_UNSIGNED_BYTE;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RG8_I:
					gl_internal_format = GL_RG8;
					gl_pixel_format = GL_RG;
					gl_data_type = GL_UNSIGNED_BYTE;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGB8_I:
					gl_internal_format = GL_RGB8;
					gl_pixel_format = GL_RGB;
					gl_data_type = GL_UNSIGNED_BYTE;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGBA8_I:
					gl_internal_format = GL_RGBA8;
					gl_pixel_format = GL_RGBA;
					gl_data_type = GL_UNSIGNED_BYTE;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::R16_I:
					gl_internal_format = GL_R16;
					gl_pixel_format = GL_RED;
					gl_data_type = GL_INT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RG16_I:
					gl_internal_format = GL_RG16;
					gl_pixel_format = GL_RG;
					gl_data_type = GL_INT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGBA16_I:
					gl_internal_format = GL_RGB16;
					gl_pixel_format = GL_RGB;
					gl_data_type = GL_INT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::R16_F:
					gl_internal_format = GL_R16F;
					gl_pixel_format = GL_RED;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RG16_F:
					gl_internal_format = GL_RG16F;
					gl_pixel_format = GL_RG;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGB16_F:
					gl_internal_format = GL_RGB16F;
					gl_pixel_format = GL_RGB;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGBA16_F:
					gl_internal_format = GL_RGBA16F;
					gl_pixel_format = GL_RGBA;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::R32_F:
					gl_internal_format = GL_R32F;
					gl_pixel_format = GL_RED;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RG32_F:
					gl_internal_format = GL_RG32F;
					gl_pixel_format = GL_RG;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGB32_F:
					gl_internal_format = GL_RGB32F;
					gl_pixel_format = GL_RGB;
					gl_data_type = GL_FLOAT;
					break;
				case StepWay::Graphics::API::Texture::PixelFormat::RGBA32_F:
					gl_internal_format = GL_RGBA32F;
					gl_pixel_format = GL_RGBA;
					gl_data_type = GL_FLOAT;
					break;
				default:
					SW_ASSERT(false, "WRONG PIXEL FORMAT");
					break;
				}
			}
		}
	}
}