#include "pch.h"

#include <glad/glad.h>

#include "FrameBuffer.h"

namespace Aurora::Renderer {

	FrameBuffer::FrameBuffer(int width, int height)
		: m_Width(width), m_Height(height)
	{
	}

	FrameBuffer::~FrameBuffer()
	{
	}

	void FrameBuffer::Create()
	{
		if (m_FrameBufferID)
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{
			INFO("FRAMEBUFFER GOOD");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Destroy()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	}

	void FrameBuffer::Resize(int width, int height)
	{
		m_Width = width;
		m_Height = height;

		FrameBuffer::Create();
	}

	int FrameBuffer::GetWidth() const
	{
		return m_Width;
	}
	int FrameBuffer::GetHeight() const
	{
		return m_Height;
	}

	unsigned int FrameBuffer::GetColorAttachmentID()
	{
		return m_ColorAttachment;
	}

	unsigned int FrameBuffer::GetID()
	{
		return m_FrameBufferID;
	}

}