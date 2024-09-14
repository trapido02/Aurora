#pragma once

#include <glad/glad.h>

namespace Renderer {

	class Renderer
	{
	public:
		void Clear();
		void ClearColor(float r, float g, float b, float a);
	};

}