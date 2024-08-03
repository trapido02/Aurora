#pragma once

#include "renderer/Renderer.h"
#include "Window.h"

namespace Core {
	
	class Game
	{
	public:
		// Get the singleton class instance
		static Game& getInstance()
		{
			static Game instance;
			return instance;
		};

		void Create();
		void Run();
		void Shutdown();
	private:
		Game() = default;
		~Game() = default;

		Window* m_Window = nullptr;
		bool m_IsRunning = true;
		Renderer::Renderer m_Renderer;
	};

}