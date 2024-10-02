#pragma once

#include <glm.hpp>

namespace Aurora::Scene {

	struct DirectionalLightComponent
	{
		glm::vec3 direction{ -0.5f, -1.0f, -0.5f };
		glm::vec3 color{ 1.0f, 1.0f, 1.0f };
		float strength = 1.0f;
	};

}