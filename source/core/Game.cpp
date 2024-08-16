#include "pch.h"

#include "Game.h"

#include <stb_image/stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// TODO:
// 
// - Add move constructors to OpenGL wrappers
// - Fix the rest of the wrappers to not violate C++'s rule of 3/5
// - Better error checking
//

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
		m_Window->SetVsync(true);
	}

	void Game::Run()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		m_Shader = new Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
		m_Model = new Renderer::Model("resources/models/Suzanne.gltf");
		m_Camera = new Renderer::Camera(m_Window, glm::vec3(0.0f, 0.0f, 2.0f));

		float timeSinceLastFrame = 0.0f;

		while (m_IsRunning)
		{
			Game::ProcessInput();

			// Calculate deltaTime
			float deltaTime = glfwGetTime() - timeSinceLastFrame;
			timeSinceLastFrame = glfwGetTime();

			m_Renderer->Clear();
			m_Renderer->ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Camera->Update(deltaTime, *m_Shader);

			m_Model->Draw(*m_Shader);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
		delete m_Renderer;
		delete m_Shader;
		delete m_Model;
		// Fix the memory issue with this!
		//delete m_Camera;
	}

	void Game::ProcessInput()
	{
		if (m_Window->GetKeyDown(Core::KEYCODE::ESCAPE))
		{
			Game::Shutdown();
		}
	}

}