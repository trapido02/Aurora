#include "pch.h"

#include "Skybox.h"

std::vector<Aurora::Renderer::Vertex> cubeVertices = {
	// First face
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),

	// Second face
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),

	// Third face
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),

	// Fourth face
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),

	// Fifth face
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),

	// Sixth face
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
	Aurora::Renderer::Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
};

namespace Aurora::Renderer {

	Skybox::Skybox(std::vector<std::string> texturePaths)
		: m_TexturePaths(texturePaths)
	{
	}

	Skybox::~Skybox()
	{
	}

	void Skybox::Create()
	{
		m_VertexArray = new VertexArray();
		m_VertexArray->Create();

		m_VertexBuffer = new VertexBuffer(cubeVertices);
		m_VertexBuffer->Create();

		m_VertexArray->AttachVertexBuffer(*m_VertexBuffer);

		m_Cubemap = new Cubemap(m_TexturePaths);
		m_Cubemap->Create();
	}

	void Skybox::Destroy()
	{
		m_VertexArray->Destroy();
		m_VertexBuffer->Destroy();
		m_Cubemap->Destroy();
	}

	void Skybox::Draw(Shader& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		glDepthFunc(GL_LEQUAL);
		shader.Bind();

		glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));;

		shader.SetUniformMatrix4fv("view", view);
		shader.SetUniformMatrix4fv("projection", projectionMatrix);

		m_VertexArray->Bind();
		m_Cubemap->SetActiveTexture(0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_VertexArray->Unbind();
		shader.Unbind();
		glDepthFunc(GL_LESS);
	}

}