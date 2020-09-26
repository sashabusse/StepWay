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
				GLVertexArray() : m_VAO(NULL) {};

				virtual ~GLVertexArray() { if (IsInitialized())ShutDown(); };

				virtual void SetUp() override;
				virtual void ShutDown() override;

				virtual bool IsInitialized() override { return m_VAO != NULL; };

				virtual void Bind() override;
				virtual void UnBind() override;

				virtual void SetVertexBuffer(std::shared_ptr<API::VertexBuffer> pBuffer) override;
				virtual void SetIndexBuffer(std::shared_ptr<API::IndexBuffer> pBuffer) override;
			private:
				uint32 m_VAO;
			};


		}
	}
}
