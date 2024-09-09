#pragma once

#include <vector>

namespace Renderer {

	class IndexBuffer
	{
	public:
		IndexBuffer(std::vector<unsigned int> indices);
		~IndexBuffer();

		void Create();
		void Destroy();

		void Bind();
		void Unbind();
	private:
		unsigned int m_IndexBufferID;
		std::vector<unsigned int> m_Indices;
	};

}
