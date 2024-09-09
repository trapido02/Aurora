#include "pch.h"

#include "Mesh.h"

namespace Renderer {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture>& textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		m_VertexArray = new VertexArray();
		m_VertexBuffer = new VertexBuffer(m_Vertices);
		m_IndexBuffer = new IndexBuffer(m_Indices);
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Create()
	{
		m_VertexArray->Create();
		m_VertexBuffer->Create();
		m_IndexBuffer->Create();

		m_VertexArray->AttachBuffer(*m_VertexBuffer);

		// Initalize all the textures
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i].Create();
		}
	}

	void Mesh::Destroy()
	{
		delete m_VertexArray;
		delete m_VertexBuffer;
		delete m_IndexBuffer;

		// Destroy all textures
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i].Destroy();
		}
	}

	void Mesh::Draw(Shader& shader)
	{
		shader.Bind();
		m_VertexArray->Bind();
		m_IndexBuffer->Bind();

		// Bind textures
		std::string name;
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			name = "texture" + std::to_string(i + 1);
			shader.SetUniform1i((GLchar*)name.c_str(), i);
			m_Textures[i].Bind(i);
		}

		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

		m_VertexArray->Unbind();
		shader.Unbind();
	}

}