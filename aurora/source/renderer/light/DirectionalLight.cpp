#include "pch.h"

#include "DirectionalLight.h"

namespace Aurora::Renderer {

	DirectionalLight::DirectionalLight(Shader& shader)
		: m_Shader(shader)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		m_Shader.Bind();
		m_Shader.SetUniform3f("directionalLightDirection", direction.x, direction.y, direction.z);
		m_Shader.Unbind();
	}

	void DirectionalLight::SetColor(glm::vec3 color)
	{
		m_Shader.Bind();
		m_Shader.SetUniform3f("directionalLightColor", color.x, color.y, color.z);
		m_Shader.Unbind();
	}

	void DirectionalLight::SetStrength(float strength)
	{
		m_Shader.Bind();
		m_Shader.SetUniform1f("directionalLightStrength", strength);
		m_Shader.Unbind();
	}

}