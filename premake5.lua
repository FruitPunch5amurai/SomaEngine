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
IncludeDir["GLFW"] = "SomaEngine/vendor/GLFW/include"
IncludeDir["imgui"] = "SomaEngine/vendor/imgui"
IncludeDir["glm"] = "SomaEngine/vendor/glm"
IncludeDir["stb_image"] = "SomaEngine/vendor/stb_image"

include "SomaEngine/vendor/Glad"
include "SomaEngine/vendor/imgui"
include "SomaEngine/vendor/GLFW"

project "SomaEngine"
	location "SomaEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/include",
		"Deps/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.GLFW}"
	}
	libdirs { "Deps/lib/x64" }

	links {"opengl32.lib","assimp-vc141-mtd.lib","Glad","imgui","GLFW"}

	filter "system:windows"
		systemversion "latest"
		defines
		{
				"SOMA_ENABLE_ASSERTS",
				"SOMA_PLATFORM_WINDOWS",
				"SOMA_PLATFORM_GLFW",
				"SOMA_RENDER_OPENGL"
		}

	filter "configurations:Debug"
		defines "SOMA_DEBUG"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "SOMA_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		symbols "on"

	filter "configurations:Dist"
		defines "SOMA_DIST"
		buildoptions "/MD"
		runtime "Release"
		symbols "on"
		
project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	cppdialect "C++17"
	staticruntime "on"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
				"SOMA_ENABLE_ASSERTS",
				"SOMA_PLATFORM_WINDOWS",
				"SOMA_PLATFORM_GLFW"
		}

	filter "configurations:Debug"
		defines "SOMA_DEBUG"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SOMA_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "SOMA_DIST"
		runtime "Release"
		buildoptions "/MD"
		symbols "On"
		
