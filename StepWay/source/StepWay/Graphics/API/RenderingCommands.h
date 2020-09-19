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
				inline void BeginScene() { m_shader->Bind(); };

				inline void Clear() { RenderingCommands::Clear(); };

				inline void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO,
					const glm::mat4& MVP)
				{
					m_shader->SetUniform("u_MVP", MVP);
					RenderingCommands::DrawIndexed(VAO, IBO);
				}
				inline void DrawIndexed(
					const Mesh& mesh,
					const glm::mat4& MVP)
				{
					m_shader->SetUniform("u_MVP", MVP);
					RenderingCommands::DrawIndexed(mesh.GetVAO(), mesh.GetIBO());
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

				std::shared_ptr<Graphics::API::Shader> m_shader;
			};

		}
	}
}
