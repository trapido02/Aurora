#pragma once

namespace Renderer {

	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size, const void* data, GLenum usage);
		~VertexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_VertexBufferID;
	};

}