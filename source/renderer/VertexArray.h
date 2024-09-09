#pragma once

#include "VertexBuffer.h"

namespace Renderer {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Create();
		void Destroy();

		void AttachBuffer(VertexBuffer& vertexBuffer);

		void Bind();
		void Unbind();
	private:
		unsigned int m_VertexArrayID = NULL;
	};

}