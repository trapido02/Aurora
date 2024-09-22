#include "Application.h"

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

void Application::Create()
{
	m_Window = new Aurora::Core::Window("Aurora", 720 * 16 / 9, 720);
	m_Window->Create();
	m_Window->SetCloseCallback([this]() { Application::Destroy(); });
	m_Window->SetVsync(true);

	// Setup logger
	m_Logger = new Aurora::Core::Log();
	m_Logger->Create();
}

void Application::Run()
{
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEBUG_OUTPUT);

	glDebugMessageCallback(MessageCallback, 0);

	m_Shader = new Aurora::Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	m_Camera = new Aurora::Renderer::Camera(m_Window, 60.0f, 0.1f, 100.0f);
	m_Camera->SetPosition(glm::vec3(-1.0f, 1.0f, 0.0f));

	// Load models
	m_Baseplate = new Aurora::Renderer::Model("resources/models/baseplate.gltf");
	m_Duck = new Aurora::Renderer::Model("resources/models/Duck.gltf");

	m_AmbientLight = new Aurora::Renderer::AmbientLight(*m_Shader);
	m_DirectionalLight = new Aurora::Renderer::DirectionalLight(*m_Shader);

	m_Shader->Create();

	m_Baseplate->Create();
	m_Duck->Create();

	float timeSinceLastFrame = 0.0f;

	while (m_IsRunning)
	{
		// Calculate deltaTime
		float deltaTime = glfwGetTime() - timeSinceLastFrame;
		timeSinceLastFrame = glfwGetTime();

		m_Renderer->Clear();
		m_Renderer->ClearColor(0.7f, 0.8f, 1.0f, 1.0f);

		m_Window->PreUpdate();

		m_Camera->Update(*m_Shader);

		// Update ambient light
		m_AmbientLight->SetColor(m_AmbientLightColor);
		m_AmbientLight->SetStrength(m_AmbientLightStrength);

		// Update directional light
		m_DirectionalLight->SetDirection(m_DirectionalLightDirection);
		m_DirectionalLight->SetColor(m_DirectionalLightColor);
		m_DirectionalLight->SetStrength(m_DirectionalLightStrength);

		// Scale the models and draw it
		m_Baseplate->SetSize(m_BaseplateSize);
		m_Baseplate->SetPosition(m_BaseplatePosition);
		m_Baseplate->SetRotation(glm::radians(m_BaseplateRotation));

		m_Duck->SetSize(m_DuckSize);
		m_Duck->SetPosition(m_DuckPosition);
		m_Duck->SetRotation(glm::radians(m_DuckRotation));

		m_Baseplate->Draw(*m_Shader);
		m_Duck->Draw(*m_Shader);

		Application::ImGuiRender();

		m_Window->PostUpdate();
		Application::ProcessInput(deltaTime);
	}
}

void Application::Destroy()
{
	m_IsRunning = false;

	m_Window->Destroy();
	m_Shader->Destroy();

	m_Baseplate->Destroy();
	m_Duck->Destroy();

	delete m_Window;
	delete m_Renderer;
	delete m_Shader;
	delete m_Camera;

	delete m_Baseplate;
	delete m_Duck;

	delete m_AmbientLight;
	delete m_DirectionalLight;

	delete m_Logger;
}

void Application::ImGuiRender()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		glm::vec3 cameraPosition = m_Camera->GetPosition();
		glm::vec3 cameraRotation = glm::degrees(m_Camera->GetRotation());
		glm::vec3 cameraSize = m_Camera->GetSize();

		ImGui::PushID("Camera");
		ImGui::Text("Position: (%.3f, %.3f, %.3f)", cameraPosition.x, cameraPosition.y, cameraPosition.z);
		ImGui::Text("Rotation: (%.3f, %.3f, %.3f)", cameraRotation.x, cameraRotation.y, cameraRotation.z);
		ImGui::Text("Size: (%.3f, %.3f, %.3f)", cameraSize.x, cameraSize.y, cameraSize.z);
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Baseplate"))
	{
		glm::vec3 baseplatePosition = m_Baseplate->GetPosition();
		glm::vec3 baseplateRotation = m_Baseplate->GetRotation();
		glm::vec3 baseplateSize = m_Baseplate->GetSize();

		ImGui::PushID("Baseplate");
		ImGui::Text("Size: (%.3f, %.3f, %.3f)", baseplateSize.x, baseplateSize.y, baseplateSize.z);
		ImGui::DragFloat3("Size", &m_BaseplateSize.x, 0.1f, 0.1f, 10.0f);
		ImGui::Text("Position: (%.3f, %.3f, %.3f)", baseplatePosition.x, baseplatePosition.y, baseplatePosition.z);
		ImGui::DragFloat3("Position", &m_BaseplatePosition.x, 0.1f, -10000.0f, 10000.0f);
		ImGui::Text("Rotation: (%.3f, %.3f, %.3f)", baseplateRotation.x, baseplateRotation.y, baseplateRotation.z);
		ImGui::DragFloat3("Rotation", &m_BaseplateRotation.x, 1.0f, -180.0f, 180.0f);
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Duck"))
	{
		glm::vec3 duckPosition = m_Duck->GetPosition();
		glm::vec3 duckRotation = m_Duck->GetRotation();
		glm::vec3 duckSize = m_Duck->GetSize();

		ImGui::PushID("Duck");
		ImGui::Text("Size: (%.3f, %.3f, %.3f)", duckSize.x, duckSize.y, duckSize.z);
		ImGui::DragFloat3("Size", &m_DuckSize.x, 0.1f, 0.1f, 10.0f);
		ImGui::Text("Position: (%.3f, %.3f, %.3f)", duckPosition.x, duckPosition.y, duckPosition.z);
		ImGui::DragFloat3("Position", &m_DuckPosition.x, 0.1f, -10000.0f, 10000.0f);
		ImGui::Text("Rotation: (%.3f, %.3f, %.3f)", duckRotation.x, duckRotation.y, duckRotation.z);
		ImGui::DragFloat3("Rotation", &m_DuckRotation.x, 1.0f, -180.0f, 180.0f);
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Ambient Light"))
	{
		ImGui::PushID("AmbientLight");
		ImGui::DragFloat3("Color", &m_AmbientLightColor.x, 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("Strength", &m_AmbientLightStrength, 0.1f, 0.0f, 10.0f);
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Directional Light"))
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

void Application::ProcessInput(float deltaTime)
{
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::ESCAPE))
	{
		Application::Destroy();
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
	glm::vec3 direction(0.0f);
	bool shouldMove = false;

	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::W))
	{
		glm::vec3 forward = m_Camera->GetLocalForwardVector();
		direction += forward;
		shouldMove = true;
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::S))
	{
		glm::vec3 forward = m_Camera->GetLocalForwardVector();
		direction -= forward;
		shouldMove = true;
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::A))
	{
		glm::vec3 right = m_Camera->GetLocalRightVector();
		direction -= right;
		shouldMove = true;
	}
	if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::D))
	{
		glm::vec3 right = m_Camera->GetLocalRightVector();
		direction += right;
		shouldMove = true;
	}

	if (shouldMove && (direction != glm::vec3(0.0f, 0.0f, 0.0f)))
	{
		m_Camera->Translate(glm::normalize(direction), 5.0f, deltaTime);
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