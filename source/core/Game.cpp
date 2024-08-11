#include "Game.h"

#include <iostream>
#include <string>
#include <vector>

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
		glEnable(GL_DEPTH_TEST);

		// Setup vertices
		Renderer::Vertex vertices[] = {
			Renderer::Vertex{ glm::vec3(-1.0f, 0.0f,  1.0f),	glm::vec2(0.0f, 0.0f) },
			Renderer::Vertex{ glm::vec3(-1.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 1.0f) },
			Renderer::Vertex{ glm::vec3( 1.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 1.0f) },
			Renderer::Vertex{ glm::vec3( 1.0f, 0.0f,  1.0f),	glm::vec2(1.0f, 0.0f) }
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		Renderer::Texture textures[] = {
			Renderer::Texture("resources/textures/texture.jpg"),
			Renderer::Texture("resources/textures/bird.png"),
		};

		std::vector<Renderer::Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Renderer::Vertex));
		std::vector<unsigned int> ind(indices, indices + sizeof(indices) / sizeof(unsigned int));
		std::vector<Renderer::Texture> tex(textures, textures + sizeof(textures) / sizeof(Renderer::Texture));

		m_Shader = new Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
		m_Mesh = new Renderer::Mesh(verts, ind, tex);

		while (m_IsRunning)
		{
			Game::ProcessInput();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)720 * 16 / 9 / (float)720, 0.1f, 100.0f);

			glm::mat4 mvp = projection * view * model;

			m_Shader->Bind();
			m_Shader->SetUniformMatrix4fv("mvp", mvp);
			m_Shader->Unbind();

			m_Mesh->Draw(*m_Shader);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
		delete m_Renderer;
		delete m_Shader;
		delete m_Mesh;
	}

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Shutdown();
		}
	}

}