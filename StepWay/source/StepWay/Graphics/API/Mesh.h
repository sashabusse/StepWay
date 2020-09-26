#pragma once
#include "Core.h"
#include "VertexArray.h"
#include <string>
#include <vector>
#include "glm/glm.hpp"



namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			struct Vertex {
				Vertex() :
					position({ 0,0,0 }),
					normal({ 0,0,0 }) {};
				Vertex(glm::vec3 pos, glm::vec3 norm) :
					position(pos),
					normal(norm) {};
				glm::vec3 position;
				glm::vec3 normal;
			};

			class Mesh
			{
			public:
				Mesh();

				//copy
				Mesh(const Mesh& other);
				Mesh& operator= (const Mesh & other);

				//move
				Mesh(Mesh&& other) noexcept;
				Mesh& operator= (Mesh&& other) noexcept;

				~Mesh();

				void SetUpBuffers();
				void ShutDownBuffers();
				bool IsBufInitialized() const { return m_buf_initialized; };

				void MakeFlatNormals();

				inline std::shared_ptr<VertexArray> GetVAO() { return m_VAO; };
				inline std::shared_ptr<IndexBuffer> GetIBO() { return m_IBO; };
				
				inline const std::shared_ptr<VertexArray> GetVAO() const { return m_VAO; };
				inline const std::shared_ptr<IndexBuffer> GetIBO() const { return m_IBO; };


			private:
			public:
				std::vector<Vertex> m_vertices;
				std::vector<uint16> m_indices;

			private:
				bool m_buf_initialized;

				std::shared_ptr<VertexBuffer> m_buffer;
				std::shared_ptr<IndexBuffer> m_IBO;
				std::shared_ptr<VertexArray> m_VAO;
				
			};


		}
	}
}