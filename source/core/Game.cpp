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
		// Setup vertices
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, // top right
			 0.5f, -0.5f, 0.0f, // bottom right
			-0.5f,  0.5f, 0.0f, // top left 

			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, // top left 
			 0.5f, -0.5f, 0.0f  // bottom right
		};

		// Create the Shader, VBO and VAO
		m_Shader = new Renderer::Shader(vertexShaderSource, fragmentShaderSource);
		m_VertexArray = new Renderer::VertexArray;
		m_VertexBuffer = new Renderer::VertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexArray->Bind();
		m_VertexBuffer->Bind();

		Renderer::VertexBufferLayout layout(3);
		m_VertexArray->AttachBuffer(*m_VertexBuffer, layout);

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
	}

}