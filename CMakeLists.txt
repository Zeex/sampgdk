cmake_minimum_required(VERSION 2.8)

project(sampgdk2)

include(CheckIncludeFile)

include_directories("${sampgdk2_SOURCE_DIR}/lib")
include_directories("${sampgdk2_SOURCE_DIR}/lib/amx")
include_directories("${sampgdk2_SOURCE_DIR}/include")

function(check_include_and_define include_file define)
	check_include_file(${include_file} HAVE_${include_file})
	if(HAVE_${include_file})
		add_definitions(-D${define})
	endif()
endfunction()

check_include_and_define("alloca.h"   "HAVE_ALLOCA_H")
check_include_and_define("inttypes.h" "HAVE_INTTYPES_H")
check_include_and_define("malloc.h"   "HAVE_MALLOC_H")
check_include_and_define("stdint.h"   "HAVE_STDINT_H")

add_library(sampgdk2 SHARED 
	"lib/amx/amx.h"
	"lib/amx/getch.h"
	"lib/amx/sclinux.h"
	"lib/amxplugin.cpp"
	"lib/plugin.h"
	"lib/plugincommon.h"
	"include/sampgdk/config.h"
	"include/sampgdk/core.h"
	"include/sampgdk/eventhandler.h"
	"include/sampgdk/export.h"
	"include/sampgdk/gpci.h"
	"include/sampgdk/objects.h"
	"include/sampgdk/players.h"
	"include/sampgdk/samp.h"
	"include/sampgdk/vehicles.h"
	"include/sampgdk/version.h"
	"src/callbacks.cpp"
	"src/callbacks.h"
	"src/core.cpp"
	"src/eventhandler.cpp"
	"src/fakeamx.cpp"
	"src/fakeamx.h"
	"src/gpci.cpp"
	"src/jump-x86.cpp"
	"src/jump-x86.h"
	"src/objects.cpp"
	"src/players.cpp"
	"src/samp.cpp"
	"src/vehicles.cpp"
	"src/wrapper.h"
	"src/wrapper.cpp"
)

set_property(TARGET sampgdk2 APPEND PROPERTY 
	COMPILE_DEFINITIONS "IN_SAMPGDK")

