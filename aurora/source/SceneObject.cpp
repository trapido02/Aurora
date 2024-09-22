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

	const glm::vec3& SceneObject::GetPosition() const
	{
		return m_Position;
	}

	const glm::vec3& SceneObject::GetRotation() const
	{
		return m_Rotation;
	}

	const glm::vec3& SceneObject::GetSize() const
	{
		return m_Size;
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

	const glm::mat4& SceneObject::GetTransformMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);

		// Apply position
		model = glm::translate(model, SceneObject::GetPosition());

		// Apply rotation for each axis
		model = glm::rotate(model, SceneObject::GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, SceneObject::GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, SceneObject::GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Apply scale
		model = glm::scale(model, SceneObject::GetSize());

		return model;
	}

}