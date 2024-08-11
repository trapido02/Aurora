#pragma once

#include <vector>

namespace Renderer {

	class IndexBuffer
	{
	public:
		IndexBuffer(std::vector<unsigned int> indices);
		~IndexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_IndexBufferID;
	};

}
