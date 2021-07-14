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
IncludeDir["glm"] = "SomaEngine/vendor/glm"

include "SomaEngine/vendor/Glad"
include "SomaEngine/vendor/imgui"

project "SomaEngine"
	location "SomaEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "somapch.hpp"
	pchsource "SomaEngine/src/somapch.cpp"

		defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp"
	}
	includedirs
	{
		"%{prj.name}/include",
		"Deps/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
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
				"SOMA_BUILD_DLL",
				"SOMA_PLATFORM_SDL"
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
		"SomaEngine/src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"SomaEngine/vendor"
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