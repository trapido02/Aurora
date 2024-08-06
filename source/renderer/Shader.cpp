#include "Shader.h"

#include <iostream>

namespace Renderer {

	Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		// Compile shaders
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		// Check for compilation errors
		int vertexSuccess;
		int fragmentSuccess;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
		if (!vertexSuccess)
		{
			int length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(vertexShader, length, &length, message);
			std::cerr << "VERTEX_SHADER_COMPILATION_ERROR:\n" << message << std::endl;
		}
		if (!fragmentSuccess)
		{
			int length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(fragmentShader, length, &length, message);
			std::cerr << "FRAGMENT_SHADER_COMPILATION_ERROR:\n" << message << std::endl;
		}

		// Link shaders
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);

		// Delete shaders after they are linked to the shader program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void Shader::Bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetUniform4f(GLchar* name, float v1, float v2, float v3, float v4)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniform4f(uniformLocation, v1, v2, v3, v4);
	}

}