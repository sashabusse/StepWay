#pragma once
#include "Core.h"
#include "RenderingAPI.h"
#include "Context.h"
#include "VertexArray.h"
#include "Mesh.h"
#include "glm/glm.hpp"
#include "Graphics/API/Shader.h"


namespace StepWay
{	
	namespace Graphics
	{	
		namespace API
		{	

			class RenderingCommands
			{
			public:
				static void Init()
				{
					m_API = std::unique_ptr<RenderingAPI>(RenderingAPI::Create(GAPI_TYPE::OPENGL));
					m_API->Init();
				};

				static void Clear() { m_API->Clear(); };
				static void Clear(const glm::fvec4& col) { m_API->Clear(col); };
				static void SetClearColor(const glm::fvec4& col) { m_API->SetClearColor(col); };

				static void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO)
				{
					m_API->DrawIndexed(VAO, IBO);
				};
			private:
				static std::unique_ptr<RenderingAPI> m_API;
			};

			class Renderer
			{
			public:
				void BeginScene(glm::mat4& projection, glm::mat4& cam_transform);

				inline void Clear() { RenderingCommands::Clear(); };

				inline void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO,
					const glm::mat4& model)
				{
					m_shader->SetUniform("u_VP", m_view_projection);
					m_shader->SetUniform("u_model", model);
					RenderingCommands::DrawIndexed(VAO, IBO);
				}
				inline void DrawIndexed(
					const Mesh& mesh,
					const glm::mat4& model)
				{
					DrawIndexed(mesh.GetVAO(), mesh.GetIBO(), model);
				}
				inline void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO)
				{
					RenderingCommands::DrawIndexed(VAO, IBO);
				};
				void DrawIndexed(const Mesh& mesh) { RenderingCommands::DrawIndexed(mesh.GetVAO(), mesh.GetIBO()); };

				void SetShader(std::shared_ptr<Graphics::API::Shader> shader)
				{
					m_shader = shader;
				};
			private:
				glm::mat4 m_view_projection = glm::mat4(1.0f);
				std::shared_ptr<Graphics::API::Shader> m_shader;
			};

		}
	}
}
