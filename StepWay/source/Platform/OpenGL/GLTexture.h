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
				void SetUp(int width, int height) override;
				void ShutDown() override;
				
				void Bind() override;
				void Unbind() override;

				void SetToUnit(int num) override;

				virtual ~GLTexture() {};
			private:
				void loadImageByName(std::string filename);
				GLenum UnitNumToGLenum(int num);
			private:
				uint m_id;
			};


		}
	}
}
