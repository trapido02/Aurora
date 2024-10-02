#include <glad/glad.h>

#include "Application.h"

#include "scenes/MainScene.h"
#include "scenes/TestScene.h"

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
	Aurora::Core::WindowFlags windowFlags =
		Aurora::Core::WindowFlags::VSYNC_ENABLE |
		Aurora::Core::WindowFlags::DOCKING_ENABLE |
		Aurora::Core::WindowFlags::VIEWPORT_ENABLE;

	m_Window = new Aurora::Core::Window("Aurora", 720 * 16 / 9, 720, windowFlags);
	m_Window->Create();
	m_Window->SetCloseCallback([this]() { Application::Destroy(); });
	m_Window->SetResizeCallback([this](int width, int height) {
		glViewport(0, 0, width, height);
		m_FrameBuffer->Resize(width, height);
	});

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

	// Create and load scene
	m_SceneManager.CreateScene<MainScene>("MainScene");
	m_SceneManager.CreateScene<TestScene>("TestScene");

	m_Shader = new Aurora::Renderer::Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	m_ScreenShader = new Aurora::Renderer::Shader("resources/shaders/shader_screen.vert", "resources/shaders/shader_screen.frag");

	// Load Main scene
	m_SceneManager.LoadScene("MainScene", m_Window, m_Shader, m_FrameBuffer);

	m_FrameQuad = new Aurora::Renderer::Quad();
	m_FrameQuad->Create();

	int width, height;
	m_Window->GetSize(width, height);

	m_FrameBuffer = new Aurora::Renderer::FrameBuffer(width, height);
	m_FrameBuffer->Create();

	m_Shader->Create();
	m_ScreenShader->Create();
	m_ScreenShader->SetUniform1i("screenTexture", 0);

	float timeSinceLastFrame = 0.0f;

	while (m_IsRunning)
	{
		// Calculate deltaTime
		float deltaTime = glfwGetTime() - timeSinceLastFrame;
		timeSinceLastFrame = glfwGetTime();

		m_Renderer->Clear();
		m_Renderer->ClearColor(0.7f, 0.8f, 1.0f, 1.0f);

		m_FrameBuffer->Bind();
		m_Renderer->Clear();

		m_Window->PreUpdate();

		if (m_WireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		m_SceneManager.Update(m_Window, m_Shader, m_FrameBuffer, deltaTime);

		if (m_WireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		m_FrameBuffer->Unbind();
		m_FrameQuad->Draw(*m_ScreenShader, m_FrameBuffer->GetColorAttachmentID());

		Application::ImGuiRender();
		m_Window->PostUpdate();

		if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::ESCAPE))
		{
			Application::Destroy();
		}
		if (m_Window->GetKeyDown(Aurora::Core::KEYCODE::E, true))
		{
			if (m_WireframeMode)
			{
				m_WireframeMode = false;
			}
			else
			{
				m_WireframeMode = true;
			}
		}
	}
}

void Application::Destroy()
{
	m_IsRunning = false;

	m_SceneManager.UnloadScene(m_Window, m_Shader, m_FrameBuffer);

	m_Shader->Destroy();
	m_ScreenShader->Destroy();
	delete m_Shader;
	delete m_ScreenShader;

	m_FrameQuad->Destroy();
	m_FrameBuffer->Destroy();
	delete m_FrameQuad;
	delete m_FrameBuffer;

	m_Window->Destroy();
	m_Logger->Destroy();

	delete m_Renderer;
	delete m_Window;
	delete m_Logger;
}

void Application::ImGuiRender()
{
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::DockSpaceOverViewport(dockspace_id, viewport);

	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_FrameBuffer->Resize((int)viewportPanelSize.x, (int)viewportPanelSize.y);
			//m_Camera->Resize(viewportPanelSize.x, viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		}

		unsigned int textureID = m_FrameBuffer->GetColorAttachmentID();

		ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();
	}

	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Application::Destroy();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	{
		auto activeScene = m_SceneManager.GetCurrentScene();
		if (activeScene) {
			entt::registry& registry = activeScene->GetRegistry();

			ImGui::Begin("Entity List");

			auto view = registry.view<
				Aurora::Scene::TransformComponent,
				Aurora::Scene::CameraComponent,
				Aurora::Scene::AmbientLightComponent,
				Aurora::Scene::DirectionalLightComponent
			>();

			for (auto entity : registry.view<entt::entity>())
			{
				auto entityId = static_cast<int>(entity);
				if (ImGui::TreeNode(("Entity " + std::to_string(entityId)).c_str()))
				{
					if (registry.all_of<Aurora::Scene::TransformComponent>(entity))
					{
						auto& transformComponent = view.get<Aurora::Scene::TransformComponent>(entity);
						if (ImGui::TreeNode("Transform")) {
							ImGui::SliderFloat3("Position", &transformComponent.position.x, -10.0f, 10.0f);

							glm::vec3 rotationInDegrees = glm::degrees(transformComponent.rotation);
							ImGui::SliderFloat3("Rotation", &rotationInDegrees.x, -180.0f, 180.0f);
							transformComponent.rotation = glm::radians(rotationInDegrees);

							ImGui::SliderFloat3("Scale", &transformComponent.size.x, 0.1f, 10.0f);
							ImGui::TreePop();
						}
					}

					if (registry.all_of<Aurora::Scene::CameraComponent>(entity))
					{
						auto& cameraComponent = view.get<Aurora::Scene::CameraComponent>(entity);
						if (ImGui::TreeNode("Camera")) {
							ImGui::SliderFloat("FOV", &cameraComponent.fov, 0.0f, 180.0f);
							ImGui::InputFloat("Near Plane", &cameraComponent.nearPlane, 1.0f, 10.0f);
							ImGui::InputFloat("Far Plane", &cameraComponent.farPlane, 1.0f, 10.0f);
							ImGui::TreePop();
						}
					}

					if (registry.all_of<Aurora::Scene::AmbientLightComponent>(entity))
					{
						auto& ambientLightComponent = view.get<Aurora::Scene::AmbientLightComponent>(entity);
						if (ImGui::TreeNode("Light")) {
							ImGui::DragFloat3("Color", &ambientLightComponent.color.x, 0.1f, 0.0f, 1.0f);
							ImGui::DragFloat("Strength", &ambientLightComponent.strength, 0.1f, 0.0f, 10.0f);
							ImGui::TreePop();
						}
					}

					if (registry.all_of<Aurora::Scene::DirectionalLightComponent>(entity))
					{
						auto& directionalLightComponent = view.get<Aurora::Scene::DirectionalLightComponent>(entity);
						if (ImGui::TreeNode("Light")) {
							ImGui::DragFloat3("Direction", &directionalLightComponent.direction.x, 0.1f, -1.0f, 1.0f);
							ImGui::DragFloat3("Color", &directionalLightComponent.color.x, 0.1f, 0.0f, 1.0f);
							ImGui::DragFloat("Strength", &directionalLightComponent.strength, 0.1f, 0.0f, 10.0f);
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
			}

			ImGui::End();
		}
	}

	{
		auto scenes = m_SceneManager.GetScenes();

		ImGui::Begin("Scenes");

		for (const auto& pair : scenes)
		{
			const std::string& sceneName = pair.first;

			ImGui::PushID(sceneName.c_str());
			ImGui::Text(sceneName.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				m_SceneManager.LoadScene(sceneName, m_Window, m_Shader, m_FrameBuffer);
			}
			ImGui::PopID();
		}

		ImGui::End();
	}

	{
		// Debug info
		ImGui::Begin("Debug window");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
		ImGui::End();
	}
}