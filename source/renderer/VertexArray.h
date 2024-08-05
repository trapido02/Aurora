#pragma once

namespace Renderer {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();
	private:
		unsigned int m_VertexArrayID;
	};

}