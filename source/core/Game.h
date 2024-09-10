#pragma once

#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Texture.h"
#include "renderer/Model.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"
#include "Window.h"
#include "Log.h"

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
		void Destroy();

		void Run();
		void ProcessInput();
	private:
		Game() = default;
		~Game() = default;

		Window* m_Window = nullptr;
		bool m_IsRunning = true;

		bool m_WireframeMode = false;

		Renderer::Renderer* m_Renderer = nullptr;
		Renderer::Shader* m_Shader = nullptr;
		Renderer::Camera* m_Camera = nullptr;
		Renderer::Model* m_Model = nullptr;

		Log* m_Logger = nullptr;
	};

}