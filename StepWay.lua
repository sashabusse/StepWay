project "StepWay"
	location "StepWay"

	targetname  "%{prj.name}"
	targetdir ("bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C++"
	cppdialect "C++17"

	kind "StaticLib"
	staticruntime "on"
	
	pchheader "StepWayPCH.h"
	pchsource "StepWay/source/StepWay/StepWayPCH.cpp"

	postbuildcommands("{MKDIR} ../bin/" .. outputdirname .. "/Sandbox")
	postbuildcommands("{COPY} \"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdirname .. "/Sandbox/\"")
	
	-----------------------------------------------------------------------
	defines 
	{
	}
	filter("configurations:Debug")
	defines{"SW_DEBUG"}
	
	filter("configurations:Release")
	defines{"SW_RELEASE"}
	
	filter("configurations:Dist")
	defines {"SW_DIST"}
	
	filter {}
	------------------------------------------------------------------------
	files
	{
		"%{prj.name}/source/StepWay/**.cpp",	--main engine files
		"%{prj.name}/source/StepWay/**.h",		--main engine files
		"%{prj.name}/source/Platform/OpenGL/**.cpp",
		"%{prj.name}/source/Platform/OpenGL/**.h",
		
		"%{prj.name}/vendor/stb_image/**.cpp" --mb change layter stb_image files
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
		"%{AddIncludeDirs.implot}",
		"%{AddIncludeDirs.glad}",
		"%{AddIncludeDirs.glm}",
		"%{AddIncludeDirs.stb_image}",
		"%{AddIncludeDirs.entt}",
		"%{AddIncludeDirs.assimp}",
		"%{AddIncludeDirs.expression_evaluation"
		
	}
	-- Links---------------------------------------------------------------------------------------
	links
	{
		"glad",
		"imgui",
		"expression_evaluation"
	}
	filter("system:windows")
		links
		{
			"Opengl32.lib", --wglCreateContext e.t.c.
		}	
	filter{}
	------------------------------------------------------------------------------------------------
	filter("configurations:Debug")
		runtime "Debug"
		symbols "On"
		optimize "Off"
		targetsuffix "_d"
		

	filter("configurations:Release")
		runtime "Release"
		symbols "Off"
		optimize "On"
		targetsuffix "_r"
		

	filter("configurations:Dist")
		runtime "Release"
		symbols "Off"
		optimize "On"
		

	filter {} --end of configuration filters
	-------------------------------------------------------------------------------------------------

	filter("action:vs*")
		defines {"SW_MSVC"}
		
	filter {} --end of compiler filters

