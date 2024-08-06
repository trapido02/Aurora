#include <glad/glad.h>

#include "VertexArray.h"

#include <iostream>

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
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * sizeof(element.type);
		}
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