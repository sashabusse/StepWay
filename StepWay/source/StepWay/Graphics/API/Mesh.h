#pragma once
#include "Core.h"
#include "VertexArray.h"
#include <string>
#include <vector>


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{
			
			class Mesh
			{
			public:
				Mesh();
				~Mesh();

				void SetUpBuffers();
				void ShutDownBuffers();

				void LoadFromFile(std::string filename);

				inline std::shared_ptr<VertexArray> GetVAO() { return m_VAO; };
				inline std::shared_ptr<IndexBuffer> GetIBO() { return m_IBO; };
				
				inline const std::shared_ptr<VertexArray> GetVAO() const { return m_VAO; };
				inline const std::shared_ptr<IndexBuffer> GetIBO() const { return m_IBO; };

			private:
			public:
				std::vector<float> m_vertices;
				std::vector<uint16> m_indices;

			private:

				std::shared_ptr<VertexBuffer> m_buffer;
				std::shared_ptr<IndexBuffer> m_IBO;
				std::shared_ptr<VertexArray> m_VAO;
				
			};


		}
	}
}