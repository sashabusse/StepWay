#pragma once
#include "Core.h"
#include "Context.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			class Texture
			{
			public:

				virtual void SetUp(std::string filename) = 0;
				virtual void SetUp(int width, int height) = 0;
				virtual void ShutDown() = 0;

				virtual void Bind() = 0;
				virtual void Unbind() = 0;
				
				virtual void SetToUnit(int num) = 0;

				static Texture* Create(GAPI_TYPE api);
				virtual ~Texture() {};
			private:
			public:
			private:
			};
		}
	}
}