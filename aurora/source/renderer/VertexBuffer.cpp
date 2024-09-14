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
		glCreateBuffers(1, &m_VertexBufferID);
		glNamedBufferData(m_VertexBufferID, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
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
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	unsigned int VertexBuffer::GetID()
	{
		return m_VertexBufferID;
	}

}