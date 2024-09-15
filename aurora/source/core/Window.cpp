#include "pch.h"

#include <glad/glad.h>
#include "Window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Aurora::Core {

	Window::Window(const char* title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
	}

	Window::~Window()
	{
	}

	void Window::Create()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(m_Vsync);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(m_Window, m_Width / 2, m_Height / 2);

		// Load glad, should maybe be removed since this window class should ONLY handle the window, and not glad really.
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		// Load ImGui
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 450");
		ImGui::StyleColorsDark();
	}

	void Window::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		if (m_Window != nullptr)
			glfwTerminate();
	}

	void Window::PreUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Window::PostUpdate()
	{
		// Update FPS
		double currentTime = glfwGetTime();
		m_FrameCount++;
		// If a second has passed.
		if (currentTime - m_PreviousTime >= 1.0)
		{
			m_FPS = m_FrameCount;

			std::stringstream ss;
			ss << m_Title << " [" << m_FrameCount << " FPS]";
			glfwSetWindowTitle(m_Window, ss.str().c_str());

			m_FrameCount = 0;
			m_PreviousTime = currentTime;
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::SetVsync(bool state)
	{
		m_Vsync = state;
	}

	void Window::SetCloseCallback(std::function<void()> callback)
	{
		glfwSetWindowUserPointer(m_Window, new std::function<void()>(callback));

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			auto func = static_cast<std::function<void()>*>(glfwGetWindowUserPointer(window));
			(*func)();
		});
	}

	bool Window::GetKeyDown(KEYCODE keycode, bool once)
	{
		int key = glfwGetKey(m_Window, (int)keycode);
		if (once)
		{
			bool isPressed = (key == GLFW_PRESS);

			if (isPressed && !m_KeyState[(int)keycode])
			{
				m_KeyState[(int)keycode] = true;
				return true;
			}
			else if (!isPressed)
			{
				m_KeyState[(int)keycode] = false;
			}

			return false;
		}
		else
		{
			return key == GLFW_PRESS;
		}
	}

	void Window::GetMousePosition(double& x, double& y)
	{
		glfwGetCursorPos(m_Window, &x, &y);
	}

	void Window::GetSize(int& width, int& height)
	{
		glfwGetWindowSize(m_Window, &width, &height);
	}

	void Window::SetCursorPosition(double x, double y)
	{
		glfwSetCursorPos(m_Window, x, y);
	}

	void Window::LockMouseCursor()
	{
		m_MouseLocked = true;
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Prevent the camera from snapping when you lock your cursor
		int windowWidth, windowHeight;
		Window::GetSize(windowWidth, windowHeight);
		Window::SetCursorPosition(((float)windowWidth / 2), ((float)windowHeight / 2));
	}

	void Window::UnlockMouseCursor()
	{
		m_MouseLocked = false;
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}