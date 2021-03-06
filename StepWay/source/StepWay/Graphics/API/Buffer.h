#pragma once
#include "Memory/Memory.h"
#include "Context.h"
#include "Core.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			//rename and move somewhere else later-------------------------------
			enum ShaderDataType : int
			{
				NONE = 0,
				FLOAT, FLOAT2, FLOAT3, FLOAT4,
				INT, INT2, INT3, INT4,
				BOOL,
				MAT2, MAT3, MAT4
			};

			int ShaderDataTypeComponentCount(ShaderDataType type);
			int ShaderDataTypeByteSize(ShaderDataType type);


			class BufferLayout;

			class LayoutElement
			{
				friend BufferLayout;
			public:
				LayoutElement(ShaderDataType type);

				inline int GetComponentCount() const { return ShaderDataTypeComponentCount(m_DataType); }
				inline int GetElementSize() const { return ShaderDataTypeByteSize(m_DataType); }
				inline int GetOffset() const { return m_offset; }

			private:
				ShaderDataType m_DataType;
				int m_offset;
				
			};


			class BufferLayout
			{
			public:
				BufferLayout(std::initializer_list<LayoutElement> elements);

				typedef std::vector<LayoutElement>::iterator		Iterator;
				typedef std::vector<LayoutElement>::const_iterator	ConstIterator;

				Iterator begin() { return m_elements.begin(); }
				Iterator end() { return m_elements.end(); }
				ConstIterator begin() const { return m_elements.begin(); }
				ConstIterator end() const { return m_elements.end(); }
				
				inline int GetElementCount()const { return (int)m_elements.size(); }
				inline int GetStride() const { return m_Stride; }

			private:
				void RecalculateTotalSize();

			private:
				std::vector<LayoutElement> m_elements;
				int m_Stride;
			};


			class VertexBuffer
			{
			public:
				//not copyable
				VertexBuffer(VertexBuffer&) = delete;
				VertexBuffer(const VertexBuffer&) = delete;
				VertexBuffer& operator=(VertexBuffer&) = delete;
				VertexBuffer& operator=(const VertexBuffer&) = delete;

				//not moveable
				VertexBuffer(VertexBuffer&&) = delete;
				VertexBuffer& operator=(VertexBuffer&&) = delete;

				VertexBuffer() : m_layout({}) {};
				//should release(shut down) all the resources
				virtual ~VertexBuffer() {};

				//should load reload data
				virtual void SetUp(void* data, int size) = 0;
				template<typename T>
				void SetUp(std::vector<T>& data)
				{
					SW_CORE_ASSERT(!data.empty(), "empty data not allowed");
					SetUp(&data[0], data.size() * sizeof(data[0]));
				};

				//should release buffer (raise error if not Setted Up)
				virtual void ShutDown() = 0;

				virtual bool IsInitialized() = 0;

				virtual void Bind() = 0;
				virtual void UnBind() = 0;

				void SetLayout(const BufferLayout& layout) { m_layout = layout; }
				BufferLayout& GetLayout() { return m_layout; }
				const BufferLayout& GetLayout() const { return m_layout; }

				//make factorys later?? maybe some other arguments later
				static VertexBuffer* Create(GAPI_TYPE api);
			protected:
				BufferLayout m_layout;
			};



			class IndexBuffer
			{
			public:
				//not copyable
				IndexBuffer(IndexBuffer&) = delete;
				IndexBuffer(const IndexBuffer&) = delete;
				IndexBuffer& operator=(IndexBuffer&) = delete;
				IndexBuffer& operator=(const IndexBuffer&) = delete;

				//not moveable
				IndexBuffer(IndexBuffer&&) = delete;
				IndexBuffer& operator=(IndexBuffer&&) = delete;

				IndexBuffer() {};
				//should release(shut down) all the resources
				virtual ~IndexBuffer() {}

				//load reload indices
				virtual void SetUp(uint16* indices, int count) = 0;
				//release buffer
				virtual void ShutDown() = 0;

				virtual bool IsInitialized() = 0;

				virtual void Bind() = 0;
				virtual void UnBind() = 0;
				
				virtual int GetCount()const = 0;

				static IndexBuffer* Create(GAPI_TYPE api);
			private:
			public:
			private:
			};


		}
	}
}