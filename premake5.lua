workspace "BunchPhysicEngine"
    configurations
	{ 
		"Debug",
		"Release"
	}

project "Bunch"
	location "Bunch"
    kind "ConsoleApp" -- Change this to Static Library
    language "C++"

    targetdir "bin/%{cfg.buildcfg}"

	files 
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "on"