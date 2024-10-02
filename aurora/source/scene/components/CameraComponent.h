#pragma once

#include "renderer/Skybox.h"

#include <glm.hpp>

namespace Aurora::Scene {

	struct CameraComponent
	{
		float fov = 60.0f;
		float nearPlane = 0.1f;
		float farPlane = 10000.0f;

		Renderer::Skybox* skybox = nullptr;
		Renderer::Shader* skyboxShader = nullptr;
	};

}
