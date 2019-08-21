project "glad"
	location "glad"
	
	targetname  "%{prj.name}"
	targetdir ("../../bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("../../bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C"
	
	kind "StaticLib"
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
		"glad/src/**.c",
		"glad/include/**.h"
	}
	-------------------------------------------------------------------------
	includedirs
	{
		"glad/include/"		
	}
	-------------------------------------------------------------------------
	links
	{
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