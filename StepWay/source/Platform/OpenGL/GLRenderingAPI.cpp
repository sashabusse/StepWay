#include "StepWayPCH.h"
#include "GLRenderingAPI.h"
#include "ErrorHandling.h"
#include "glad/glad.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			void GLRenderingAPI::Clear()
			{
				glClear(GL_COLOR_BUFFER_BIT);
				GL_CHECK_ERRORS();
			}
			void GLRenderingAPI::Clear(const glm::fvec4& col)
			{
				SetClearColor(col);
				Clear();
			}

			void GLRenderingAPI::SetClearColor(const glm::fvec4& col)
			{
				glClearColor(col.r, col.g, col.b, col.a);
				GL_CHECK_ERRORS();
			}

			void GLRenderingAPI::DrawIndexed(const std::shared_ptr<API::VertexArray> VAO, const std::shared_ptr<API::IndexBuffer> IBO)
			{
				VAO->Bind();
				IBO->Bind();
				glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_SHORT, NULL);
				return;
			}

		}
	}
}