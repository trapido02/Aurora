#pragma once

#include <GLFW/glfw3.h>

#include <functional>

namespace Aurora::Core {

	enum class KEYCODE
	{
		ESCAPE = GLFW_KEY_ESCAPE,
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F
	};

	struct WindowCallbacks
	{
		std::function<void()> closeCallback;
		std::function<void(int, int)> resizeCallback;
	};

	enum class WindowFlags : unsigned int
	{
		VSYNC_ENABLE = 1 << 0,
		DOCKING_ENABLE = 1 << 1,
		VIEWPORT_ENABLE = 1 << 2
	};

	inline WindowFlags operator|(WindowFlags a, WindowFlags b) {
		return static_cast<WindowFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
	}

	inline bool operator&(WindowFlags a, WindowFlags b) {
		return static_cast<unsigned int>(a) & static_cast<unsigned int>(b);
	}

	class Window
	{
	public:
		Window(const char* title, int width, int height, WindowFlags windowFlags = WindowFlags(0));
		~Window();

		void Create();
		void Destroy();

		void PreUpdate();
		void PostUpdate();

		void SetCloseCallback(std::function<void()> lambda);
		void SetResizeCallback(std::function<void(int width, int height)> lambda);

		bool GetKeyDown(KEYCODE keycode, bool once = false);
		void GetMousePosition(double& x, double& y);
		void GetSize(int& width, int& height);

		void SetCursorPosition(double x, double y);

		void LockMouseCursor();
		void UnlockMouseCursor();
		bool IsMouseLocked() { return m_MouseLocked; }
		float GetFPS() { return m_FPS; }
	private:
		GLFWwindow* m_Window = nullptr;

		WindowCallbacks m_Callbacks;
		WindowFlags m_WindowFlags;

		const char* m_Title;
		int m_Width, m_Height;

		bool m_MouseLocked = false;

		double m_PreviousTime = glfwGetTime();
		int m_FrameCount = 0;
		int m_FPS = 0;

		bool m_KeyState[GLFW_KEY_LAST + 1] = { false }; // To track the state of each key
	};

}
