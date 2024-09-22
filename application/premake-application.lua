project "application"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin/%{cfg.buildcfg}"
	cppdialect "C++20"
	staticruntime "off"

	files
	{
		"source/**.h",
		"source/**.cpp"
	}

	includedirs
	{
		"source",
		"../aurora/source",

		"../aurora/vendor/glfw/include",
		"../aurora/vendor/glad/include",
		"../aurora/vendor/stb_image",
		"../aurora/vendor/assimp/include",
		"../aurora/vendor/glm",
		"../aurora/vendor/spdlog/include",
		"../aurora/vendor/imgui"
	}

	links
	{
		"aurora"
	}

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../obj/" .. OutputDir .. "/%{prj.name}")

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		buildoptions "/MD"
		symbols "On"
		optimize "On"