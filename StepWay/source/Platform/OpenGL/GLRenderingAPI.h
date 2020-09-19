#pragma once
#include "Graphics/API/RenderingAPI.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			class GLRenderingAPI : public API::RenderingAPI
			{
			public:
				virtual ~GLRenderingAPI() {};

				virtual void Clear() override;
				virtual void Clear(const glm::fvec4& col) override;
				virtual void SetClearColor(const glm::fvec4& col) override;

				virtual void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO) override;
			};

		}
	}
}