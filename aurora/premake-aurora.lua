project "aurora"
	kind "StaticLib"
	language "C++"
	targetdir "../bin/%{cfg.buildcfg}"
	cppdialect "C++20"
	staticruntime "off"

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
		"vendor/glfw/lib-vc2022"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib"
	}

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../obj/" .. OutputDir .. "/%{prj.name}")

	filter "files:vendor/**.c"
    	flags { "NoPCH" }

	filter "files:vendor/**.cpp"
    	flags { "NoPCH" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"

		libdirs
		{
			"vendor/assimp/lib/debug"
		}

		links
		{
			"assimp-vc143-mtd.lib",
			"zlibstaticd.lib"
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		buildoptions "/MD"
		symbols "On"
		optimize "On"

		libdirs
		{
			"vendor/assimp/lib/release"
		}

		links
		{
			"assimp-vc143-mt.lib",
			"zlibstatic.lib"
		}