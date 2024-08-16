#include "pch.h"

#include "Camera.h"

namespace Renderer {
	Camera::Camera(Core::Window* window, glm::vec3 position, float FOV, float nearPlane, float farPlane)
		: m_Window(window), m_Position(position), m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Update(float deltaTime, Shader& shader)
	{
		ProcessInput(deltaTime);
		ProcessMouse();
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
		projection = glm::perspective(glm::radians(m_FOV), (float)(m_Window->GetWidth() / m_Window->GetHeight()), m_NearPlane, m_FarPlane);

		shader.Bind();
		shader.SetUniformMatrix4fv("mvp", projection * view);
		shader.Unbind();
	}

	void Camera::ProcessInput(float deltaTime)
	{
		float velocity = m_Speed * deltaTime;

		if (m_Window->GetKeyDown(Core::KEYCODE::W))
		{
			m_Position += velocity * m_Orientation;
		}
		if (m_Window->GetKeyDown(Core::KEYCODE::S))
		{
			m_Position -= velocity * m_Orientation;
		}
		if (m_Window->GetKeyDown(Core::KEYCODE::D))
		{
			m_Position += velocity * glm::normalize(glm::cross(m_Orientation, m_Up));
		}
		if (m_Window->GetKeyDown(Core::KEYCODE::A))
		{
			m_Position -= velocity * glm::normalize(glm::cross(m_Orientation, m_Up));
		}
	}

	void Camera::ProcessMouse()
	{
		std::pair<double, double> position = m_Window->GetMousePosition();

		double mouseX = position.first;
		double mouseY = position.second;

		float rotX = m_Sensitivity * (float)(mouseY - (m_Window->GetHeight() / 2)) / m_Window->GetHeight();
		float rotY = m_Sensitivity * (float)(mouseX - (m_Window->GetWidth() / 2)) / m_Window->GetWidth();

		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Orientation = newOrientation;
		}

		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);
		
		m_Window->SetCursorPosition((m_Window->GetWidth() / 2), (m_Window->GetHeight() / 2));
	}

}