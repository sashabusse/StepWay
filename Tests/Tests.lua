

project "Tests"

	kind "ConsoleApp"
	
	targetname "%{prj.name}"
	
	targetdir ("../bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("../bin-int/" .. outputdirname .. "/%{prj.name}/")
	
	language "C++"
	cppdialect "C++11"
	
	staticruntime "Off"
	
	files
	{
		"**.cpp",
		"**.h",
		"../Dependencies/google_test/googletest/src/gtest-all.cc",
		"../StepWay/source/**.cpp"
	}
	
	includedirs
	{
		"../Dependencies/google_test/googletest/include/",
		"../Dependencies/google_test/googletest/",
		"../StepWay/source/",
		"../StepWay/source/StepWay/",
		"../" .. "%{AddIncludeDirs.spdlog}",
		"../" .. "%{AddIncludeDirs.imgui}",
		"../" .. "%{AddIncludeDirs.glad}" .. "include/"
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