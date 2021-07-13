workspace "SomaEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relativeto root folder
IncludeDir = {}
IncludeDir["Glad"] = "SomaEngine/vendor/Glad/include"
IncludeDir["imgui"] = "SomaEngine/vendor/imgui"

include "SomaEngine/vendor/Glad"
include "SomaEngine/vendor/imgui"

project "SomaEngine"
	location "SomaEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "somapch.hpp"
	pchsource "SomaEngine/src/somapch.cpp"

	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/include",
		"Deps/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}
	libdirs { "Deps/lib/x64" }

	links {"opengl32.lib","assimp-vc141-mtd.lib","SDL2.lib","Glad","imgui"}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
				"SOMA_ENABLE_ASSERTS",
				"SOMA_PLATFORM_WINDOWS",
				"SOMA_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SOMA_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SOMA_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "SOMA_DIST"
		buildoptions "/MD"
		symbols "On"
		
project "SandBox"
	location "SandBox"
	kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/include",
		"Deps/include",
		"SomaEngine/include",
		"%{IncludeDir.Glad}"
	}
	
	libdirs { "Deps/lib/x64" }

	links
	{
		"SomaEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
				"SOMA_ENABLE_ASSERTS",
				"SOMA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SOMA_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SOMA_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "SOMA_DIST"
		buildoptions "/MD"
		symbols "On"