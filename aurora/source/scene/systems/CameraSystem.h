#pragma once

#include <entt/entt.hpp>

#include "scene/components/TransformComponent.h"
#include "scene/components/CameraComponent.h"

#include "renderer/Camera.h"

namespace Aurora::Scene {

	class CameraSystem
	{
	public:
		CameraSystem() = default;

		void Init(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) {
				auto& transformComponent = view.get<TransformComponent>(entity);
				auto& cameraComponent = view.get<CameraComponent>(entity);

				m_Camera = new Renderer::Camera(window, cameraComponent.fov, cameraComponent.nearPlane, cameraComponent.farPlane);
			}
		}

		void Update(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime)
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) {
				auto& transformComponent = view.get<TransformComponent>(entity);
				auto& cameraComponent = view.get<CameraComponent>(entity);

				// Create transformation matrix
				glm::mat4 transformationMatrix = glm::mat4(1.0f);
				transformationMatrix = glm::translate(transformationMatrix, transformComponent.position);
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				transformationMatrix = glm::scale(transformationMatrix, transformComponent.size);

				// Get framebuffer size
				int width, height;
				framebuffer->GetSize(width, height);

				glm::vec3 forward = glm::normalize(glm::vec3(-transformationMatrix[2]));

				glm::mat4 viewMatrix = glm::lookAt(transformComponent.position, transformComponent.position + forward, glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 projectionMatrix = glm::perspective(glm::radians(cameraComponent.fov), (float)width / (float)height, cameraComponent.nearPlane, cameraComponent.farPlane);

				m_Camera->Update(*shader, viewMatrix, projectionMatrix);
				if (cameraComponent.skybox != nullptr && cameraComponent.skyboxShader != nullptr)
				{
					cameraComponent.skybox->Draw(*cameraComponent.skyboxShader, viewMatrix, projectionMatrix);
				}
			}
		}

		void Exit(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			delete m_Camera;
		}
	private:
		// Will only be a single camera which is why its not a vector
		Renderer::Camera* m_Camera = nullptr;
		Renderer::Skybox* m_Skybox = nullptr;
	};

}
