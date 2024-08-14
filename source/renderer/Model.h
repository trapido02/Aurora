#pragma once

#include "Mesh.h"

#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Renderer {

	class Model
	{
	public:
		Model(std::string modelPath);
		void Draw(Shader& shader);
	private:
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}