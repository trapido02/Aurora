#pragma once

#include "Aurora.h"

#include <memory>

class Editor
{
public:
	// Get the singleton class instance
	static Editor& getInstance()
	{
		static Editor instance;
		return instance;
	};

	void Create();
	void Destroy();

	void Run();
	void ImGuiRender();
	void ProcessInput(float deltaTime);
private:
	Editor() = default;
	~Editor() = default;

	Aurora::Core::Window* m_Window = nullptr;
	bool m_IsRunning = true;

	bool m_WireframeMode = false;

	glm::vec3 m_ModelSize = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_ModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_AmbientLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_AmbientLightStrength = 0.1f;

	glm::vec3 m_DirectionalLightDirection = glm::vec3(-0.5f, -1.0f, -0.5f);
	glm::vec3 m_DirectionalLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_DirectionalLightStrength = 1.0f;

	Aurora::Renderer::Renderer* m_Renderer = nullptr;
	Aurora::Renderer::Shader* m_Shader = nullptr;
	Aurora::Renderer::Camera* m_Camera = nullptr;
	Aurora::Renderer::Model* m_Model = nullptr;

	Aurora::Renderer::AmbientLight* m_AmbientLight = nullptr;
	Aurora::Renderer::DirectionalLight* m_DirectionalLight = nullptr;

	Aurora::Core::Log* m_Logger = nullptr;
};