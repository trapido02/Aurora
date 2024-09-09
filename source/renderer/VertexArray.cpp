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
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::AttachBuffer(VertexBuffer& vertexBuffer)
	{
		Bind();
		vertexBuffer.Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(1);

		vertexBuffer.Unbind();
		Unbind();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

}