#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Renderer {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Create();
		void Destroy();

		void AttachVertexBuffer(VertexBuffer& vertexBuffer);
		void AttachIndexBuffer(IndexBuffer& indexBuffer);

		void Bind();
		void Unbind();

		unsigned int GetID();
	private:
		unsigned int m_VertexArrayID = NULL;
	};

}