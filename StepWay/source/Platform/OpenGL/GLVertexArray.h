#pragma once
#include "Core.h"
#include "Graphics/API/VertexArray.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{


			class GLVertexArray : public API::VertexArray
			{
			public:
				GLVertexArray() : m_VAO(0) {};

				virtual void SetUp() override;
				virtual void ShutDown() override;

				virtual void Bind() override;
				virtual void UnBind() override;

				virtual void SetVertexBuffer(std::shared_ptr<API::VertexBuffer> pBuffer) override;
				virtual void SetIndexBuffer(std::shared_ptr<API::IndexBuffer> pBuffer) override;

				virtual ~GLVertexArray() {};
			private:
				uint32 m_VAO;
			};


		}
	}
}
