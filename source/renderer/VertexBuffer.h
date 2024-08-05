#pragma once

namespace Renderer {

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(float count)
			: m_Count(count) {}
		float m_Count;
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