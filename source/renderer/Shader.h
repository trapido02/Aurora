#pragma once

#include <glad/glad.h>

namespace Renderer {

	class Shader
	{
	public:
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		~Shader();

		void Bind();
		void Unbind();
	private:
		unsigned int m_ShaderProgram;
	};

}