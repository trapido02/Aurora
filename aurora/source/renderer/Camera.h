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
		Camera(Core::Window* window, glm::vec3 position, float fov, float nearPlane, float farPlane);
		~Camera();

		void Update(Shader& shader);

		void Translate(const glm::vec3& direction, float deltaTime);
		void Rotate(const glm::vec3& axis, float angle, float deltaTime);

		void SetPosition(const glm::vec3& position);
		void SetOrientation(const glm::vec3& orientation);
		
		glm::vec3 GetPosition() const;
		glm::vec3 GetOrientation() const;

		glm::vec3 GetUp() const;

		void MoveForward(float deltaTime);
		void MoveBackward(float deltaTime);
		void MoveLeft(float deltaTime);
		void MoveRight(float deltaTime);
	private:
		Core::Window* m_Window;

		float m_Fov;
		float m_NearPlane;
		float m_FarPlane;

		float m_Speed = 2.0f;
		float m_Sensitivity = 50.0f;

		glm::vec3 m_Position;
		glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		void ProcessMouse();
	};

}