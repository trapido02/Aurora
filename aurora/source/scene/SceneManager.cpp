#include "pch.h"

#include "SceneManager.h"

namespace Aurora::Scene {

	SceneManager::SceneManager()
		: m_CurrentScene(nullptr)
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::LoadScene(const std::string& name, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
	{
		if (m_CurrentScene) {
			m_CurrentScene->OnDetach(window, shader, framebuffer); // Clean up the current scene
		}
		m_CurrentScene = m_Scenes[name];
		if (m_CurrentScene) {
			m_CurrentScene->OnAttach(window, shader, framebuffer); // Initialize the new scene
		}
	}

	void SceneManager::Update(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime)
	{
		if (m_CurrentScene) {
			m_CurrentScene->OnUpdate(window, shader, framebuffer, deltaTime);
		}
	}

	void SceneManager::UnloadScene(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
	{
		if (m_CurrentScene) {
			m_CurrentScene->OnDetach(window, shader, framebuffer);
		}
		m_CurrentScene = nullptr;
	}

}