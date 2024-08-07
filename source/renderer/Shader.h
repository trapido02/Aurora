#pragma once

#include <glad/glad.h>

#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Renderer {

	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void Bind();
		void Unbind();

		void SetUniform4f(GLchar* name, float v1, float v2, float v3, float v4);
		void SetUniform1i(GLchar* name, int v1);
		void SetUniformMatrix4fv(GLchar* name, glm::mat4& value);
	private:
		unsigned int m_ShaderProgram;
	};

}