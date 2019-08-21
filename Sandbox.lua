project "Sandbox"
	location "Sandbox"

	targetname  "%{prj.name}"
	targetdir ("bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C++"
	cppdialect "C++11"

	kind "ConsoleApp"
	staticruntime "on"
	-------------------------------------------------------------------------
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
	-------------------------------------------------------------------------
	files
	{
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/source/**.h"
	}
	-------------------------------------------------------------------------
	includedirs
	{
		"%{AddIncludeDirs.spdlog}",
		"%{AddIncludeDirs.imgui}",
		"%{AddIncludeDirs.glad}",
		"%{AddIncludeDirs.glm}",
		"StepWay/source/",
		"StepWay/source/StepWay/"
	}
	-------------------------------------------------------------------------
	links
	{
		"StepWay"
	}
	-------------------------------------------------------------------------
	filter("configurations:Debug")
		runtime "Debug"
		symbols "On"
		optimize "Off"
		

	filter("configurations:Release")
		runtime "Release"
		symbols "Off"
		optimize "On"
		

	filter("configurations:Dist")
		runtime "Release"
		symbols "Off"
		optimize "On"
		

	filter {}
	-------------------------------------------------------------------------
	