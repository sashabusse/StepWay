
--workspace/solution discription file
workspace "StepWay"
	
	startproject "Sandbox"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	platforms
	{
		"x86",
		"x64"
	}
	
	systemversion "latest"

	filter("platforms:x86")
		architecture "x86"
	filter("platforms:x64")
		architecture "x64"

	filter {}

	--TODO:
	--ADD comand line arg to choose--------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!--------------------------------
	filter("system:windows")
		defines "SW_PLATFORM_WINDOWS"
	
	filter {}
	
	
	--variables for common use--
	outputdirname = "%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}"
	
	AddIncludeDirs = {}
	AddIncludeDirs["spdlog"] =  "StepWay/vendor/spdlog/include/"
	AddIncludeDirs["imgui"] = "StepWay/vendor/imgui/"
	AddIncludeDirs["glad"] = "StepWay/vendor/glad/include/"
	AddIncludeDirs["glm"] = "StepWay/vendor/glm/"
	AddIncludeDirs["stb_image"] = "StepWay/vendor/stb_image/"
	AddIncludeDirs["entt"] = "StepWay/vendor/entt/"
	AddIncludeDirs["assimp"] = "StepWay/vendor/Assimp/include"
	AddIncludeDirs["expression_evaluation"] = "StepWay/vendor/expression_evaluation/"
	
	include "StepWay.lua"
	include "Sandbox.lua"
	--include "Tests/Tests.lua"
	include "StepWay/vendor/glad.lua"
	include "StepWay/vendor/imgui.lua"
	include "StepWay/vendor/expression_evaluation.lua"
	
	--Projects are defined in such order
	--[[
	
	1. location
	
	2. targetname
	3. targetdir
	4. objdir
	
	5. language and dialect
	
	6. kind (static/shared lib e.t.c.)
	7. staticruntime("off") cause all should use common dll runtime
	
	--0.1. precompiled header
	--0.2. postbuild commands
	
	8. defines with their filters if needed
	
	9. files with their filters if needed
	10. include directories with their filters if needed
	
	11. links with their filters if needed
	
	12. configuration filters runtime,symbols,optimizations
	
	--0.3. configuration some other filters e.g. compiler or smth other not specified before
	
	]]--
	
	
	