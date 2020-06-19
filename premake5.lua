workspace "Botnet"
	architecture "x64"

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
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.cpp",
	}
	

	includedirs
	{
	}

	libdirs
	{
	}

	links
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


project "Zombie"
	location "Zombie"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	staticruntime "on"

	files
	{
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.cpp"
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
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.cpp"
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