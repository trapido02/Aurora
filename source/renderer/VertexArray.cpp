#include "pch.h"

#include <glad/glad.h>

#include "VertexArray.h"

namespace Renderer {

	VertexArray::VertexArray()
	{
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::Create()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::AttachVertexBuffer(VertexBuffer& vertexBuffer)
	{
		glVertexArrayVertexBuffer(m_VertexArrayID, 0, vertexBuffer.GetID(), 0, sizeof(Vertex));

		glVertexArrayAttribFormat(m_VertexArrayID, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
		glVertexArrayAttribBinding(m_VertexArrayID, 0, 0);
		glEnableVertexArrayAttrib(m_VertexArrayID, 0);

		glVertexArrayAttribFormat(m_VertexArrayID, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoord));
		glVertexArrayAttribBinding(m_VertexArrayID, 1, 0);
		glEnableVertexArrayAttrib(m_VertexArrayID, 1);
	}

	void VertexArray::AttachIndexBuffer(IndexBuffer& indexBuffer)
	{
		glVertexArrayElementBuffer(m_VertexArrayID, indexBuffer.GetID());
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(NULL);
	}

	unsigned int VertexArray::GetID()
	{
		return m_VertexArrayID;
	}

}