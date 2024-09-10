#pragma once

#include "Mesh.h"

#include <vector>
#include <memory>

#include <glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Renderer {

	class Model
	{
	public:
		Model(std::string modelPath);
		~Model();

		void Create();
		void Destroy();

		void Draw(Shader& shader);

		void SetScale(glm::vec3);
		void SetPosition(glm::vec3);
		void SetRotation(glm::vec3);
	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;
		std::string m_ModelPath;

		glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}