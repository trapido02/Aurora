#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Aurora::Renderer {

	class Cubemap
	{
	public:
		Cubemap(std::vector<std::string> texturePaths);
		~Cubemap();

		void Create();
		void Destroy();

		void SetActiveTexture(unsigned int unit);
	private:
		unsigned int m_TextureID = NULL;
		std::vector<std::string> m_TexturePaths;

		Aurora::Renderer::VertexArray* m_VertexArray = nullptr;
		Aurora::Renderer::VertexBuffer* m_VertexBuffer = nullptr;
	};

}