#pragma once

#include <string>

namespace Aurora::Renderer {

	class Texture
	{
	public:
		Texture(std::string texturePath);
		~Texture();

		void Create();
		void Destroy();

		void SetActiveTexture(unsigned int unit = 0);
	private:
		unsigned int m_TextureID = NULL;
		std::string m_TexturePath;
	};

}