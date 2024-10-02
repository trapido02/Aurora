#pragma once

#include <entt/entt.hpp>

#include "scene/components/TransformComponent.h"
#include "scene/components/MeshComponent.h"

#include "renderer/Model.h"

#include <iostream>

namespace Aurora::Scene {

	class RenderSystem
	{
	public:
		RenderSystem() = default;

		void Init(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			auto view = registry.view<TransformComponent, MeshComponent>();

			m_Models.reserve(view.size_hint());

			for (auto entity : view) {
				auto& transformComponent = view.get<TransformComponent>(entity);
				auto& meshComponent = view.get<MeshComponent>(entity);

				Aurora::Renderer::Model model(meshComponent.filePath);
				model.Create();
				m_Models.push_back(model);
			}
		}

		void Update(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer, float deltaTime)
		{
			auto view = registry.view<TransformComponent, MeshComponent>();
			size_t index = 0;

			for (auto entity : view) {
				auto& transformComponent = view.get<TransformComponent>(entity);
				auto& meshComponent = view.get<MeshComponent>(entity);

				// Create transformation matrix
				glm::mat4 transformationMatrix = glm::mat4(1.0f);
				transformationMatrix = glm::translate(transformationMatrix, transformComponent.position);
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				transformationMatrix = glm::rotate(transformationMatrix, transformComponent.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				transformationMatrix = glm::scale(transformationMatrix, transformComponent.size);

				// Get the model from the vector and draw it
				auto& model = m_Models[index++];
				model.Draw(*shader, transformationMatrix);
			}
		}

		void Exit(entt::registry& registry, Core::Window* window, Renderer::Shader* shader, Renderer::FrameBuffer* framebuffer)
		{
			for (auto& model : m_Models) {
				model.Destroy();
			}
			m_Models.clear();
		}
	private:
		std::vector<Aurora::Renderer::Model> m_Models;
	};

}
