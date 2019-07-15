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




		}
	}
}