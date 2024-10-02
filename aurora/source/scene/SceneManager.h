#pragma once

#include "Scene.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace Aurora::Scene {

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		template<typename T>
		void CreateScene(const std::string& name)
		{
			static_assert(std::is_base_of<Scene, T>::value, "T must derive from Scene");
			m_Scenes[name] = std::make_shared<T>();
		}

		void LoadScene(const std::string& name, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer);
		void Update(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime);
		void UnloadScene(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer);

		std::unordered_map<std::string, std::shared_ptr<Scene>> GetScenes() { return m_Scenes; }
		std::shared_ptr<Scene> GetCurrentScene() { return m_CurrentScene; }
	private:
		std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};

}