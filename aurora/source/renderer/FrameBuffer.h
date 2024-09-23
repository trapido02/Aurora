#pragma once

#include "Shader.h"

namespace Aurora::Renderer {

	class FrameBuffer
	{
	public:
		FrameBuffer(int width = 0, int height = 0);
		~FrameBuffer();

		void Create();
		void Destroy();

		void Bind();
		void Unbind();

		void Resize(int width, int height);

		unsigned int GetColorAttachmentID();
		unsigned int GetID();
	private:
		unsigned int m_FrameBufferID = NULL;

		unsigned int m_ColorAttachment;
		unsigned int m_DepthAttachment;

		int m_Width;
		int m_Height;
	};

}