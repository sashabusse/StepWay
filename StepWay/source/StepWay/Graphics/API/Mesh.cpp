#pragma once
#include "StepWayPCH.h"
#include "Mesh.h"
#include <vector>


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
				m_buffer->SetUp(&m_vertices[0], m_vertices.size() * sizeof(m_vertices[0]));
				m_buffer->Bind();
				m_buffer->SetLayout({ ShaderDataType::FLOAT3 });

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

			void Mesh::LoadFromFile(std::string filename)
			{
				
			}

		}
	}
}