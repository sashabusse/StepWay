#include "StepWayPCH.h"
#include "GLBuffer.h"
#include "glad/glad.h"
#include "ErrorHandling.h"



namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			StepWay::Graphics::OpenGL::GLVertexBuffer::GLVertexBuffer() :
				m_buffer(NULL),
				VertexBuffer()
			{
			}

			void GLVertexBuffer::SetUp(void* data, int size)
			{
				if(m_buffer == NULL)
					glGenBuffers(1, &m_buffer);

				Bind();
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
				GL_CHECK_ERRORS();
			}


			void GLVertexBuffer::ShutDown()
			{
				SW_CORE_ASSERT(m_buffer != NULL, "trying to shutdown not initialized buffer");

				glDeleteBuffers(1, &m_buffer);
				GL_CHECK_ERRORS();

				m_buffer = NULL;
			}

			bool GLVertexBuffer::IsInitialized()
			{
				return m_buffer != NULL;
			}

			void GLVertexBuffer::Bind()
			{
				SW_CORE_ASSERT(m_buffer != NULL, "trying to bind NULL buffer");
				glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
				GL_CHECK_ERRORS();
			}

			void GLVertexBuffer::UnBind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				GL_CHECK_ERRORS();
			}


			GLIndexBuffer::GLIndexBuffer():
				m_indexBuffer(NULL),
				m_count(0)
			{
			}

			void GLIndexBuffer::SetUp(uint16* indices, int count)
			{
				if(m_indexBuffer==NULL)
					glGenBuffers(1, &m_indexBuffer);

				Bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), indices, GL_STATIC_DRAW);
				GL_CHECK_ERRORS();
				m_count = count;
			}

			void GLIndexBuffer::ShutDown()
			{
				SW_CORE_ASSERT(m_indexBuffer != NULL, "trying to shut down not initialized index buffer");

				glDeleteBuffers(1, &m_indexBuffer);
				GL_CHECK_ERRORS();

				m_indexBuffer = NULL;
				m_count = 0;
			}

			bool GLIndexBuffer::IsInitialized()
			{
				return m_indexBuffer != NULL;
			}

			
			void GLIndexBuffer::Bind()
			{
				SW_CORE_ASSERT(m_indexBuffer != NULL, "trying to bind not initialized index buffer");
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
				GL_CHECK_ERRORS();
			}

			void GLIndexBuffer::UnBind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
				GL_CHECK_ERRORS();
			}

			
		}
	}
}