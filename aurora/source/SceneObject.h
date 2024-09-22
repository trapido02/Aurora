#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <ext/matrix_transform.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/matrix_decompose.hpp>

namespace Aurora {

	class SceneObject
	{
	public:
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetSize(const glm::vec3& scale);

		void Translate(const glm::vec3& axis, float amount, float deltaTime);
		void Rotate(const glm::vec3& axis, float amount, float deltaTime);
		void Scale(const glm::vec3& axis, float amount, float deltaTime);

		const glm::vec3 GetPosition() const;
		const glm::vec3 GetRotation() const;
		const glm::vec3 GetSize() const;

		const glm::vec3 GetGlobalUpVector() const;
		const glm::vec3 GetGlobalForwardVector() const;
		const glm::vec3 GetGlobalRightVector() const;

		const glm::vec3 GetLocalUpVector() const;
		const glm::vec3 GetLocalForwardVector() const;
		const glm::vec3 GetLocalRightVector() const;

		const glm::mat4 GetTransformMatrix() const;
	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Size = glm::vec3(1.0f, 1.0f, 1.0f);
	};

}