#pragma once

#include <GLFW/glfw3.h>

namespace Core {

	class Window
	{
	public:
		Window(const char* title, int width, int height);
		~Window();

		void OnUpdate();
		void SetVsync(bool state);
	private:
		GLFWwindow* m_Window;

		const char* m_Title;
		int m_Width, m_Height;
		bool m_Vsync;
	};

}
