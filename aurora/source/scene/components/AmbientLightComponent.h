#pragma once

#include <glm.hpp>

namespace Aurora::Scene {

	struct AmbientLightComponent
	{
		glm::vec3 color{ 1.0f, 1.0f, 1.0f };
		float strength = 0.5f;
	};

}