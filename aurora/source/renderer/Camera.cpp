#include "pch.h"

#include "Camera.h"

namespace Aurora::Renderer {

	Camera::Camera(Core::Window* window, float fov, float nearPlane, float farPlane)
		: m_Window(window), m_Fov(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Update(Shader& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		int windowWidth, windowHeight;
		m_Window->GetSize(windowWidth, windowHeight);

		if (windowWidth != NULL || windowHeight != NULL)
		{
			shader.Bind();
			shader.SetUniformMatrix4fv("view", viewMatrix);
			shader.SetUniformMatrix4fv("projection", projectionMatrix);
			shader.Unbind();
		}
	}

}