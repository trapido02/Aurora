#include <glad/glad.h>

#include "VertexArray.h"

namespace Renderer {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::AttachBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout)
	{
		Bind();
		vertexBuffer.Bind();
		glVertexAttribPointer(0, layout.m_Count, GL_FLOAT, GL_FALSE, layout.m_Count * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
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