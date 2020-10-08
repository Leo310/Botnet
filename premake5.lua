workspace "Botnet"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}

	startproject "BotMaster"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "BM Dependencies"
include "BotMaster/vendor/glad"
include "BotMaster/vendor/imgui"
include "BotMaster/vendor/glfw"

group ""

project "BotMaster"
	location "BotMaster"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	staticruntime "on"

	pchsource "%{prj.location}/src/BMpch.cpp"
	pchheader "BMpch.h"

	links
	{
		"Glad",
		"GLFW",
		"ImGUI",
		"opengl32",
		"ws2_32"
	}

	files
	{
		--"%{prj.location}/src/*.h",
		--"%{prj.location}/src/*.cpp",
		"%{prj.location}/vendor/glm/**.hpp",
		"%{prj.location}/vendor/stb_image/**.h",
		"%{prj.location}/vendor/stb_image/**.cpp",
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"**.shader"
	}
	

	includedirs
	{
		"%{wks.location}/BotMaster/vendor/glfw/include",
		"%{wks.location}/BotMaster/vendor/glm",
		"%{wks.location}/BotMaster/vendor/spdlog/include",
		"%{wks.location}/BotMaster/vendor/stb_image",
		"%{wks.location}/BotMaster/vendor/imgui",
		"%{wks.location}/BotMaster/src/BotMaster/GUI",
		"%{wks.location}/BotMaster/vendor/glad/include",
		"%{prj.location}/src"
	}

	libdirs
	{
		"%{wks.location}/BotMaster/vendor/glfw/bin/".. outputdir,
		"%{wks.location}/BotMaster/vendor/imgui/bin/".. outputdir,
		"%{wks.location}/BotMaster/vendor/glad/bin/".. outputdir
	}

	defines
	{
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


	filter "configurations:Debug"
		defines "BM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BM_RELEASE"
		optimize "On"


project "Zombie"
	location "Zombie"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	staticruntime "on"

	files
	{
		"%{prj.location}/src/*.h",
		"%{prj.location}/src/*.cpp"
	}

	includedirs
	{
	}

	libdirs
	{
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


	filter "configurations:Debug"
		defines "Z_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "Z_RELEASE"
		optimize "On"
 
 project "CandC"
	location "CandC"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	staticruntime "on"

	files
	{
		"%{prj.location}/src/*.h",
		"%{prj.location}/src/*.cpp"
	}

	includedirs
	{
	}

	libdirs
	{
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


	filter "configurations:Debug"
		defines "CC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CC_RELEASE"
		optimize "On"