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
		"lib",
		"lib/amx",
		"include" 
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
			"lib/amx/amx.h",
			"lib/amx/getch.h",
			"lib/amx/sclinux.h",
			"lib/amxplugin.cpp",
			"lib/plugin.h",
			"lib/plugincommon.h",
			"include/sampgdk/config.h",
			"include/sampgdk/eventhandler.h",
			"include/sampgdk/gpci.h",
			"include/sampgdk/objects.h",
			"include/sampgdk/players.h",
			"include/sampgdk/samp.h",
			"include/sampgdk/vehicles.h",
			"include/sampgdk/version.h",
			"include/sampgdk/wrapper.h",
			"src/callbacks.cpp",
			"src/callbacks.h",
			"src/eventhandler.cpp",
			"src/fakeamx.cpp",
			"src/fakeamx.h",
			"src/gpci.cpp",
			"src/jump-x86.cpp",
			"src/jump-x86.h",
			"src/objects.cpp",
			"src/players.cpp",
			"src/samp.cpp",
			"src/vehicles.cpp",
			"src/wrapper.cpp"
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

