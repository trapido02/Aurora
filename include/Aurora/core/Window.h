#pragma once

#include <string>
#include "Aurora/event/Event.h"

namespace Aurora::Core {

    class AURORA_API Window
    {
    public:
        Window() = delete;
        ~Window() = delete;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        static void SetTitle(const std::string& title);
        static void SetSize(int width, int height);
        static void SetVsync(bool enable);

        static Event::EventDispatcher& GetEventDispatcher();
    };

} // namespace Aurora::Core