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
			Mesh::Mesh()
			{
			}

			Mesh::~Mesh()
			{
			}

			void Mesh::SetUpBuffers()
			{
				m_buffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(GAPI_TYPE::OPENGL));
				m_buffer->SetUp(m_vertices);
				m_buffer->Bind();
				m_buffer->SetLayout({ ShaderDataType::FLOAT3, ShaderDataType::FLOAT3 });

				m_IBO = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(GAPI_TYPE::OPENGL));
				m_IBO->SetUp(&m_indices[0], m_indices.size());
				m_IBO->Bind();

				m_VAO = std::shared_ptr<VertexArray>(VertexArray::Create(GAPI_TYPE::OPENGL));
				m_VAO->SetUp();
				m_VAO->Bind();
				m_VAO->SetVertexBuffer(m_buffer);
			}

			void Mesh::ShutDownBuffers()
			{
				m_buffer->ShutDown();
				m_IBO->ShutDown();
				m_VAO->ShutDown();
			}

			void Mesh::make_flat_normals()
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

