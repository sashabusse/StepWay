


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
	
	
	outputdirname = "%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}"
	
	AddIncludeDirs = {}
	AddIncludeDirs["spdlog"] =  "StepWay/vendor/spdlog/include/"
	AddIncludeDirs["imgui"] = "StepWay/vendor/imgui/"
	AddIncludeDirs["glad"] = "StepWay/vendor/glad/include/"
	AddIncludeDirs["glm"] = "StepWay/vendor/glm/"
	
	
	include "Tests/Tests.lua"
	include "StepWay/vendor/glad/glad.lua"
	include "StepWay/vendor/imgui/imgui.lua"
	--TODO:
	--add imgui later---------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-------------------------------------
	
	project "StepWay"
		
		location "StepWay"

		targetname  "%{prj.name}"
		targetdir ("bin/" .. outputdirname .. "/%{prj.name}/")
		objdir ("bin-int/" .. outputdirname .. "/%{prj.name}/")

		language "C++"
		cppdialect "C++11"

		kind "SharedLib"
		staticruntime "Off"
		
		pchheader "StepWayPCH.h"
		pchsource "StepWay/source/StepWay/StepWayPCH.cpp"

		postbuildcommands("{MKDIR} ../bin/" .. outputdirname .. "/Sandbox")
		postbuildcommands("{COPY} \"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdirname .. "/Sandbox/\"")
		
		------------------------------------------------------------------------
		files
		{
			"%{prj.name}/source/StepWay/**.cpp",	--main engine files
			"%{prj.name}/source/StepWay/**.h",		--main engine files
			"%{prj.name}/source/Platform/OpenGL/**.cpp",
			"%{prj.name}/source/Platform/OpenGL/**.h"
		}
		filter("system:windows")
			files
			{
				"%{prj.name}/source/Platform/Win32/**.cpp",
				"%{prj.name}/source/Platform/Win32/**.h",
				"%{prj.name}/source/Platform/Direct3D11/**.cpp",
				"%{prj.name}/source/Platform/Direct3D11/**.h"
			}
		
		filter{}
		------------------------------------------------------------------------

		includedirs
		{
			"StepWay/source/StepWay/",
			"StepWay/source/Platform",
			"%{AddIncludeDirs.spdlog}",
			"%{AddIncludeDirs.imgui}",
			"%{AddIncludeDirs.glad}",
			"%{AddIncludeDirs.glm}"
		}
		-- Links---------------------------------------------------------------------------------------
		links
		{
			"glad",
			"imgui"
		}
		filter("system:windows")
			links
			{
				"Opengl32.lib" --wglCreateContext e.t.c.
			}
			
		filter{}
		------------------------------------------------------------------------------------------------

		defines 
		{
			"SW_BUILD_DLL"
		}


		filter("configurations:Debug")
			runtime "Debug"
			symbols "On"
			optimize "Off"
			targetsuffix "_d"
			defines
			{
				"SW_DEBUG"
			}

		filter("configurations:Release")
			runtime "Release"
			symbols "Off"
			optimize "On"
			targetsuffix "_r"
			defines
			{
				"SW_RELEASE"
			}

		filter("configurations:Dist")
			runtime "Release"
			symbols "Off"
			optimize "On"
			defines 
			{
				"SW_DIST"
			}

		filter {} --end of configuration filters


		filter("action:vs*")
			defines {"SW_MSVC"}
			
		filter {} --end of compiler filters





	project "Sandbox"
		location "Sandbox"

		targetname  "%{prj.name}"
		targetdir ("bin/" .. outputdirname .. "/%{prj.name}/")
		objdir ("bin-int/" .. outputdirname .. "/%{prj.name}/")

		language "C++"
		cppdialect "C++11"

		kind "ConsoleApp"
		staticruntime "Off"

		files
		{
			"%{prj.name}/source/**.cpp",
			"%{prj.name}/source/**.h"
		}

		includedirs
		{
			"%{AddIncludeDirs.spdlog}",
			"%{AddIncludeDirs.imgui}",
			"%{AddIncludeDirs.glad}",
			"%{AddIncludeDirs.glm}",
			"StepWay/source/",
			"StepWay/source/StepWay/"
		}
		
		links
		{
			"StepWay"
		}
		
		defines
		{
			"SW_USE_DLL"
		}

		filter("configurations:Debug")
			runtime "Debug"
			symbols "On"
			optimize "Off"
			defines
			{
				"SW_DEBUG"
			}

		filter("configurations:Release")
			runtime "Release"
			symbols "Off"
			optimize "On"
			defines
			{
				"SW_RELEASE"
			}

		filter("configurations:Dist")
			runtime "Release"
			symbols "Off"
			optimize "On"
			defines 
			{
				"SW_DIST"
			}

		filter {}