cmake_minimum_required(VERSION 2.8)

project(unlimitedfs)

set(PLUGIN_NAME "unlimitedfs")

set(PLUGIN_SOURCES 
	filterscript.cpp
	filterscript.h
	plugin.cpp
	plugin.h
	unlimitedfs.cpp
)

if(WIN32)
	set(PLUGIN_SOURCES ${PLUGIN_SOURCES} 
		dlfcn.c
		dlfcn.h
	)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) # for <dlfcn.h>

include(SampPlugin)

target_link_libraries(${PLUGIN_TARGET} sampgdk)
