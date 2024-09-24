#pragma once

#include "Cubemap.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Camera.h"

namespace Aurora::Renderer {

	class Skybox
	{
	public:
		Skybox(std::vector<std::string> texturePaths, Camera& camera);
		~Skybox();

		void Create();
		void Destroy();

		void Draw(Shader& shader);
	private:
		std::vector<std::string> m_TexturePaths;
		Camera& m_Camera;

		Cubemap* m_Cubemap = nullptr;
		VertexArray* m_VertexArray = nullptr;
		VertexBuffer* m_VertexBuffer = nullptr;
	};

}