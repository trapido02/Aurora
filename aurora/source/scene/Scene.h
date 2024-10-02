#pragma once

#include <entt/entt.hpp>

#include "core/Window.h"
#include "renderer/Shader.h"
#include "renderer/FrameBuffer.h"

namespace Aurora::Scene {

	class Scene
	{
	public:
		Scene() : m_Registry() {}
		virtual ~Scene() = default;

		virtual void OnAttach(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer) = 0;
		virtual void OnUpdate(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime) = 0;
		virtual void OnDetach(Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer) = 0;

		entt::registry& GetRegistry() { return m_Registry; }
	private:
		entt::registry m_Registry;
	};

}