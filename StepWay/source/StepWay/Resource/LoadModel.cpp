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
		Mesh processMesh(aiMesh* mesh, const aiScene* scene)
		{
			Mesh result;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;

				result.m_vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					result.m_indices.push_back(face.mIndices[j]);
			}

			return std::move(result);
		}

		void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
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

		std::vector<Mesh> Load3DModel(const std::string& filename)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

			SW_CORE_ASSERT(scene != nullptr && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode != nullptr,
							std::string("ERROR::ASSIMP::") + import.GetErrorString());
			
			std::string directory = filename.substr(0, filename.find_last_of('/'));

			std::vector<Mesh> meshes;
			processNode(scene->mRootNode, scene, meshes);

			return meshes;
		}
	}
}