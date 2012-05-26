# SampPlugin.cmake - code common to most of SA:MP plugins.
#
# This module makes use of the following variables:
#   PLUGIN_NAME           The plugin name. Set to ${CMAKE_PROJECT_NAME} by default.
#   PLUGIN_SOURCES        The list of source files used to build the plugin.
#   PLUGIN_DEF            A full path to a module definition (.def) file.
#                         Set to ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.def by default.
#
#  In turn, this module defines the following variables:
#    PLUGIN_TARGET        The name of the target used to compile the plugin.
#
# Supported platforms:
#   Windows
#   Linux
#
# Supported compilers:
#   GCC
#   MinGW
#   Microsoft Visual C++

include(AmxConfig)

if(NOT DEFINED PLUGIN_NAME)
	set(PLUGIN_NAME "${CMAKE_PROJECT_NAME}")
endif()
if(PLUGIN_NAME STREQUAL "")
	message(FATAL_ERROR "At least one of PLUGIN_NAME/CMAKE_PROEJCT_NAME must be set")
endif()

if(NOT DEFINED PLUGIN_SOURCES OR PLUGIN_SOURCES STREQUAL "")
	message(FATAL_ERROR "PLUGIN_SOURCES is not defined")
endif()	

if(NOT DEFINED PLUGIN_DEF OR PLUGIN_DEF STREQUAL "")
	set(PLUGIN_DEF "${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.def")
	if(NOT EXISTS ${PLUGIN_DEF})
		set(PLUGIN_DEF "")
	endif()
endif()

set(PLUGIN_TARGET ${PLUGIN_NAME})

add_library(${PLUGIN_TARGET} MODULE ${PLUGIN_SOURCES})

set_target_properties(${PLUGIN_TARGET} PROPERTIES PREFIX "")

if(NOT PLUGIN_DEF STREQUAL "")
	if(MSVC)
		set_target_properties(${PLUGIN_TARGET} PROPERTIES 
				LINK_FLAGS "/DEF:${PLUGIN_DEF}")
	elseif(MINGW)
		set_target_properties(${PLUGIN_TARGET} PROPERTIES
				LINK_FLAGS "-Wl,--kill-at --def ${PLUGIN_DEF}")
	endif()
endif()

if(UNIX)
	add_definitions(-DLINUX)
endif()
if(WIN32)
	add_definitions(-DWIN32)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()
