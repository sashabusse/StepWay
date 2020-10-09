project "Sandbox"
	location "Sandbox"

	targetname  "%{prj.name}"
	targetdir ("bin/" .. outputdirname .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdirname .. "/%{prj.name}/")

	language "C++"
	cppdialect "C++17"

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
		"%{AddIncludeDirs.implot}",
		"%{AddIncludeDirs.glad}",
		"%{AddIncludeDirs.glm}",
		"%{AddIncludeDirs.stb_image}",
		"%{AddIncludeDirs.entt}",
		"%{AddIncludeDirs.expression_evaluation}",
		"StepWay/source/",
		"StepWay/source/StepWay/"
	}
	-------------------------------------------------------------------------
	links
	{
		"StepWay"
	}
	
	libdirs 
	{ 
		"StepWay/vendor/Assimp/" 
	}
	-------------------------------------------------------------------------
	filter("configurations:Debug")
		runtime "Debug"
		symbols "On"
		optimize "Off"
		links
		{
			"assimp-vc142-mtd.lib"
		}
		prebuildcommands("{MKDIR} ../bin/" .. outputdirname .. "/Sandbox")
		prebuildcommands("{COPY} \"../StepWay/vendor/Assimp/assimp-vc142-mtd.dll\" \"../bin/" .. outputdirname .. "/Sandbox/\"")
		

	filter("configurations:Release")
		runtime "Release"
		symbols "Off"
		optimize "On"
		links
		{
			"assimp-vc142-mt.lib"
		}
		prebuildcommands("{MKDIR} ../bin/" .. outputdirname .. "/Sandbox")
		prebuildcommands("{COPY} \"../StepWay/vendor/Assimp/assimp-vc142-mt.dll\" \"../bin/" .. outputdirname .. "/Sandbox/\"")
		

	filter("configurations:Dist")
		runtime "Release"
		symbols "Off"
		optimize "On"
		links
		{
			"assimp-vc142-mt.lib"
		}
		prebuildcommands("{MKDIR} ../bin/" .. outputdirname .. "/Sandbox")
		prebuildcommands("{COPY} \"../StepWay/vendor/Assimp/assimp-vc142-mt.dll\" \"../bin/" .. outputdirname .. "/Sandbox/\"")
		

	filter {}
	-------------------------------------------------------------------------
	