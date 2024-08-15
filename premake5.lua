workspace "Aurora"
	architecture "x64"
	configurations { "Debug", "Release" }

	filter "system:windows"
    	buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

project "Aurora"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	pchheader "pch.h"
	pchsource "source/pch.cpp"

	files { "source/**.h", "source/**.cpp", "vendor/glad/src/glad.c", "vendor/stb_image/stb_image/stb_image.cpp" }

	includedirs
	{
		"source",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/stb_image",
		"vendor/assimp/include",
		"vendor/glm"
	}

	libdirs
	{
		"vendor/glfw/lib-vc2022",
		"vendor/assimp/lib"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib",
		"assimp-vc143-mtd.lib",
		"zlibstaticd.lib"
	}

	filter "files:vendor/**.c"
    	flags { "NoPCH" }

	filter "files:vendor/**.cpp"
    	flags { "NoPCH" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		buildoptions "/MD"