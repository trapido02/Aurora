#pragma once

#include <glm.hpp>
#include "../Shader.h"

namespace Aurora::Renderer {

	class AmbientLight
	{
	public:
		AmbientLight(Shader& shader);
		~AmbientLight();

		void SetColor(glm::vec3 color);
		void SetStrength(float strength);
	private:
		Shader& m_Shader;
	};

}
