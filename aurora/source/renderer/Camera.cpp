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

	void Camera::Update(Shader& shader)
	{
		if (m_Window->IsMouseLocked())
		{
			ProcessMouse();
		}
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		int windowWidth, windowHeight;
		m_Window->GetSize(windowWidth, windowHeight);

		if (windowWidth != NULL || windowHeight != NULL)
		{
			glm::vec3 rotation = Camera::GetRotation();
			glm::vec3 up = Camera::GetGlobalUpVector();
			glm::vec3 forward = Camera::GetLocalForwardVector();
			glm::vec3 position = Camera::GetPosition();

			view = glm::lookAt(position, position + forward, glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(glm::radians(m_Fov), (float)windowWidth / (float)windowHeight, m_NearPlane, m_FarPlane);

			shader.Bind();
			shader.SetUniformMatrix4fv("view", view);
			shader.SetUniformMatrix4fv("projection", projection);
			shader.Unbind();
		}
	}

	void Camera::ProcessMouse()
	{
		double mouseX, mouseY;
		m_Window->GetMousePosition(mouseX, mouseY);

		int windowWidth, windowHeight;
		m_Window->GetSize(windowWidth, windowHeight);

		float rotX = m_Sensitivity * ((float)mouseY - ((float)windowHeight / 2.0f)) / (float)windowHeight;
		float rotY = m_Sensitivity * ((float)mouseX - ((float)windowWidth / 2.0f)) / (float)windowWidth;

		glm::vec3 rotation = Camera::GetRotation();

		rotation.x -= glm::radians(rotX);
		rotation.y -= glm::radians(rotY);

		if (rotation.x > glm::radians(89.0f))
			rotation.x = glm::radians(89.0f);
		if (rotation.x < glm::radians(-89.0f))
			rotation.x = glm::radians(-89.0f);

		if (rotation.y > glm::radians(180.0f))
			rotation.y = glm::radians(-180.0f);
		if (rotation.y < glm::radians(-180.0f))
			rotation.y = glm::radians(180.0f);

		Camera::SetRotation(rotation);

		m_Window->SetCursorPosition(((float)windowWidth / 2), ((float)windowHeight / 2));
	}

}