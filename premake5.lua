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

	targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
	objdir "bin-int/%{prj.name}/%{cfg.buildcfg}"

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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"

	targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
	objdir "bin-int/%{ prj.name}/%{cfg.buildcfg}"

	libdirs { "%{prj.name}/World3D/lib" }  -- where to find the World3D library
	links { "World3D", "Bunch" }  -- the World3D and the Bunch library

	files 
	{
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/World3D/include",
		"Bunch/include/"
	}