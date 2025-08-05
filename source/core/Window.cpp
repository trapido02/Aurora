#include "Aurora/core/Window.h"

#include "core/WindowImpl.h"

namespace Aurora::Core {

    void Window::SetTitle(const std::string& title)
    {
        WindowImpl::GetInstance().SetTitle(title);
    }

    void Window::SetSize(const int width, const int height)
    {
        WindowImpl::GetInstance().SetSize(width, height);
    }

    void Window::SetVsync(const bool enable)
    {
        WindowImpl::SetVsync(enable);
    }

    Event::EventDispatcher& Window::GetEventDispatcher()
    {
        return WindowImpl::GetInstance().GetEventDispatcher();
    }

} // namespace Aurora::Core