#pragma once

#include "Aurora.h"

#include <memory>

class Application
{
public:
	// Get the singleton class instance
	static Application& getInstance()
	{
		static Application instance;
		return instance;
	};

	void Create();
	void Destroy();

	void Run();
	void ImGuiRender();
	void ProcessInput(float deltaTime);
private:
	Application() = default;
	~Application() = default;

	Aurora::Core::Window* m_Window = nullptr;
	bool m_IsRunning = true;

	bool m_WireframeMode = false;

	glm::vec3 m_BaseplateSize = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_BaseplatePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_DuckSize = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_DuckPosition = glm::vec3(0.0f, -0.1f, 0.0f);

	glm::vec3 m_AmbientLightColor = glm::vec3(0.7f, 0.8f, 1.0f);
	float m_AmbientLightStrength = 0.4f;

	glm::vec3 m_DirectionalLightDirection = glm::vec3(-0.5f, -1.0f, -0.5f);
	glm::vec3 m_DirectionalLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_DirectionalLightStrength = 1.0f;

	Aurora::Renderer::Renderer* m_Renderer = nullptr;
	Aurora::Renderer::Shader* m_Shader = nullptr;
	Aurora::Renderer::Camera* m_Camera = nullptr;

	Aurora::Renderer::Model* m_Baseplate = nullptr;
	Aurora::Renderer::Model* m_Duck = nullptr;

	Aurora::Renderer::AmbientLight* m_AmbientLight = nullptr;
	Aurora::Renderer::DirectionalLight* m_DirectionalLight = nullptr;

	Aurora::Core::Log* m_Logger = nullptr;
};