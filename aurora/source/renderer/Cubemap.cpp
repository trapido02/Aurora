#include "pch.h"

#include <glad/glad.h>

#include "Cubemap.h"

#include <stb_image/stb_image.h>

namespace Aurora::Renderer {

	Cubemap::Cubemap(std::vector<std::string> texturePaths)
		: m_TexturePaths(texturePaths)
	{
	}

	Cubemap::~Cubemap()
	{
	}

	void Cubemap::Create()
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < m_TexturePaths.size(); i++)
		{
			unsigned char* data = stbi_load(m_TexturePaths[i].c_str(), &width, &height, &nrChannels, 3);
			if (data)
			{
				glTextureStorage2D(m_TextureID, 1, GL_RGB8, width, height);
				glTextureSubImage3D(m_TextureID, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				ERROR("Failed to load cubemap textures.");
				stbi_image_free(data);
			}
		}

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Cubemap::Destroy()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Cubemap::SetActiveTexture(unsigned int unit)
	{
		glBindTextureUnit(unit, m_TextureID);
	}

}