#include "Game.h"

#include <iostream>
#include <string>

#include <stb_image/stb_image.h>

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
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		// Create the Shader, VBO, EBO and VAO
		m_Shader = new Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
		m_VertexArray = new Renderer::VertexArray;
		m_VertexBuffer = new Renderer::VertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexArray->Bind();
		m_VertexBuffer->Bind();

		Renderer::VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VertexArray->AttachBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = new Renderer::IndexBuffer(indices, 12);
		m_Texture = new Renderer::Texture("resources/textures/bird.png");

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			Game::ProcessInput();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Texture->Bind();

			m_Shader->Bind();
			m_VertexArray->Bind();

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

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Shutdown();
		}
	}

}