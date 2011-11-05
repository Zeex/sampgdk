cmake_minimum_required(VERSION 2.8)
project(sampgdk)

include(CheckIncludeFile)
include_directories("${sampgdk_SOURCE_DIR}/include")

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

# OS definitions
if(UNIX)
	add_definitions(-DUNIX)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		add_definitions(-DLINUX)
	endif()
	if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		add_definitions(-DFREEBSD)
	endif()
elseif(WIN32)
	add_definitions(-DWIN32 -D_WIN32)
endif()

add_library(sampgdk STATIC
	"include/sampgdk/amx/amx.h"
	"include/sampgdk/amx/getch.h"
	"include/sampgdk/amx/sclinux.h"
	"include/sampgdk/amx.h"
	"include/sampgdk/eventhandler.h"
	"include/sampgdk/gpci.h"
	"include/sampgdk/objects.h"
	"include/sampgdk/players.h"
	"include/sampgdk/plugincommon.h"
	"include/sampgdk/samp.h"
	"include/sampgdk/vehicles.h"
	"include/sampgdk/wrapper.h"
	"include/sampgdk.h"
	"src/amxplugin.cpp"
	"src/callbacks.cpp"
	"src/callbacks.h"
	"src/eventhandler.cpp"
	"src/fakeamx.cpp"
	"src/fakeamx.h"
	"src/gpci.cpp"
	"src/jump.cpp"
	"src/jump.h"
	"src/objects.cpp"
	"src/players.cpp"
	"src/samp.cpp"
	"src/vehicles.cpp"
	"src/wrapper.cpp")

add_subdirectory(examples)

