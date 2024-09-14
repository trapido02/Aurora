#include "pch.h"

#include "Model.h"

namespace Renderer {

	Model::Model(std::string modelPath)
		: m_ModelPath(modelPath)
	{
	}

	Model::~Model()
	{
	}

	void Model::Create()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_ModelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::string error = "ASSIMP ERROR: " + std::string(importer.GetErrorString());
			ERROR(error);
			return;
		}

		m_Directory = m_ModelPath.substr(0, m_ModelPath.find_last_of("/"));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::Destroy()
	{
		// Destroy all meshes
		for (unsigned int i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].Destroy();
		}
	}

	void Model::Draw(Shader& shader)
	{ 
		glm::mat4 model = glm::mat4(1.0f);

		// Apply position
		model = glm::translate(model, m_Position);

		// Apply rotation for each axis
		model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Apply scale
		model = glm::scale(model, m_Scale);

		shader.Bind();
		shader.SetUniformMatrix4fv("model", model);
		shader.Unbind();

		for (unsigned int i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].Draw(shader);
		}
	}

	void Model::SetScale(glm::vec3 scale)
	{
		m_Scale = scale;
	}

	void Model::SetPosition(glm::vec3 position)
	{
		m_Position = position;
	}

	void Model::SetRotation(glm::vec3 rotation)
	{
		m_Rotation = rotation;
	}

	// Private methods

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoord = vec;
			}
			else
			{
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		
		// Create the final mesh with all vertices, indices and textures and run its Create method
		Mesh finalMesh(vertices, indices, textures);
		finalMesh.Create();

		return finalMesh;
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture(m_Directory + "/" + str.C_Str());
			textures.push_back(texture);
		}
		return textures;
	}

};