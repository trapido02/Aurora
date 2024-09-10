#include "pch.h"

#include "core/Game.h"

int main()
{
	Core::Game& game = Core::Game::getInstance();
	game.Create();
	game.Run();

	return 0;
}