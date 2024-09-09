#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <string>

namespace Renderer {

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture>& textures);
		~Mesh();
		
		void Create();
		void Destroy();

		void Draw(Shader& shader);
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;

		VertexArray* m_VertexArray = nullptr;
		VertexBuffer* m_VertexBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
	};

}
