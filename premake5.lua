workspace "Aurora"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "editor"

	filter "system:windows"
    	buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "aurora/premake-aurora.lua"
include "editor/premake-editor.lua"