#pragma once

#include <glm.hpp>
#include "../Shader.h"

namespace Aurora::Renderer {

	class DirectionalLight
	{
	public:
		DirectionalLight(Shader& shader);
		~DirectionalLight();

		void SetDirection(glm::vec3 direction);
		void SetColor(glm::vec3 color);
		void SetStrength(float strength);
	private:
		Shader& m_Shader;
	};

}
