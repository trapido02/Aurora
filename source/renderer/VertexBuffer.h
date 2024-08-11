#pragma once

#include <glm.hpp>
#include <vector>

namespace Renderer {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(std::vector<Vertex> vertices);
		~VertexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_VertexBufferID;
	};

}