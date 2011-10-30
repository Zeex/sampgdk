-- SA:MP Gamemode Development Kit for C++
-- Premake 4 script

solution "sampgdk"
	language "C++"

	configurations {
		"Debug",  
		"Release"  
	}

	platforms "x32"

	includedirs {
		"include",         -- public headers 
		"include/sampgdk"  -- some files include "amx.h" directly
	}

	flags {
		"No64BitChecks",
		"NoPCH"
	}

	configuration "Debug"
		flags {
			"ExtraWarnings",
			"Symbols"
		}
		objdir    "obj/Debug"
		targetdir "bin/Debug"

	configuration "Release"
		flags {
			"Optimize"
		}
		objdir    "obj/Release"
		targetdir "bin/Release"

	location("projects/".._ACTION)

	project "sampgdk"
		kind "StaticLib"
		files {
			"src/**.c",
			"src/**.cpp",
			"src/**.h",
			"include/**.h"
		}

	project "helloworld"
		kind "SharedLib"
		files {
			"examples/helloworld/*.*"
		}
		links "sampgdk"

