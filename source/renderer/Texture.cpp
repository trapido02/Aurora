#include "pch.h"

#include <glad/glad.h>

#include "Texture.h"

#include <stb_image/stb_image.h>

namespace Renderer {

	Texture::Texture(std::string texturePath)
		: m_TexturePath(texturePath)
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::Create()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(m_TexturePath.c_str(), &width, &height, &nrChannels, 4);
		if (data)
		{
			glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);
			glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateTextureMipmap(m_TextureID);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	void Texture::Destroy()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::SetActiveTexture(unsigned int unit)
	{
		glBindTextureUnit(unit, m_TextureID);
	}

}