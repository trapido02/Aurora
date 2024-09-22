#pragma once

#include "Mesh.h"
#include "SceneObject.h"

#include <vector>
#include <memory>

#include <glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Aurora::Renderer {

	class Model : public SceneObject
	{
	public:
		Model(std::string modelPath);
		~Model();

		void Create();
		void Destroy();

		void Draw(Shader& shader);
	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;
		std::string m_ModelPath;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}