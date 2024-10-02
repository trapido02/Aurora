#include "pch.h"

#include <glad/glad.h>

#include "Quad.h"

namespace Aurora::Renderer {

	std::vector<Aurora::Renderer::Vertex> quadVertices = {
		Aurora::Renderer::Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		Aurora::Renderer::Vertex(glm::vec3(-1.0f,-1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		Aurora::Renderer::Vertex(glm::vec3( 1.0f,-1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		Aurora::Renderer::Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		Aurora::Renderer::Vertex(glm::vec3( 1.0f,-1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		Aurora::Renderer::Vertex(glm::vec3( 1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f))
	};

	std::vector<unsigned int> quadIndices = {
		1, 2, 3,
		3, 4, 5
	};

	Quad::Quad()
	{
	}

	Quad::~Quad()
	{
	}

	void Quad::Create()
	{
		m_VertexArray = new Aurora::Renderer::VertexArray();
		m_VertexBuffer = new Aurora::Renderer::VertexBuffer(quadVertices);
		m_IndexBuffer = new Aurora::Renderer::IndexBuffer(quadIndices);

		m_VertexArray->Create();
		m_VertexBuffer->Create();
		m_IndexBuffer->Create();

		m_VertexArray->AttachVertexBuffer(*m_VertexBuffer);
		m_VertexArray->AttachIndexBuffer(*m_IndexBuffer);
	}

	void Quad::Destroy()
	{
		m_VertexArray->Destroy();
		m_VertexBuffer->Destroy();
		m_IndexBuffer->Destroy();
	}

	void Quad::Draw(Shader& shader, unsigned int frameBufferID)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		shader.Bind();
		shader.SetUniformMatrix4fv("model", model);
		m_VertexArray->Bind();
		if (frameBufferID > 0)
		{
			glBindTexture(GL_TEXTURE_2D, frameBufferID);
		}
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(quadIndices.size()), GL_UNSIGNED_INT, nullptr);
		m_VertexArray->Unbind();
		shader.Unbind();
	}

}