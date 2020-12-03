outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" --Output directory path for the projects

workspace "Xenos"		--Settings applied to the whole solution
	architecture "x64"	--Arhitecture for the platforms that we will be supporting
	startproject "XenosEditor"
	configurations		--Configurations we will be supporting
	{
		"Debug",		--For debugging purposes, with all the debugging features on and optimizations off
		"Release",		--For testing and profiling purposes, with debuggin stripped down and optimizations on
		"Distribution"	--For actual distribution, with debugging off and optimizations on
	}

IncludeDir = {} 
IncludeDir["glfw"] = "XenosEngine/vendor/glfw/include"
IncludeDir["glad"] = "XenosEngine/vendor/glad/include"
IncludeDir["imgui"] = "XenosEngine/vendor/imgui"
IncludeDir["glm"] = "XenosEngine/vendor/glm"
IncludeDir["stb_image"] = "XenosEngine/vendor/stb_image"
IncludeDir["entt"] = "XenosEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "XenosEngine/vendor/yaml-cpp/include"
IncludeDir["magic_enum"] = "XenosEngine/vendor/magic_enum"
IncludeDir["ImGuizmo"] = "XenosEngine/vendor/ImGuizmo"

include "XenosEngine/vendor/glfw"
include "XenosEngine/vendor/glad"
include "XenosEngine/vendor/imgui"
include "XenosEngine/vendor/yaml-cpp"

project "XenosEngine"	--Settings applied to the project only


	location "XenosEngine"
	kind "StaticLib"	--Specify that this produces a dynamic library
	language "C++"
	cppdialect "C++17"		
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	--Directory for output files
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	--Directory for Visual Studio intermediate files

	pchheader "xenospch.h"
	pchsource "XenosEngine/src/xenospch.cpp"

	files
	{
		"%{prj.name}/src/**.h",		--copy all the header files
		"%{prj.name}/src/**.cpp",	--copy all the object files
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	includedirs				--Include paths for the generated project
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",		--Include path for the spdlog library
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.magic_enum}",
		"%{IncludeDir.ImGuizmo}"
	}

	links 
	{ 
		"glfw",
		"glad",
		"opengl32.lib",
		"imgui",
		"yaml-cpp"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags {"NoPCH"}

	filter "system:windows"			--Settings applied to windows only
		systemversion "latest"		--Sets the system version to the latest installed
		
		defines
		{
			"XENOS_PLATFORM_WINDOWS",
			"XENOS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "XENOS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "XENOS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "XENOS_DISTRIBUTION"
		runtime "Release"
		optimize "On"

	--filter {"system:windows", "configurations:Release}
	--	buildoptions "/MT"

project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs				--Include paths for the generated project
	{
		"XenosEngine/vendor/spdlog/include",
		"XenosEngine/src",
		"XenosEngine",
		"%{IncludeDir.glm}",
		"XenosEngine/vendor"
	}

	links
	{
		"XenosEngine"
	}

	filter "system:windows"		--Settings applied to windows only
		systemversion "latest"

		defines
		{
			"XENOS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "XENOS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "XENOS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "XENOS_DISTRIBUTION"
		optimize "On"
		runtime "Release"

project "XenosEditor"

	location "XenosEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs				--Include paths for the generated project
	{
		"XenosEngine/vendor/spdlog/include",
		"XenosEngine/src",
		"XenosEngine",		
		"XenosEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"

	}

	links
	{
		"XenosEngine"
	}

	filter "system:windows"		--Settings applied to windows only
		systemversion "latest"

		defines
		{
			"XENOS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "XENOS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "XENOS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "XENOS_DISTRIBUTION"
		optimize "On"
		runtime "Release"
