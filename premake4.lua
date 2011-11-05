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

	configuration "windows"
		defines {"WIN32", "_WIN32"}

	configuration "linux"
		defines {"LINUX"}

	location("build/"..os.get().."/".._ACTION.."/")

	project "sampgdk"
		kind "StaticLib"
		defines {
			"AMX_NODYNLOAD"
		}
		files {
			"src/**.c",
			"src/**.cpp",
			"src/**.h",
			"include/**.h"
		}

	project "helloworld"
		kind "SharedLib"
		targetprefix ""
		flags {
			"NoImportLib"
		}
		files {
			"examples/helloworld/helloworld.cpp",
			"examples/helloworld/helloworld.h"
		}
		links "sampgdk"
		targetprefix ""
		configuration {"windows", "vs*"}
			linkoptions "/DEF:../../../examples/helloworld/helloworld.def"
		configuration {"windows", "gmake or codeblocks"}
			linkoptions "-Wl,--kill-at --def ../../../examples/helloworld/helloworld.def"

