#pragma once

#include <GLFW/glfw3.h>

namespace Core {

	enum class KEYCODE
	{
		ESCAPE = GLFW_KEY_ESCAPE,
	};

	class Window
	{
	public:
		Window(const char* title, int width, int height);
		~Window();

		void OnUpdate();
		void SetVsync(bool state);

		bool GetKeyDown(KEYCODE keycode);
	private:
		GLFWwindow* m_Window;

		const char* m_Title;
		int m_Width, m_Height;
		bool m_Vsync;
	};

}
