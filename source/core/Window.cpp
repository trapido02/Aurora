#include <glad/glad.h>
#include "Window.h"

namespace Core {

    Window::Window(const char* title, int width, int height)
        : m_Window(nullptr),
          m_Title(title),
          m_Width(width),
          m_Height(height),
          m_Vsync(false)
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(m_Vsync);

        // Load glad
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    Window::~Window()
    {
        if (m_Window != nullptr)
            glfwTerminate();
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void Window::SetVsync(bool state)
    {
        m_Vsync = state;
    }

}