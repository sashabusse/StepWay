#include "StepWayPCH.h"
#include "Buffer.h"
#include "OpenGL/GLBuffer.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			//chek for api support for os later but the better way would be to make factory that will know
			VertexBuffer * VertexBuffer::Create(GAPI_TYPE api)
			{
				VertexBuffer* ret;
				switch (api)
				{
				case GAPI_TYPE::OPENGL:
					ret = (VertexBuffer*)SW_NEW OpenGL::GLVertexBuffer();
					break;
				default:
					SW_CORE_ASSERT(false, "not supported api for VertexBuffer");
					break;
				}
				return ret;
			}


			BufferLayout::BufferLayout(std::initializer_list<LayoutElement> elements):
				m_elements(elements),
				m_Stride(0)
			{
				RecalculateTotalSize();
			}

			void BufferLayout::RecalculateTotalSize()
			{
				m_Stride = 0;
				for (auto& element : m_elements)
				{
					element.m_offset = m_Stride;
					m_Stride += element.GetElementSize();
				}
			}

			int ShaderDataTypeComponentCount(ShaderDataType type)
			{
				switch (type)
				{
				case FLOAT:		return 1;
				case FLOAT2:	return 2;
				case FLOAT3:	return 3;
				case FLOAT4:	return 4;
				case INT:		return 1;
				case INT2:		return 2;
				case INT3:		return 3;
				case INT4:		return 4;
				case BOOL:		return 1;
				case MAT2:		return 2 * 2;
				case MAT3:		return 3 * 3;
				case MAT4:		return 4 * 4;
				}
				SW_CORE_ASSERT(false, "failed count components");
				return 0;
			}

			int ShaderDataTypeByteSize(ShaderDataType type)
			{
				switch (type)
				{
				case FLOAT:		return 1 * 4;
				case FLOAT2:	return 2 * 4;
				case FLOAT3:	return 3 * 4;
				case FLOAT4:	return 4 * 4;
				case INT:		return 1 * 4;
				case INT2:		return 2 * 4;
				case INT3:		return 3 * 4;
				case INT4:		return 4 * 4;
				case BOOL:		return 1;
				case MAT2:		return 2 * 2 * 4;
				case MAT3:		return 3 * 3 * 4;
				case MAT4:		return 4 * 4 * 4;
				}
				return 0;
			}

			LayoutElement::LayoutElement(ShaderDataType type):
				m_DataType(type)
			{
			}

			IndexBuffer * IndexBuffer::Create(GAPI_TYPE api)
			{
				switch (api)
				{
				case GAPI_TYPE::OPENGL:
					return SW_NEW OpenGL::GLIndexBuffer();
					break;
				default:
					SW_CORE_ASSERT(false, "no IndexBuffer support for such api");
					break;
				}
				SW_CORE_ASSERT(false, "no IndexBuffer support for such api");
				return nullptr;
			}

		}
	}
}