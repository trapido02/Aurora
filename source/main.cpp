#include "core/Window.h"

#include <iostream>

int main()
{
    Core::Window* window = new Core::Window("Aurora", 720 * 16 / 9, 720);
    window->SetVsync(true);

    while (true)
    {
        glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window->OnUpdate();
    }

    return 0;
}