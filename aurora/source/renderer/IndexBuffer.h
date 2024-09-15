#pragma once

#include <vector>

namespace Aurora::Renderer {

	class IndexBuffer
	{
	public:
		IndexBuffer(std::vector<unsigned int> indices);
		~IndexBuffer();

		void Create();
		void Destroy();

		void Bind();
		void Unbind();

		unsigned int GetID();
	private:
		unsigned int m_IndexBufferID;
		std::vector<unsigned int> m_Indices;
	};

}
