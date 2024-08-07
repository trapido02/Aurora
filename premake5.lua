workspace "Aurora"
	architecture "x64"
	configurations { "Debug", "Release" }

project "Aurora"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "source/**.h", "source/**.cpp", "vendor/glad/src/glad.c", "vendor/stb_image/stb_image/stb_image.cpp" }

	includedirs
	{
		"source",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/stb_image",
		"vendor/glm"
	}

	libdirs
	{
		"vendor/glfw/lib-vc2022"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"