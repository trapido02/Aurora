#include "Mesh.h"
#include <iostream>

namespace Renderer {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture>& textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		vertexArray = new VertexArray();
		vertexBuffer = new VertexBuffer(m_Vertices);
		indexBuffer = new IndexBuffer(m_Indices);

		vertexArray->AttachBuffer(*vertexBuffer);
	}

	void Mesh::Draw(Shader& shader)
	{

		shader.Bind();
		vertexArray->Bind();
		indexBuffer->Bind();

		// Bind textures
		std::string name;
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			name = "texture" + std::to_string(i + 1);
			shader.SetUniform1i((GLchar*)name.c_str(), i);
			m_Textures[i].Bind(i);
		}

		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

		vertexArray->Unbind();
		shader.Unbind();
	}

}