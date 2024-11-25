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
private:
	Application() = default;
	~Application() = default;

	bool m_WireframeMode = false;

	bool m_ShouldDestroyApplication = false;

	Aurora::Scene::SceneManager m_SceneManager;

	Aurora::Core::Window* m_Window = nullptr;
	bool m_IsRunning = true;

	glm::vec2 m_ViewportSize;

	Aurora::Renderer::Shader* m_Shader = nullptr;
	Aurora::Renderer::Shader* m_ScreenShader = nullptr;

	Aurora::Renderer::Renderer* m_Renderer = nullptr;

	Aurora::Renderer::Quad* m_FrameQuad = nullptr;
	Aurora::Renderer::FrameBuffer* m_FrameBuffer = nullptr;

	Aurora::Core::Log* m_Logger = nullptr;
};