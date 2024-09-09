#include "pch.h"

#include "Game.h"

#include <stb_image/stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void GLAPIENTRY MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

namespace Core {

	void Game::Create()
	{
		m_Window = new Window("Aurora", 720 * 16 / 9, 720);
		m_Window->Create();
		m_Window->SetVsync(true);
	}

	void Game::Run()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		m_Shader = new Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
		m_Camera = new Renderer::Camera(m_Window, glm::vec3(0.0f, 0.0f, 3.0f), 60.0f, 0.1f, 100.0f);
		m_Model = new Renderer::Model("resources/models/Suzanne.gltf");

		m_Shader->Create();
		m_Model->Create();

		float timeSinceLastFrame = 0.0f;

		while (m_IsRunning)
		{
			// Calculate deltaTime
			float deltaTime = glfwGetTime() - timeSinceLastFrame;
			timeSinceLastFrame = glfwGetTime();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Camera->Update(deltaTime, *m_Shader);

			m_Model->Draw(*m_Shader);

			m_Window->OnUpdate();
			Game::ProcessInput();
		}
	}

	void Game::Destroy()
	{
		m_IsRunning = false;

		m_Window->Destroy();
		m_Shader->Destroy();
		m_Model->Destroy();

		delete m_Window;
		delete m_Renderer;
		delete m_Shader;
		delete m_Camera;
		delete m_Model;
	}

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Destroy();
		}
	}

}