#pragma once

#include "Shader.h"
#include "core/Window.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>

namespace Aurora::Renderer {

	class Camera
	{
	public:
		Camera(Core::Window* window, float fov, float nearPlane, float farPlane);
		~Camera();

		void Update(Shader& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	private:
		Core::Window* m_Window;

		float m_Fov;
		float m_NearPlane;
		float m_FarPlane;

		float m_Speed = 2.0f;
		float m_Sensitivity = 50.0f;
	};

}