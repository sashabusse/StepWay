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
				//not copyable
				VertexArray(VertexArray&) = delete;
				VertexArray(const VertexArray&) = delete;
				VertexArray& operator=(VertexArray&) = delete;
				VertexArray& operator=(const VertexArray&) = delete;

				//not moveable
				VertexArray(VertexArray&&) = delete;
				VertexArray& operator=(VertexArray&&) = delete;


				VertexArray():
				m_VertexBuffer(nullptr),
				m_IndexBuffer(nullptr) {};

				virtual ~VertexArray() {};
				
				//call just once to set up
				virtual void SetUp() = 0;
				virtual void ShutDown() = 0;

				virtual bool IsInitialized() = 0;

				virtual void Bind() = 0;
				virtual void UnBind() = 0;

				virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> pBuffer) = 0;
				virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> pBuffer) = 0;

				static VertexArray* Create(GAPI_TYPE type);
			protected:
				std::shared_ptr<VertexBuffer> m_VertexBuffer;
				std::shared_ptr<IndexBuffer> m_IndexBuffer;
			};


		}
	}
}