#include "Game.h"

#include <iostream>
#include <string>

#include <stb_image/stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
		m_Shader->Bind();

		m_IndexBuffer = new Renderer::IndexBuffer(indices, 12);
		m_Texture1 = new Renderer::Texture("resources/textures/texture.jpg");
		m_Texture2 = new Renderer::Texture("resources/textures/bird.png");

		m_Shader->SetUniform1i("texture1", 0);
		m_Shader->SetUniform1i("texture2", 1);

		m_Shader->Unbind();
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();

		while (m_IsRunning)
		{
			Game::ProcessInput();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Texture1->Bind();
			m_Texture2->Bind(1);

			m_Shader->Bind();
			m_VertexArray->Bind();

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)720 * 16 / 9 / (float)720, 0.1f, 100.0f);

			glm::mat4 mvp = projection * view * model;

			m_Shader->SetUniformMatrix4fv("mvp", mvp);

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
		delete m_Texture1;
		delete m_Texture2;
	}

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Shutdown();
		}
	}

}