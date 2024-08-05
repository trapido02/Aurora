#pragma once

namespace Renderer {

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_IndexBufferID;
	};

}
