#pragma once

#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Texture.h"
#include "renderer/Model.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"
#include "renderer/light/DirectionalLight.h"
#include "renderer/light/AmbientLight.h"
#include "Window.h"
#include "Log.h"

#include <memory>

namespace Core {
	
	class Game
	{
	public:
		// Get the singleton class instance
		static Game& getInstance()
		{
			static Game instance;
			return instance;
		};

		void Create();
		void Destroy();

		void Run();
		void ImGuiRender();
		void ProcessInput(float deltaTime);
	private:
		Game() = default;
		~Game() = default;

		Window* m_Window = nullptr;
		bool m_IsRunning = true;

		bool m_WireframeMode = false;

		glm::vec3 m_ModelSize = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_ModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 m_AmbientLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_AmbientLightStrength = 0.1f;

		glm::vec3 m_DirectionalLightDirection = glm::vec3(-0.5f, -1.0f, -0.5f);
		glm::vec3 m_DirectionalLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_DirectionalLightStrength = 1.0f;

		Renderer::Renderer* m_Renderer = nullptr;
		Renderer::Shader* m_Shader = nullptr;
		Renderer::Camera* m_Camera = nullptr;
		Renderer::Model* m_Model = nullptr;

		Renderer::AmbientLight* m_AmbientLight = nullptr;
		Renderer::DirectionalLight* m_DirectionalLight = nullptr;

		Log* m_Logger = nullptr;
	};

}