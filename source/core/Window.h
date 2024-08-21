#pragma once

#include <GLFW/glfw3.h>

namespace Core {

	enum class KEYCODE
	{
		ESCAPE = GLFW_KEY_ESCAPE,
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
	};

	class Window
	{
	public:
		Window(const char* title, int width, int height);
		~Window();

		void OnUpdate();
		void SetVsync(bool state);

		bool GetKeyDown(KEYCODE keycode);
		void GetMousePosition(double& x, double& y);
		void GetSize(int& width, int& height);

		void SetCursorPosition(double x, double y);
	private:
		GLFWwindow* m_Window;

		const char* m_Title;
		bool m_Vsync;
	};

}
