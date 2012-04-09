# Use this file to build GDK with CMake: http://cmake.org

project(sampgdk)
cmake_minimum_required(VERSION 2.8.6)

# Add ./cmake to CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sampgdk_SOURCE_DIR}/cmake")

include(AmxConfig)
include(ParseVersionString)

include_directories("${sampgdk_SOURCE_DIR}/include")
include_directories("${sampgdk_SOURCE_DIR}/include/amx")

add_library(sampgdk SHARED 
	"include/sampgdk/amx/amx.h"
	"include/sampgdk/amx/getch.h"
	"include/sampgdk/amx/sclinux.h"
	"include/sampgdk/a_objects.h"
	"include/sampgdk/a_players.h"
	"include/sampgdk/a_samp.h"
	"include/sampgdk/a_vehicles.h"
	"include/sampgdk/amx.h"
	"include/sampgdk/plugin.h"
	"include/sampgdk/plugincommon.h"
	"include/sampgdk/config.h"
	"include/sampgdk/core.h"
	"include/sampgdk/export.h"
	"include/sampgdk/version.h"
	"src/a_objects.cpp"
	"src/a_players.cpp"
	"src/a_samp.cpp"
	"src/a_vehicles.cpp"
	"src/amxhooks.cpp"
	"src/amxhooks.h"
	"src/amxplugin.cpp"
	"src/callbacks.cpp"
	"src/callbacks.h"
	"src/core.cpp"
	"src/fakeamx.cpp"
	"src/fakeamx.h"
	"src/jump-x86.cpp"
	"src/jump-x86.h"
	"src/natives.cpp"
	"src/natives.h"
	"src/sampgdk.rc"
	"src/timers.cpp"
	"src/timers.h"
	"src/version.cpp"
)

# Read current version from VERSION.txt and set appropriate variables
file(STRINGS "${sampgdk_SOURCE_DIR}/VERSION.txt" SAMPGDK_VERSION_STRING LIMIT_COUNT 1)
parse_version_string(${SAMPGDK_VERSION_STRING}
	SAMPGDK_VERSION_MAJOR
	SAMPGDK_VERSION_MINOR
	SAMPGDK_VERSION_PATCH
	SAMPGDK_VERSION_TWEAK
)

# FIXME: Manually set ABI version
set(SAMPGDK_VERSION_ABI 3)

# Generate or update include/sampgdk/version.h
configure_file(
	"${sampgdk_SOURCE_DIR}/version.h.in"
	"${sampgdk_SOURCE_DIR}/include/sampgdk/version.h"
)

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
		OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_ABI}")
elseif(UNIX)
	add_definitions(-DLINUX)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   ${SAMPGDK_VERSION_STRING}
		SOVERSION ${SAMPGDK_VERSION_ABI}
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

set(CPACK_PACKAGE_NAME "libsampgdk${SAMPGDK_VERSION_ABI}") 
set(CPACK_PACKAGE_VENDOR "Zeex")
set(CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA-MP Gamemode Development Kit for C/C++")
set(CPACK_RESOURCE_FILE_LICENSE "${sampgdk_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})

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

