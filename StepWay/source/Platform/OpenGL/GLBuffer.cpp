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

			StepWay::Graphics::OpenGL::GLVertexBuffer::GLVertexBuffer()
			{
			}

			void GLVertexBuffer::SetUp(void * data, int size)
			{
				glGenBuffers(1, &m_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
				GL_CHECK_ERRORS();
			}

			void GLVertexBuffer::ShutDown()
			{
				glDeleteBuffers(1, &m_buffer);
				GL_CHECK_ERRORS();
			}

			void GLVertexBuffer::Bind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
				GL_CHECK_ERRORS();
			}

			void GLVertexBuffer::UnBind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				GL_CHECK_ERRORS();
			}

			GLVertexBuffer::~GLVertexBuffer()
			{
			}




			GLIndexBuffer::GLIndexBuffer():
				m_indexBuffer(NULL),
				m_count(0)
			{
			}

			void GLIndexBuffer::SetUp(uint16 * indices, int count)
			{
				glGenBuffers(1, &m_indexBuffer);
				GL_CHECK_ERRORS();
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
				GL_CHECK_ERRORS();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), indices, GL_STATIC_DRAW);
				GL_CHECK_ERRORS();
				m_count = count;
			}

			void GLIndexBuffer::ShutDown()
			{
				glDeleteBuffers(1, &m_indexBuffer);
				GL_CHECK_ERRORS();
			}

			void GLIndexBuffer::Bind()
			{
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