#include "Editor.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GLAPIENTRY MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		INFO(message);
	if (severity == GL_DEBUG_SEVERITY_LOW)
		WARN(message);
	if (severity == GL_DEBUG_SEVERITY_MEDIUM)
		WARN(message);
	if (severity == GL_DEBUG_SEVERITY_HIGH)
		ERROR(message);
}

void Editor::Create()
{
	m_Window = new Aurora::Core::Window("Aurora", 720 * 16 / 9, 720);
	m_Window->Create();
	m_Window->SetCloseCallback([this]() { Editor::Destroy(); });
	m_Window->SetVsync(true);

	// Setup logger
	m_Logger = new Aurora::Core::Log();
	m_Logger->Create();
}

void Editor::Run()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEBUG_OUTPUT);

	glDebugMessageCallback(MessageCallback, 0);

	m_Shader = new Aurora::Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	m_Camera = new Aurora::Renderer::Camera(m_Window, glm::vec3(0.0f, 0.0f, 3.0f), 60.0f, 0.1f, 100.0f);
	m_Model = new Aurora::Renderer::Model("resources/models/Duck.gltf");

	m_AmbientLight = new Aurora::Renderer::AmbientLight(*m_Shader);
	m_DirectionalLight = new Aurora::Renderer::DirectionalLight(*m_Shader);

	m_Shader->Create();
	m_Model->Create();

	float timeSinceLastFrame = 0.0f;

	while (m_IsRunning)
	{
		// Calculate deltaTime
		float deltaTime = glfwGetTime() - timeSinceLastFrame;
		timeSinceLastFrame = glfwGetTime();

		m_Renderer->Clear();
		m_Renderer->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		m_Window->PreUpdate();

		m_Camera->Update(*m_Shader);

		// Update ambient light
		m_AmbientLight->SetColor(m_AmbientLightColor);
		m_AmbientLight->SetStrength(m_AmbientLightStrength);

		// Update directional light
		m_DirectionalLight->SetDirection(m_DirectionalLightDirection);
		m_DirectionalLight->SetColor(m_DirectionalLightColor);
		m_DirectionalLight->SetStrength(m_DirectionalLightStrength);

		// Scale the model and draw it
		m_Model->SetScale(m_ModelSize);
		m_Model->SetPosition(m_ModelPosition);

		m_Model->Draw(*m_Shader);

		Editor::ImGuiRender();

		m_Window->PostUpdate();
		Editor::ProcessInput(deltaTime);
	}
}

void Editor::Destroy()
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

	delete m_AmbientLight;
	delete m_DirectionalLight;

	delete m_Logger;
}

void Editor::ImGuiRender()
{
	ImGui::DragFloat3("Size", &m_ModelSize.x, 0.1f, 0.1f, 10.0f);
	ImGui::DragFloat3("Position", &m_ModelPosition.x, 0.1f, -10000.0f, 10000.0f);

	if (ImGui::CollapsingHeader("Ambient Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::PushID("AmbientLight");
		ImGui::DragFloat3("Color", &m_AmbientLightColor.x, 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("Strength", &m_AmbientLightStrength, 0.1f, 0.0f, 10.0f);
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Directional Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::PushID("DirectionalLight");
		ImGui::DragFloat3("Direction", &m_DirectionalLightDirection.x, 0.1f, -1.0f, 1.0f);
		ImGui::DragFloat3("Color", &m_DirectionalLightColor.x, 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("Strength", &m_DirectionalLightStrength, 0.1f, 0.0f, 10.0f);
		ImGui::PopID();
	}

	// Debug info
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Separator();
	ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
}

void Editor::ProcessInput(float deltaTime)
{
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::ESCAPE))
	{
		Editor::Destroy();
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::E, true))
	{
		if (!m_WireframeMode)
		{
			m_WireframeMode = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			m_WireframeMode = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	// Move camera
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::W))
	{
		m_Camera->MoveForward(deltaTime);
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::S))
	{
		m_Camera->MoveBackward(deltaTime);
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::A))
	{
		m_Camera->MoveLeft(deltaTime);
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::D))
	{
		m_Camera->MoveRight(deltaTime);
	}

	// Unlock/lock mouse cursor
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::F, true))
	{
		if (!m_Window->IsMouseLocked())
		{
			m_Window->LockMouseCursor();
		}
		else
		{
			m_Window->UnlockMouseCursor();
		}
	}
}