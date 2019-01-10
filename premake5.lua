workspace "BunchPhysicEngine"
    configurations
	{ 
		"Debug",
		"Release"
	}
	platforms { "Windows" }

	filter "platforms:Windows"
	systemversion "10.0.17763.0"  --  Specify the version of the SDK

project "Bunch"
	location "Bunch"
    kind "StaticLib"
    language "C++"

    targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

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

