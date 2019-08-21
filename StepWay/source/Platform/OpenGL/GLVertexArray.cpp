#include "StepWayPCH.h"
#include "GLVertexArray.h"
#include "glad/glad.h"
#include "ErrorHandling.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{


			void GLVertexArray::SetUp()
			{
				glGenVertexArrays(1, &m_VAO);
				GL_CHECK_ERRORS();
			}

			void GLVertexArray::ShutDown()
			{
				glDeleteVertexArrays(1, &m_VAO);
				GL_CHECK_ERRORS();
			}

			void GLVertexArray::Bind()
			{
				glBindVertexArray(m_VAO);
				GL_CHECK_ERRORS();
			}

			void GLVertexArray::UnBind()
			{
				glBindVertexArray(NULL);
				GL_CHECK_ERRORS();
			}

			void GLVertexArray::SetVertexBuffer(std::shared_ptr<API::VertexBuffer> pBuffer)
			{
				m_VertexBuffer = pBuffer;
				glBindVertexArray(m_VAO);
				int i = 0;
				for (auto& element : m_VertexBuffer->GetLayout())
				{
					glEnableVertexAttribArray(i);
					glVertexAttribPointer(i, element.GetComponentCount(), GL_FLOAT, GL_TRUE, m_VertexBuffer->GetLayout().GetStride(), (void*)((int64)element.GetOffset()));//uin64 isn't good
					i++;
				}
				GL_CHECK_ERRORS();
			}

			void GLVertexArray::SetIndexBuffer(std::shared_ptr<API::IndexBuffer> pBuffer)
			{
				m_IndexBuffer = pBuffer;
			}




		}
	}
}