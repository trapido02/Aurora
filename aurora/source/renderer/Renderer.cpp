#include "pch.h"

#include <glad/glad.h>

#include "Renderer.h"

namespace Aurora::Renderer {

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

}