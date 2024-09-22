#include "pch.h"

#include "SceneObject.h"

namespace Aurora {

	void SceneObject::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void SceneObject::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
	}

	void SceneObject::SetSize(const glm::vec3& size)
	{
		m_Size = size;
	}

	void SceneObject::Translate(const glm::vec3& axis, float amount, float deltaTime)
	{
		glm::vec3 newPosition = axis * amount * deltaTime;
		m_Position += newPosition;
	}

	void SceneObject::Rotate(const glm::vec3& axis, float amount, float deltaTime)
	{
		glm::vec3 newRotation = axis * amount * deltaTime;
		m_Rotation += newRotation;
	}

	void SceneObject::Scale(const glm::vec3& axis, float amount, float deltaTime)
	{
		glm::vec3 newSize = axis * amount * deltaTime;
		m_Size += newSize;
	}

	const glm::vec3 SceneObject::GetPosition() const
	{
		return m_Position;
	}

	const glm::vec3 SceneObject::GetRotation() const
	{
		return m_Rotation;
	}

	const glm::vec3 SceneObject::GetSize() const
	{
		return m_Size;
	}

	const glm::vec3 SceneObject::GetGlobalUpVector() const
	{
		return glm::vec3(0.0f, 1.0f, 0.0f);
	}

	const glm::vec3 SceneObject::GetGlobalForwardVector() const
	{
		return glm::vec3(0.0f, 0.0f, -1.0f);
	}

	const glm::vec3 SceneObject::GetGlobalRightVector() const
	{
		return glm::vec3(1.0f, 0.0f, 0.0f);
	}

	const glm::vec3 SceneObject::GetLocalUpVector() const
	{
		return glm::normalize(glm::cross(GetLocalRightVector(), GetLocalForwardVector()));
	}

	const glm::vec3 SceneObject::GetLocalForwardVector() const
	{
		glm::mat4 transformation = SceneObject::GetTransformMatrix();

		return glm::normalize(glm::vec3(-transformation[2]));
	}

	const glm::vec3 SceneObject::GetLocalRightVector() const
	{
		return glm::normalize(glm::cross(GetLocalForwardVector(), GetGlobalUpVector()));
	}

	const glm::mat4 SceneObject::GetTransformMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, m_Size);

		model = glm::rotate(model, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

		model = glm::translate(model, m_Position);

		return model;
	}

}