workspace "Botnet"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BotMaster"
	location "BotMaster"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	staticruntime "on"

	files
	{
		--"%{prj.location}/src/*.h",
		--"%{prj.location}/src/*.cpp",
		"%{prj.location}/src/BotMaster/GUI/vendor/glm/**.hpp",
		"%{prj.location}/src/BotMaster/GUI/vendor/stb_image/**.h",
		"%{prj.location}/src/BotMaster/GUI/vendor/stb_image/**.cpp",
		"%{prj.location}/src/BotMaster/GUI/src/**.cpp",
		"%{prj.location}/src/BotMaster/GUI/src/**.h"
	}
	

	includedirs
	{
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/GLEW/include",
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/GLFW/include",
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/glm",
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/stb_image",
		"%{wks.location}/BotMaster/src/BotMaster/GUI"
	}

	libdirs
	{
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/GLFW/lib-vc2019",
		"%{wks.location}/BotMaster/src/BotMaster/GUI/vendor/GLEW/lib/Release/Win32"
	}

	defines
	{
		"GLEW_STATIC"
	}

	links
	{
		"glew32s.lib",
		"glfw3.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
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
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
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
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"