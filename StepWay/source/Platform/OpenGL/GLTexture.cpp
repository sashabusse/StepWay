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
			GLTexture::GLTexture()
			{
				
			}

			void GLTexture::SetUp(std::string filename)
			{
				glActiveTexture(GL_TEXTURE0);

				glGenTextures(1, &m_id);
				Bind();

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				loadImageByName(filename);
				glGenerateMipmap(GL_TEXTURE_2D);

			}

			void GLTexture::SetUp(int width, int height)
			{
				glActiveTexture(GL_TEXTURE0);

				glGenTextures(1, &m_id);
				Bind();

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
				// here it is for compute shaders need move somewhere later
				glBindImageTexture(0, m_id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
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

			//0 is reserved for common temporal purposes
			//all the temporal textures are set to the 0 as default
			void GLTexture::SetToUnit(int num)
			{
				glActiveTexture(UnitNumToGLenum(num));
				Bind();
			}

			void GLTexture::loadImageByName(std::string filename)
			{
				int width, height, nrChannels;
				unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

				SW_ASSERT(data != 0, "can't load image");

				Bind();
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				GL_CHECK_ERRORS();

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
		}
	}
}