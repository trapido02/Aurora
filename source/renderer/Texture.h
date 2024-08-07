#pragma once

#include <string>

namespace Renderer {

	class Texture
	{
	public:
		Texture(std::string texturePath);
		~Texture();

		void Bind(unsigned int unit = 0);
		void Unbind();
	private:
		unsigned int m_TextureID;
	};

}