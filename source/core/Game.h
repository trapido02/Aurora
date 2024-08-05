#pragma once

#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "Window.h"

#include <memory>

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

		Renderer::Renderer* m_Renderer = nullptr;
		Renderer::Shader* m_Shader = nullptr;
		Renderer::VertexArray* m_VertexArray = nullptr;
		Renderer::VertexBuffer* m_VertexBuffer = nullptr;
	};

}