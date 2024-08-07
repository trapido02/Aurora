#pragma once

#include <glad/glad.h>

#include <string>

namespace Renderer {

	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void Bind();
		void Unbind();

		void SetUniform4f(GLchar* name, float v1, float v2, float v3, float v4);
	private:
		unsigned int m_ShaderProgram;
	};

}