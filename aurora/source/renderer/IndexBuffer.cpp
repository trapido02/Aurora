#include "pch.h"

#include <glad/glad.h>

#include "IndexBuffer.h"

namespace Aurora::Renderer {

	IndexBuffer::IndexBuffer(std::vector<unsigned int> indices)
		: m_IndexBufferID(NULL), m_Indices(indices)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Create()
	{
		glCreateBuffers(1, &m_IndexBufferID);
		glNamedBufferData(m_IndexBufferID, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);
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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

	unsigned int IndexBuffer::GetID()
	{
		return m_IndexBufferID;
	}

}
