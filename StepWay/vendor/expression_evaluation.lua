project "expression_evaluation"
	location "expression_evaluation"
	
	targetname  "%{prj.name}"
	targetdir ("../../bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("../../bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C++"
	cppdialect "C++17"
	
	
	kind "StaticLib"
	staticruntime "on"

	files
	{
		"expression_evaluation/*.cpp",
		"expression_evaluation/*.hpp",
		"expression_evaluation/*.h"
	}

	includedirs
	{		
		"expression_evaluation/"
	}
	
	links
	{
	}
	
	defines
	{
	}
	
	buildoptions 
	{
	"/bigobj" 
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