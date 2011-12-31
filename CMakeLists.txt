cmake_minimum_required(VERSION 2.8.6)

project(sampgdk)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CheckHeader)
include(GetGitRevisionDescription)

include_directories("${sampgdk_SOURCE_DIR}/include")
include_directories("${sampgdk_SOURCE_DIR}/include/amx")

check_header(alloca.h)
check_header(inttypes.h)
check_header(malloc.h)
check_header(stdint.h)
check_header(stdbool.h)

add_library(sampgdk SHARED 
	"include/sampgdk/amx/amx.h"
	"include/sampgdk/amx/getch.h"
	"include/sampgdk/amx/sclinux.h"
	"include/sampgdk/plugin.h"
	"include/sampgdk/plugincommon.h"
	"include/sampgdk/config.h"
	"include/sampgdk/core.h"
	"include/sampgdk/export.h"
	"include/sampgdk/gpci.h"
	"include/sampgdk/objects.h"
	"include/sampgdk/players.h"
	"include/sampgdk/samp.h"
	"include/sampgdk/vehicles.h"
	"include/sampgdk/version.h"
	"src/amxhooks.cpp"
	"src/amxhooks.h"
	"src/amxplugin.cpp"
	"src/callbacks.cpp"
	"src/callbacks.h"
	"src/core.cpp"
	"src/fakeamx.cpp"
	"src/fakeamx.h"
	"src/gpci.cpp"
	"src/jump-x86.cpp"
	"src/jump-x86.h"
	"src/natives.cpp"
	"src/natives.h"
	"src/objects.cpp"
	"src/players.cpp"
	"src/samp.cpp"
	"src/sampgdk.rc"
	"src/timers.cpp"
	"src/timers.h"
	"src/vehicles.cpp"
	"src/version.cpp"
)

set(version_tag_regex "v([0-9]+)\\.([0-9]+)\\.([0-9]+)-?([0-9]*)-?g?([a-f0-9]*)")
git_describe(description --match v[0-9]*.[0-9]*.[0-9]*)
if(description MATCHES ${version_tag_regex})
	string(REGEX REPLACE ${version_tag_regex} 
		"\\1;\\2;\\3;\\4;\\5" version_components ${description})
	list(GET version_components 0 version_major)
	list(GET version_components 1 version_minor)
	list(GET version_components 2 version_patch)
	list(GET version_components 3 version_commit)
	if(version_commit STREQUAL "")
		set(version_commit 0)
		set(version_string ${version_major}.${version_minor}.${version_patch})
	else()
		set(version_string ${version_major}.${version_minor}.${version_patch}.${version_commit})
	endif()
else()
	message(FATAL_ERROR "Couldn't obtain version info")
endif()

file(WRITE "include/sampgdk/version.h" 
"/* Version information */ 

#ifndef SAMPGDK_VERSION_H
#define SAMPGDK_VERSION_H

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#define SAMPGDK_VERSION_MAJOR ${version_major}
#define SAMPGDK_VERSION_MINOR ${version_minor}
#define SAMPGDK_VERSION_PATCH ${version_patch}
#define SAMPGDK_VERSION_COMMIT ${version_commit}
#define SAMPGDK_VERSION_STRING \"${version_string}\"

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_version();
SAMPGDK_EXPORT const char *SAMPGDK_CALL sampgdk_version_string();

#endif
")

set_target_properties(sampgdk PROPERTIES DEBUG_POSTFIX "_d")

# Needed for SAMPGDK_EXPORT macro to be defined correctly on Windows
add_definitions(-DIN_SAMPGDK)

# Output library properties
if(WIN32)
	# Set module definition file
	set(DEF_FILE "${sampgdk_SOURCE_DIR}/src/sampgdk.def")
	if(MINGW)
		set_property(TARGET sampgdk APPEND_STRING PROPERTY 
			LINK_FLAGS " -Wl,--kill-at --def ${DEF_FILE}")
	else()
		set_property(TARGET sampgdk APPEND_STRING PROPERTY 
			LINK_FLAGS " /DEF:${DEF_FILE}")
	endif()
	set_target_properties(sampgdk PROPERTIES 
		PREFIX      ""
		OUTPUT_NAME "sampgdk${version_major}")
elseif(UNIX)
	add_definitions(-DLINUX)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   ${version_major}.${version_minor}.${version_patch}
		SOVERSION ${version_major}
	)
endif()

option(USE_STATIC_CXX_RUNTIME "Prefer static C/C++ runtime" ON)

# Compiler/linker options
if(UNIX OR MINGW)
	set_property(TARGET sampgdk APPEND_STRING PROPERTY 
		COMPILE_FLAGS " -m32 -Wno-attributes")
	if(WIN32)
		# Link with static libgcc/libstdc++
		set_property(TARGET sampgdk APPEND_STRING PROPERTY
			LINK_FLAGS " -m32 -Wl,--export-all-symbols")
		if(USE_STATIC_CXX_RUNTIME)
			set_property(TARGET sampgdk APPEND_STRING PROPERTY
				LINK_FLAGS " -static-libgcc -static-libstdc++")
		endif()
	else()
		set_property(TARGET sampgdk APPEND_STRING PROPERTY
			LINK_FLAGS " -m32 -Wl,--export-dynamic")
	endif()
elseif(MSVC)
	if(USE_STATIC_CXX_RUNTIME)
		# Use static VC++ runtime in all configuraions except Debug
		foreach(flag_var
        		CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE
        		CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   	   	   if(${flag_var} MATCHES "/MD" AND NOT ${flag_var} MATCHES "/MDd")
      	      	      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   	   	   endif()
		endforeach(flag_var)
	endif()
endif()

message(STATUS "Version: ${version_string}")

install(TARGETS sampgdk 
	RUNTIME DESTINATION "bin" COMPONENT "runtime"
	LIBRARY DESTINATION "lib" COMPONENT "libraries"
	ARCHIVE DESTINATION "lib" COMPONENT "libraries"
)

install(DIRECTORY "include" DESTINATION "." COMPONENT "headers")

if(MSVC)
	get_target_property(output_name sampgdk OUTPUT_NAME)
	set(PDB_NAME "${output_name}.pdb")
	set(PDB_PATH "${CMAKE_CURRENT_BINARY_DIR}/\${CMAKE_INSTALL_CONFIG_NAME}/${PDB_NAME}")
	install(FILES ${PDB_PATH} DESTINATION "bin" COMPONENT "runtime")
endif()

set(CPACK_PACKAGE_NAME "libsampgdk") 
set(CPACK_PACKAGE_VENDOR "Zeex")
set(CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA-MP Gamemode Development Kit for C/C++")
set(CPACK_RESOURCE_FILE_LICENSE "${sampgdk_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${version_major})
set(CPACK_PACKAGE_VERSION_MINOR ${version_minor})
set(CPACK_PACKAGE_VERSION_PATCH ${version_patch})

set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime library")
set(CPACK_COMPONENT_RUNTIME_INSTALL_TYPES "Full" "Runtime Only")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Import library")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES "Full")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C/C++ headers")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C/C++ header files for developers")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES "Full")
set(CPACK_COMPONENT_HEADERS_DEPENDS "libraries")

# NSIS
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)

# Build sample projects
add_subdirectory(examples)
