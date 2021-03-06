project "imgui"
	location "imgui"
	
	targetname  "%{prj.name}"
	targetdir ("../../bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("../../bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C++"
	cppdialect "C++17"
	
	
	kind "StaticLib"
	staticruntime "on"

	files
	{
		"imgui/*.cpp",
		"imgui/misc/cpp/*.cpp",
		"imgui/*.h",
		"implot/*.cpp",
		"implot/*.h"
	}

	includedirs
	{		
		"imgui/",
		"implot/"
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