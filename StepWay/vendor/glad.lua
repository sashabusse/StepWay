project "glad"
	
	location "glad"
	targetname  "%{prj.name}"
	targetdir ("../../bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("../../bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C"
	
	kind "StaticLib"
	staticruntime "Off"

	files
	{
		"glad/src/**.c",
		"glad/include/**.h"
	}

	includedirs
	{
		"glad/include/"		
	}
	
	links
	{
	}
	
	defines
	{
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