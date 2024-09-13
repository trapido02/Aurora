#include "pch.h"

#include "Camera.h"

namespace Renderer {
	Camera::Camera(Core::Window* window, glm::vec3 position, float fov, float nearPlane, float farPlane)
		: m_Window(window), m_Position(position), m_Fov(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane)
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
			view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
			projection = glm::perspective(glm::radians(m_Fov), (float)windowWidth / (float)windowHeight, m_NearPlane, m_FarPlane);

			shader.Bind();
			shader.SetUniformMatrix4fv("view", view);
			shader.SetUniformMatrix4fv("projection", projection);
			shader.Unbind();
		}
	}

	void Camera::MoveForward(float deltaTime)
	{
		float velocity = m_Speed * deltaTime;
		m_Position += velocity * m_Orientation;
	}

	void Camera::MoveBackward(float deltaTime)
	{
		float velocity = m_Speed * deltaTime;
		m_Position -= velocity * m_Orientation;
	}

	void Camera::MoveLeft(float deltaTime)
	{
		float velocity = m_Speed * deltaTime;
		m_Position -= velocity * glm::normalize(glm::cross(m_Orientation, m_Up));
	}

	void Camera::MoveRight(float deltaTime)
	{
		float velocity = m_Speed * deltaTime;
		m_Position += velocity * glm::normalize(glm::cross(m_Orientation, m_Up));
	}

	void Camera::ProcessMouse()
	{
		double mouseX, mouseY;
		m_Window->GetMousePosition(mouseX, mouseY);

		int windowWidth, windowHeight;
		m_Window->GetSize(windowWidth, windowHeight);

		float rotX = m_Sensitivity * ((float)mouseY - ((float)windowHeight / 2.0f)) / (float)windowHeight;
		float rotY = m_Sensitivity * ((float)mouseX - ((float)windowWidth / 2.0f)) / (float)windowWidth;

		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Orientation = newOrientation;
		}

		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);
		
		m_Window->SetCursorPosition(((float)windowWidth / 2), ((float)windowHeight / 2));
	}

}