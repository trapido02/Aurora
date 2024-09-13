#include "pch.h"

#include "Shader.h"

namespace Renderer {

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
		: m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::Create()
	{
		std::string vertexShaderSourceString;
		std::string fragmentShaderSourceString;

		std::ifstream vertexShaderStream;
		std::ifstream fragmentShaderStream;

		vertexShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		// Parse shaders
		try
		{
			{
				vertexShaderStream.open(m_VertexShaderPath);
				vertexShaderStream.exceptions(std::ifstream::badbit);
				std::string line;
				std::stringstream vertexShaderStringStream;
				while (std::getline(vertexShaderStream, line))
				{
					vertexShaderStringStream << line << "\n";
				}
				vertexShaderSourceString = vertexShaderStringStream.str();
			}
			{
				fragmentShaderStream.open(m_FragmentShaderPath);
				fragmentShaderStream.exceptions(std::ifstream::badbit);
				std::string line;
				std::stringstream fragmentShaderStringStream;
				while (std::getline(fragmentShaderStream, line))
				{
					fragmentShaderStringStream << line << "\n";
				}
				fragmentShaderSourceString = fragmentShaderStringStream.str();
			}
		}
		catch (std::ifstream::failure& e)
		{
			std::string error = "SHADER_LOADING_ERROR: " + std::string(e.what());
			ERROR(error);
		};

		const char* vertexShaderSource = vertexShaderSourceString.c_str();
		const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

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

			std::string error = "VERTEX_SHADER_COMPILATION_ERROR: " + (message ? std::string(message) : "");
			ERROR(error);
		}
		if (!fragmentSuccess)
		{
			int length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(fragmentShader, length, &length, message);

			std::string error = "FRAGMENT_SHADER_COMPILATION_ERROR: " + (message ? std::string(message) : "");
			ERROR(error);
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

	void Shader::Destroy()
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

	void Shader::SetUniform1f(GLchar* name, float v1)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniform1f(uniformLocation, v1);
	}

	void Shader::SetUniform3f(GLchar* name, float v1, float v2, float v3)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniform3f(uniformLocation, v1, v2, v3);
	}

	void Shader::SetUniform4f(GLchar* name, float v1, float v2, float v3, float v4)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniform4f(uniformLocation, v1, v2, v3, v4);
	}

	void Shader::SetUniform1i(GLchar* name, int v1)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniform1i(uniformLocation, v1);
	}

	void Shader::SetUniformMatrix4fv(GLchar* name, glm::mat4& value)
	{
		int uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
	}

}