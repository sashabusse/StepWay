#include "StepWayPCH.h"
#include "GLRenderingCommands.h"
#include "ErrorHandling.h"
#include "glad/glad.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{
			void GLRenderCommand::SetClearColor(const glm::fvec4 & col)
			{
				glClearColor(col.r, col.g, col.b, col.a);
				GL_CHECK_ERRORS();
			}

			void GLRenderCommand::Clear()
			{
				glClear(GL_COLOR_BUFFER_BIT);
				return;
			}

			void GLRenderCommand::Draw(API::VertexArray* const VAO)
			{
				VAO->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 3);
				return;
			}

			void GLRenderCommand::DrawIndexed(API::VertexArray* const VAO, API::IndexBuffer* const IBO)
			{
				VAO->Bind();
				IBO->Bind();
				glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_SHORT, NULL);
				return;
			}

		}
	}
}
