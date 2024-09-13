#pragma once

#include <glm.hpp>
#include <vector>

namespace Renderer {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(std::vector<Vertex> vertices);
		~VertexBuffer();

		void Create();
		void Destroy();

		void Bind();
		void Unbind();

		unsigned int GetID();
	private:
		unsigned int m_VertexBufferID = NULL;
		std::vector<Vertex> m_Vertices;
	};

}