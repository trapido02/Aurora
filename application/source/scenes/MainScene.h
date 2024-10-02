#pragma once

#include "Aurora.h"

class MainScene : public Aurora::Scene::Scene
{
public:
	MainScene() = default;
	~MainScene() = default;

	void OnAttach(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer) override;
	void OnUpdate(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer, float deltaTime) override;
	void OnDetach(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer) override;
private:
	entt::registry& m_Registry = GetRegistry();
	Aurora::Scene::RenderSystem m_RenderSystem;
	Aurora::Scene::CameraSystem m_CameraSystem;
	Aurora::Scene::LightSystem m_LightSystem;

	Aurora::Renderer::Shader* m_SkyboxShader = nullptr;

	// Entities
	entt::entity m_Camera = entt::null;
	entt::entity m_Duck = entt::null;
	entt::entity m_Baseplate = entt::null;
	entt::entity m_AmbientLight = entt::null;
	entt::entity m_DirectionalLight = entt::null;
};