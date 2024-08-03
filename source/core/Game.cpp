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
			m_Renderer.Clear();
			m_Renderer.ClearColor(0.1f, 0.3f, 0.2f, 1.0f);

			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		m_IsRunning = false;
		delete m_Window;
	}

}