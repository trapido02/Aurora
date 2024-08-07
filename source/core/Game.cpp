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

		// Create the texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		const std::string& texturePath = "resources/textures/texture.jpg";
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			Game::ProcessInput();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			glBindTexture(GL_TEXTURE_2D, texture);

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