#pragma once
#include "Core.h"
#include "Buffer.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			//rework later when will add DirectX
			class VertexArray
			{
			public:
				VertexArray() {};
				
				virtual void SetUp() = 0;
				virtual void ShutDown() = 0;

				virtual void Bind() = 0;
				virtual void UnBind() = 0;

				virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> pBuffer) = 0;
				virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> pBuffer) = 0;

				static VertexArray* Create(GAPI_TYPE type);

				~VertexArray() {};
			protected:
				std::shared_ptr<VertexBuffer> m_VertexBuffer;
				std::shared_ptr<IndexBuffer> m_IndexBuffer;
			};


		}
	}
}