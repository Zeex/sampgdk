-- SA:MP Gamemode Development Kit for C++
-- Premake 4 build script

solution "sampgdk"
	configurations {
		"DebugLib",   -- static library - Debug
		"DebugDLL",   -- shared library - Debug
		"ReleaseLib", -- static library 
		"ReleaseDLL"  -- shared library
	}

	platforms {
		"x32"
	}

	defines {
		"IN_SAMPGDK"  -- used to define appropriate SAMPGDK_EXPORT macro
	}

	includedirs {
		"include",             -- GDK public headers directory
		"include/sampgdk/amx"  -- some source files #include "amx.h" 
	}

	flags {
		"No64BitChecks",
		"NoPCH"
	}

	-- static libraries
	configuration "*Lib"
		kind "StaticLib"
		defines "SAMPGDK_STATIC"

	-- dynamic libraries
	configuration "*DLL"
		kind "SharedLib"

	-- debug builds
	configuration "Debug*"
		flags {
			"ExtraWarnings",
			"Symbols"
		}
		objdir    "obj/Debug"
		targetdir "bin/Debug"

	-- release builds
	configuration "Release*"
		flags {
			"Optimize"
		}
		objdir    "obj/Release"
		targetdir "bin/Release"

	-- MinGW or Cygwin
	configuration {"windows", "gmake or codeblocks"}
		implibprefix ""
		targetprefix ""

	function getCompilerAbbrev()
		local action2compiler = {
			vs2010 = "VC10",
			vs2008 = "VC9",
			vs2005 = "VC8",
			vs2003 = "VC71",
			vs2002 = "VC7",
			gmake = "G",
			codeblocks = "G"
		}
		return action2compiler[_ACTION]
	end

	-- short string describing build configuration and toolset (Windows only)
	compiler = getCompilerAbbrev()
	configuration {"windows", "ReleaseDLL"}
		targetsuffix(compiler)
	configuration {"windows", "ReleaseLib"}
		targetsuffix("S"..compiler)
	configuration {"windows", "DebugDLL"}
		targetsuffix("D"..compiler)
	configuration {"windows", "DebugLib"}
		targetsuffix("SD"..compiler)

	-- set project files locaiton
	location("project/".._ACTION)

	-- main project
	project "sampgdk"
		language "C++"

		files {
			"src/**.c",
			"src/**.cpp",
			"include/**.h"
		}

