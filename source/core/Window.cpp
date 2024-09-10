#include "pch.h"

#include <glad/glad.h>
#include "Window.h"
#include "Game.h"

namespace Core {

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

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(m_Vsync);
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(m_Window, m_Width / 2, m_Height / 2);

        // Load glad, should maybe be removed since this window class should ONLY handle the window, and not glad really.
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            Game::getInstance().Destroy();
            });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            });
    }

    void Window::Destroy()
    {
        if (m_Window != nullptr)
            glfwTerminate();
    }

    void Window::OnUpdate()
    {
        // Update FPS
        double currentTime = glfwGetTime();
        m_FrameCount++;
        // If a second has passed.
        if (currentTime - m_PreviousTime >= 1.0)
        {
            std::stringstream ss;
            ss << m_Title << " [" << m_FrameCount << " FPS]";
            glfwSetWindowTitle(m_Window, ss.str().c_str());

            m_FrameCount = 0;
            m_PreviousTime = currentTime;
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void Window::SetVsync(bool state)
    {
        m_Vsync = state;
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

}