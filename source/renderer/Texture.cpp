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
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(1);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(m_TexturePath.c_str(), &width, &height, &nrChannels, 4);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
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

	void Texture::Bind(unsigned int unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}