#include <glad/glad.h>

#include "VertexBuffer.h"

#include <iostream>

namespace Renderer {

	VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
	{
		glGenBuffers(1, &m_VertexBufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBufferID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}