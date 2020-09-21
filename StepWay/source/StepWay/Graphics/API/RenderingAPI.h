#pragma once
#include "Core.h"
#include "glm/glm.hpp"
#include "VertexArray.h"
#include <memory>

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			class RenderingAPI
			{
			public:
				static RenderingAPI* Create(GAPI_TYPE api);

				virtual ~RenderingAPI() {};

				virtual void Init() = 0;
				virtual void Clear() = 0;
				virtual void Clear(const glm::fvec4& col) = 0;
				virtual void SetClearColor(const glm::fvec4& col) = 0;

				virtual void DrawIndexed(
					const std::shared_ptr<API::VertexArray> VAO,
					const std::shared_ptr<API::IndexBuffer> IBO) = 0;

			private:
			};

		}
	}
}