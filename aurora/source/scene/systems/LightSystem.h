#pragma once

#include <entt/entt.hpp>

#include "scene/components/AmbientLightComponent.h"
#include "scene/components/DirectionalLightComponent.h"

#include "renderer/light/AmbientLight.h"
#include "renderer/light/DirectionalLight.h"

namespace Aurora::Scene {

	class LightSystem
	{
	public:
		LightSystem() = default;

		void Init(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			// Ambient light
			auto ambientView = registry.view<AmbientLightComponent>();
			for (auto entity : ambientView) {
				auto& ambientLightComponent = ambientView.get<AmbientLightComponent>(entity);

				m_AmbientLight = new Renderer::AmbientLight(*shader);
			}

			// Directional light
			auto directionalView = registry.view<DirectionalLightComponent>();
			for (auto entity : directionalView) {
				auto& directionalLightComponent = directionalView.get<DirectionalLightComponent>(entity);

				m_DirectionalLight = new Renderer::DirectionalLight(*shader);
			}
		}

		void Update(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime)
		{
			// Ambient light
			auto ambientView = registry.view<AmbientLightComponent>();
			for (auto entity : ambientView) {
				auto& ambientLightComponent = ambientView.get<AmbientLightComponent>(entity);

				m_AmbientLight->SetColor(ambientLightComponent.color);
				m_AmbientLight->SetStrength(ambientLightComponent.strength);
			}

			// Directional light
			auto directionalView = registry.view<DirectionalLightComponent>();
			for (auto entity : directionalView) {
				auto& directionalLightComponent = directionalView.get<DirectionalLightComponent>(entity);

				m_DirectionalLight->SetDirection(directionalLightComponent.direction);
				m_DirectionalLight->SetColor(directionalLightComponent.color);
				m_DirectionalLight->SetStrength(directionalLightComponent.strength);
			}
		}

		void Exit(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			delete m_AmbientLight;
			delete m_DirectionalLight;
		}
	private:
		// Will only be one ambient light and directional light which is why its not a vector
		Renderer::AmbientLight* m_AmbientLight = nullptr;
		Renderer::DirectionalLight* m_DirectionalLight = nullptr;
	};

}
