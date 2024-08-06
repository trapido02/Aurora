#pragma once

#include <vector>

namespace Renderer {

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		template<typename T>
		void Push(unsigned int count) = delete;

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * sizeof(GL_FLOAT);
		}

		inline std::vector<VertexBufferElement> GetElements()
		{
			return m_Elements;
		}

		inline unsigned int GetStride()
		{
			return m_Stride;
		}
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};

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