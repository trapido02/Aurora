#include "Shader.h"

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

}