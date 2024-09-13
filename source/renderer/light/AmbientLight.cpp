#include "pch.h"

#include "AmbientLight.h"

namespace Renderer {

	AmbientLight::AmbientLight(Shader& shader)
		: m_Shader(shader)
	{
	}

	AmbientLight::~AmbientLight()
	{
	}

	void AmbientLight::SetColor(glm::vec3 color)
	{
		m_Shader.Bind();
		m_Shader.SetUniform3f("ambientLightColor", color.x, color.y, color.z);
		m_Shader.Unbind();
	}

	void AmbientLight::SetStrength(float strength)
	{
		m_Shader.Bind();
		m_Shader.SetUniform1f("ambientLightStrength", strength);
		m_Shader.Unbind();
	}

}