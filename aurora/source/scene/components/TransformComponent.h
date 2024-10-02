#pragma once

#include <glm.hpp>

namespace Aurora::Scene {

	struct TransformComponent
	{
		glm::vec3 position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 size{ 1.0f, 1.0f, 1.0f };
	};

}
