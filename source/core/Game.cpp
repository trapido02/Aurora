#include "Game.h"

#include <iostream>
#include <string>

const char* vertexShaderSource = R"(
#version 450 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
const char* fragmentShaderSource = R"(
#version 450 core
out vec4 FragColor;

uniform vec4 ourColor;

void main()
{
	FragColor = ourColor;
	//FragColor = vec4(0.6f, 0.4f, 1.0f, 1.0f);
}
)";

namespace Core {

	void Game::Create()
	{
		m_Window = new Window("Aurora", 720 * 16 / 9, 720);
		m_Window->SetVsync(true);
	}

	void Game::Run()
	{
		// Setup vertices
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		unsigned int indices[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		// Create the Shader, VBO, EBO and VAO
		m_Shader = new Renderer::Shader(vertexShaderSource, fragmentShaderSource);
		m_VertexArray = new Renderer::VertexArray;
		m_VertexBuffer = new Renderer::VertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexArray->Bind();
		m_VertexBuffer->Bind();

		Renderer::VertexBufferLayout layout(3);
		m_VertexArray->AttachBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = new Renderer::IndexBuffer(indices, 12);

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Shader->Bind();
			m_VertexArray->Bind();

			float color = sin(glfwGetTime()) / 2.0f + 0.5f;
			m_Shader->SetUniform4f("ourColor", color, color, 0.0f, 1.0f);

			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
		delete m_Renderer;
		delete m_Shader;
		delete m_VertexArray;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

}