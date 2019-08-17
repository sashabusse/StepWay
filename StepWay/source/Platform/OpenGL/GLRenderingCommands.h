#pragma once
#include "Core.h"
#include "Graphics/API/RenderingCommands.h"

namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class GLRenderCommand : public API::RenderCommand
			{
			public:
				GLRenderCommand() {};

				virtual void SetClearColor(const glm::fvec4& col) override;

				virtual void Clear() override;
				virtual void Draw(API::VertexArray* const VAO) override;
				virtual void DrawIndexed(API::VertexArray* const VAO, API::IndexBuffer* const IBO) override;

				~GLRenderCommand() {};
			private:
			public:
			private:
			};


		}
	}
}