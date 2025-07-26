#pragma once

#include <GLFW/glfw3.h>
#include <string>

class WindowImpl
{
public:
    static WindowImpl& GetInstance()
    {
        static WindowImpl instance;
        return instance;
    }

    WindowImpl(const WindowImpl&) = delete;
    WindowImpl& operator=(const WindowImpl&) = delete;
    WindowImpl(WindowImpl&&) = delete;
    WindowImpl& operator=(WindowImpl&&) = delete;

    void Create();
    void Destroy();

    void Update() const;

    bool ShouldClose() const;

    void SetTitle(const std::string& title) const;
    void SetSize(int width, int height) const;
    static void SetVsync(bool enable);

private:
    WindowImpl() = default;
    ~WindowImpl() = default;

    // ---------------------------- //

    GLFWwindow* m_Window = nullptr;

    const char* m_Title = "Aurora";
    int m_Width = 640;
    int m_Height = 480;
};