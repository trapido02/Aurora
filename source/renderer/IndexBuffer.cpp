#include "pch.h"

#include <glad/glad.h>

#include "IndexBuffer.h"

namespace Renderer {

	IndexBuffer::IndexBuffer(std::vector<unsigned int> indices)
		: m_IndexBufferID(NULL), m_Indices(indices)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Create()
	{
		glGenBuffers(1, &m_IndexBufferID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);
		Unbind();
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
