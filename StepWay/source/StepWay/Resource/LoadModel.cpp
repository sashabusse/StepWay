#include "StepWayPCH.h"
#include "LoadModel.h"
#include <string>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using StepWay::Graphics::API::Mesh;
using StepWay::Graphics::API::Vertex;

namespace StepWay
{
	namespace ResourceLoaders
	{
		std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::shared_ptr<Mesh> result(new Mesh());

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;

				result->m_vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					result->m_indices.push_back(face.mIndices[j]);
			}

			return std::move(result);
		}

		void processNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& meshes)
		{

			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene, meshes);
			}
		}

		std::vector<std::shared_ptr<Mesh>> Load3DModel(const std::string& filename)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

			SW_CORE_ASSERT(scene != nullptr && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode != nullptr,
							std::string("ERROR::ASSIMP::") + import.GetErrorString());
			
			std::string directory = filename.substr(0, filename.find_last_of('/'));

			std::vector<std::shared_ptr<Mesh>> meshes;
			processNode(scene->mRootNode, scene, meshes);

			return meshes;
		}
		std::shared_ptr<Graphics::API::Mesh> LoadCube(const glm::vec3& pos, const glm::vec3& size)
		{
			glm::vec3 n_size = size;
			n_size.x /= 2;
			n_size.y /= 2;
			n_size.z /= 2;

			std::shared_ptr<Mesh> result(new Mesh());
			glm::vec3 ppp = n_size + pos;
			glm::vec3 mpp = glm::vec3({ -n_size.x, n_size.y, n_size.z }) + pos;
			glm::vec3 pmp = glm::vec3({ n_size.x, -n_size.y, n_size.z }) + pos;
			glm::vec3 mmp = glm::vec3({ -n_size.x, -n_size.y, n_size.z }) + pos;

			glm::vec3 ppm = glm::vec3({n_size.x, n_size.y, -n_size.z}) + pos;
			glm::vec3 mpm = glm::vec3({ -n_size.x, n_size.y, -n_size.z }) + pos;
			glm::vec3 pmm = glm::vec3({ n_size.x, -n_size.y, -n_size.z }) + pos;
			glm::vec3 mmm = glm::vec3({ -n_size.x, -n_size.y, -n_size.z }) + pos;
			result->m_vertices = {
				Vertex(ppp,{0,0,1}),
				Vertex(mpp,{0,0,1}),
				Vertex(mmp,{0,0,1}),
				Vertex(pmp,{0,0,1}),

				Vertex(ppm,{0,0,-1}),
				Vertex(mpm,{0,0,-1}),
				Vertex(mmm,{0,0,-1}),
				Vertex(pmm,{0,0,-1}),

				Vertex(ppp,{0,1,0}),
				Vertex(mpp,{0,1,0}),
				Vertex(mpm,{0,1,0}),
				Vertex(ppm,{0,1,0}),

				Vertex(pmp,{0,-1,0}),
				Vertex(mmp,{0,-1,0}),
				Vertex(mmm,{0,-1,0}),
				Vertex(pmm,{0,-1,0}),

				Vertex(ppp,{1,0,0}),
				Vertex(pmp,{1,0,0}),
				Vertex(pmm,{1,0,0}),
				Vertex(ppm,{1,0,0}),

				Vertex(mpp,{-1,0,0}),
				Vertex(mmp,{-1,0,0}),
				Vertex(mmm,{-1,0,0}),
				Vertex(mpm,{-1,0,0}),

			};
			result->m_indices = {
				0,1,2,     2,3,0,
				4,5,6,     6,7,4,
				8,9,10,    10,11,8,
				12,13,14,  14,15,12,
				16,17,18,  18,19,16,
				20,21,22,  22,23,20
			};

			return result;
		}

		std::shared_ptr<Graphics::API::Mesh> LoadPlaneXY(const glm::vec3& pos, const glm::vec2& size)
		{
			glm::vec2 n_size = size;
			n_size.x /= 2;
			n_size.y /= 2;

			std::shared_ptr<Mesh> result(new Mesh());
			result->m_vertices = {
				Vertex({n_size.x, n_size.y, 0}, {0,0,1}),
				Vertex({n_size.x, -n_size.y, 0}, {0,0,1}),
				Vertex({-n_size.x, -n_size.y, 0}, {0,0,1}),
				Vertex({-n_size.x, n_size.y, 0}, {0,0,1})
			};
			result->m_indices = {
				0,1,2,  2,3,0
			};
			return result;
		}

		std::shared_ptr<Graphics::API::Mesh> LoadPlaneXZ(const glm::vec3& pos, const glm::vec2& size)
		{
			glm::vec2 n_size = size;
			n_size.x /= 2;
			n_size.y /= 2;

			std::shared_ptr<Mesh> result(new Mesh());
			result->m_vertices = {
				Vertex({n_size.x,  0,  n_size.y}, {0,1,0}),
				Vertex({n_size.x,  0, -n_size.y}, {0,1,0}),
				Vertex({-n_size.x, 0, -n_size.y}, {0,1,0}),
				Vertex({-n_size.x, 0,  n_size.y}, {0,1,0})
			};
			result->m_indices = {
				0,1,2,  2,3,0
			};
			return result;
		}

		std::shared_ptr<Graphics::API::Mesh> LoadPlaneYZ(const glm::vec3& pos, const glm::vec2& size)
		{
			glm::vec2 n_size = size;
			n_size.x /= 2;
			n_size.y /= 2;

			std::shared_ptr<Mesh> result(new Mesh());
			result->m_vertices = {
				Vertex({0, n_size.x,  n_size.y}, {1,0,0}),
				Vertex({0, n_size.x, -n_size.y}, {1,0,0}),
				Vertex({0, -n_size.x,-n_size.y}, {1,0,0}),
				Vertex({0, -n_size.x, n_size.y}, {1,0,0})
			};
			result->m_indices = {
				0,1,2,  2,3,0
			};
			return result;
		}

	}
}