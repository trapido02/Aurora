#include "pch.h"

#include <glad/glad.h>

#include "VertexBuffer.h"

namespace Renderer {

	VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
		: m_Vertices(vertices)
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Create()
	{
		glGenBuffers(1, &m_VertexBufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
		Unbind();
	}

	void VertexBuffer::Destroy()
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