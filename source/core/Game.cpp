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
void main()
{
	FragColor = vec4(0.6f, 0.4f, 1.0f, 1.0f);
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
		m_Shader = new Renderer::Shader(vertexShaderSource, fragmentShaderSource);
		m_VertexArray = new Renderer::VertexArray;

		// Setup vertices
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f
		};

		// Create the VBO and VAO
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		m_VertexArray->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		m_VertexArray->Unbind();
		glBindVertexArray(0);

		while (m_IsRunning)
		{
			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
	}

}