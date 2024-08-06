#include "Game.h"

#include <iostream>
#include <string>

const char* vertexShaderSource = R"(
#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
}
)";
const char* fragmentShaderSource = R"(
#version 450 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0f);
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
			// positions		 // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f // top
		};

		// Create the Shader, VBO, EBO and VAO
		m_Shader = new Renderer::Shader(vertexShaderSource, fragmentShaderSource);
		m_VertexArray = new Renderer::VertexArray;
		m_VertexBuffer = new Renderer::VertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexArray->Bind();
		m_VertexBuffer->Bind();

		Renderer::VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_VertexArray->AttachBuffer(*m_VertexBuffer, layout);

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			Game::ProcessInput();

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
		delete m_Renderer;
		delete m_Shader;
		delete m_VertexArray;
		delete m_VertexBuffer;
	}

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Shutdown();
		}
	}

}