#include "WindowImpl.h"

void WindowImpl::Create()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    glfwMakeContextCurrent(m_Window);
}

void WindowImpl::Destroy()
{
    if (m_Window != nullptr)
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }
    glfwTerminate();
}

void WindowImpl::Update() const
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool WindowImpl::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window) != 0;
}

void WindowImpl::SetTitle(const std::string& title) const
{
    glfwSetWindowTitle(m_Window, title.c_str());
}

void WindowImpl::SetSize(const int width, const int height) const
{
    glfwSetWindowSize(m_Window, width, height);
}

void WindowImpl::SetVsync(const bool enable){
    glfwSwapInterval(enable ? 1 : 0);
}