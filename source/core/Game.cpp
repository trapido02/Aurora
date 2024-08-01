#include "Game.h"

#include <iostream>

namespace Core {

	void Game::Create()
	{
		m_Window = new Window("Aurora", 720 * 16 / 9, 720);
		m_Window->SetVsync(true);
	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
	}

}