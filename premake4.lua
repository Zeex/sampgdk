-- SA:MP Gamemode Development Kit for C++
-- Premake 4 script

solution "sampgdk"

	kind "StaticLib"
	language "C++"

	configurations {
		"Debug",  
		"Release"  
	}

	platforms "x32"

	defines {
		"IN_SAMPGDK"
	}

	includedirs {
		"include",             -- public headers 
		"include/sampgdk/amx"  -- some files include "amx.h" directly
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

	location("project/".._ACTION)

	project "sampgdk"
		files {
			"src/**.c",
			"src/**.cpp",
			"include/**.h"
		}

