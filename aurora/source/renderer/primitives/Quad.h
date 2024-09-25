#pragma once

#include "renderer/SceneObject.h"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"

namespace Aurora::Renderer {

	class Quad : public SceneObject
	{
	public:
		Quad();
		~Quad();

		void Create();
		void Destroy();

		void Draw(Shader& shader, unsigned int frameBufferID = 0);
	private:
		VertexArray* m_VertexArray = nullptr;
		VertexBuffer* m_VertexBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
	};

}