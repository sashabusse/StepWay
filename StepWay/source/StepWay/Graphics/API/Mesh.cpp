#pragma once
#include "StepWayPCH.h"
#include "Mesh.h"
#include <vector>
#include "Resource/LoadModel.h"



namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{
			Mesh::Mesh() :
				m_buf_initialized(false),
				m_buffer(VertexBuffer::Create(GAPI_TYPE::OPENGL)),
				m_IBO(IndexBuffer::Create(GAPI_TYPE::OPENGL)),
				m_VAO(VertexArray::Create(GAPI_TYPE::OPENGL))
			{
			}

			Mesh::Mesh(const Mesh& other):
				m_vertices(other.m_vertices),
				m_indices(other.m_indices),
				m_buffer(VertexBuffer::Create(GAPI_TYPE::OPENGL)),
				m_IBO(IndexBuffer::Create(GAPI_TYPE::OPENGL)),
				m_VAO(VertexArray::Create(GAPI_TYPE::OPENGL)),
				m_buf_initialized(false)
			{
				if (other.IsBufInitialized())
					SetUpBuffers();
				int a = 2;
			}

			Mesh& Mesh::operator=(const Mesh& other)
			{
				if (&other == this) return *this;

				this->m_vertices = other.m_vertices;
				this->m_indices = other.m_indices;
				this->m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
				this->m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
				this->m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));
				m_buf_initialized = false;

				if (other.m_buf_initialized)
					SetUpBuffers();

				return *this;
			}

			Mesh::Mesh(Mesh&& other) noexcept :
				m_vertices(std::move(other.m_vertices)),
				m_indices(std::move(other.m_indices)),
				m_buffer(std::move(other.m_buffer)),
				m_IBO(std::move(other.m_IBO)),
				m_VAO(std::move(other.m_VAO)),
				m_buf_initialized(other.m_buf_initialized)
			{
				//reinitialize other
				other.m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
				other.m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
				other.m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));
				
				other.m_buf_initialized = false;
			}

			Mesh& Mesh::operator=(Mesh&& other) noexcept
			{
				this->m_vertices = std::move(other.m_vertices);
				this->m_indices = std::move(other.m_indices);
				this->m_buffer = std::move(other.m_buffer);
				this->m_IBO = std::move(other.m_IBO);
				this->m_VAO = std::move(other.m_VAO);
				this->m_buf_initialized = other.m_buf_initialized;
			
				//reinitialize other
				other.m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
				other.m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
				other.m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));

				other.m_buf_initialized = false;

				return *this;
			}

			Mesh::~Mesh()
			{
			}

			void Mesh::SetUpBuffers()
			{
				m_buffer->SetUp(m_vertices);
				m_buffer->SetLayout({ ShaderDataType::FLOAT3, ShaderDataType::FLOAT3 });

				m_IBO->SetUp(&m_indices[0], m_indices.size());

				if(!m_VAO->IsInitialized())
					m_VAO->SetUp();

				m_VAO->SetVertexBuffer(m_buffer);
				m_VAO->SetIndexBuffer(m_IBO);

				m_buf_initialized = true;
			}

			void Mesh::ShutDownBuffers()
			{
				SW_CORE_ASSERT(m_buf_initialized, "shuting down not initialized buffers in mesh");
				m_buffer->ShutDown();
				m_IBO->ShutDown();
				m_VAO->ShutDown();

				m_buf_initialized = false;

			}

			void Mesh::MakeFlatNormals()
			{
				std::vector<Vertex> nv;
				std::vector<uint16> ni;
				for (int i = 0; i < m_indices.size(); i += 3)
				{
					glm::vec3 f = m_vertices[m_indices[i + 1]].position - m_vertices[m_indices[i]].position;
					glm::vec3 s = m_vertices[m_indices[i + 2]].position - m_vertices[m_indices[i]].position;
					glm::vec3 n_norm = glm::normalize(glm::cross(f, s));
					for (int j = 0; j < 3; j++)
					{
						ni.push_back(i + j);
						nv.push_back(m_vertices[m_indices[i + j]]);
						nv.back().normal = n_norm;
					}
				}
				m_vertices = nv;
				m_indices = ni;
			}

		}
	}
}

