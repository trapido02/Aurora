#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "Aurora/event/Event.h"

namespace Aurora::Core {

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

        Event::EventDispatcher& GetEventDispatcher() const;

    private:
        WindowImpl() : m_Dispatcher(std::make_unique<Event::EventDispatcher>()) {};
        ~WindowImpl() = default;

        void OnResize(int width, int height) const;
        static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

        // ---------------------------- //

        GLFWwindow* m_Window = nullptr;
        std::unique_ptr<Event::EventDispatcher> m_Dispatcher;

        const char* m_Title = "Aurora";
        int m_Width = 640;
        int m_Height = 480;
    };

} // namespace Aurora::Core