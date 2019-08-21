#pragma once
#include "Core.h"
#include "Context.h"
#include "VertexArray.h"
#include "glm/glm.hpp"


namespace StepWay
{	namespace Graphics
	{	namespace API
		{	

	class RenderCommand
	{
	public:
		//need math library to make it
		virtual void SetClearColor(const glm::fvec4& col) = 0;
		virtual void Clear() = 0;

		virtual void Draw(API::VertexArray* const VAO) = 0;
		void Draw(const std::shared_ptr<API::VertexArray> VAO) { Draw(&*VAO); };

		virtual void DrawIndexed(API::VertexArray* const VAO,
								API::IndexBuffer* const IBO) = 0;
		void DrawIndexed(const std::shared_ptr<API::VertexArray> VAO,
			const std::shared_ptr<API::IndexBuffer> IBO)
		{DrawIndexed(&*VAO, &*IBO);}

		static RenderCommand* Create(GAPI_TYPE api);

		virtual ~RenderCommand() {};
	private:
	};

}}}
