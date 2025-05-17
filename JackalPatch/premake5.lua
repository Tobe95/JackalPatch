workspace "JackalPatch"
	configurations
	{
		"Debug",
		"Release",
	}

	location "build"

project "JackalPatch"
	kind "SharedLib"
	language "C++"
	targetname "JackalPatch"
	targetdir "bin/%{cfg.buildcfg}"
	targetextension ".asi"

	files { "../patcher/patcher.cpp" }
	files { "../patcher/patcher.h" }
	includedirs { "../patcher" }

	files { "shared/ini_reader.h" }
	files { "shared/ini_reader.cpp" }
	files { "src/fc2.cpp" }

	characterset ("MBCS")
	toolset ("v141_xp")
	floatingpoint "Fast"
	buildoptions { "/Zc:sizedDealloc-" }
	links { "legacy_stdio_definitions" }
	linkoptions { "/SAFESEH:NO /IGNORE:4222" }
	defines { "WIN32_LEAN_AND_MEAN", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_DEPRECATE", "_USE_32BIT_TIME_T", "NOMINMAX", "DLL_NAME=\"$(ProjectName)\"" }

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "full"
		optimize "off"
		runtime "debug"
		editAndContinue "off"
		flags { "NoIncrementalLink" }
		staticruntime "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "on"
		optimize "speed"
		runtime "release"
		staticruntime "on"
		flags { "LinkTimeOptimization" }
		linkoptions { "/OPT:NOICF" }