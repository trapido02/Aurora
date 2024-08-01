#include "core/Game.h"

#include <iostream>

int main()
{
    Core::Game& game = Core::Game::getInstance();
    game.Create();
    game.Run();

    return 0;
}