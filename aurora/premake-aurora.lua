project "aurora"
	kind "StaticLib"
	language "C++"
	targetdir "../bin/%{cfg.buildcfg}"
	cppdialect "C++20"

	pchheader "pch.h"
	pchsource "source/pch.cpp"

	files
	{
		"source/**.h",
		"source/**.cpp",
		"vendor/glad/src/glad.c",
		"vendor/stb_image/stb_image/stb_image.cpp",
		"vendor/imgui/**.cpp"
	}

	includedirs
	{
		"source",
		
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/stb_image",
		"vendor/assimp/include",
		"vendor/glm",
		"vendor/spdlog/include",
		"vendor/imgui"
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

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../obj/" .. OutputDir .. "/%{prj.name}")

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