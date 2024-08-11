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
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;

		VertexArray* vertexArray = nullptr;
		VertexBuffer* vertexBuffer = nullptr;
		IndexBuffer* indexBuffer = nullptr;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture>& textures);

		void Draw(Shader& shader);
	};

}
