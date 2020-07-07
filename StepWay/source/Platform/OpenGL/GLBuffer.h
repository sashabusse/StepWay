#pragma once
#include "Core.h"
#include "Graphics/API/Buffer.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			//NOT SAFE FOR GL ERRORS
			class GLVertexBuffer : public API::VertexBuffer
			{
			public:
				//maybe smth more appropriate here
				GLVertexBuffer();

				virtual void SetUp(void* data, int size) override;
				virtual void ShutDown() override;

				virtual void Bind() override;
				virtual void UnBind() override;

				virtual ~GLVertexBuffer() override;
			private:
				uint32 m_buffer;
			};

			class GLIndexBuffer :public API::IndexBuffer
			{
			public:
				GLIndexBuffer();

				virtual void SetUp(uint16* indices, int count) override;
				virtual void ShutDown() override;
				virtual int GetCount()const override { return m_count; };

				virtual void Bind();
				virtual void UnBind();

				virtual ~GLIndexBuffer() {};
			private:
			public:
			private:
				uint m_indexBuffer;
				int m_count;
			};

		}
	}
}