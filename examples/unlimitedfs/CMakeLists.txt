cmake_minimum_required(VERSION 2.8)

project(unlimitedfs)

set(SOURCES 
	filterscript.cpp
	filterscript.h
	plugin.cpp
	plugin.h
	unlimitedfs.cpp)

if(WIN32)
	set(SOURCES ${SOURCES} 
		dlfcn.c
		dlfcn.h)
endif()

add_library(unlimitedfs MODULE ${SOURCES})
set_target_properties(unlimitedfs PROPERTIES PREFIX "")

if(WIN32)
	if(MSVC)
		set_target_properties(unlimitedfs PROPERTIES 
				LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/unlimitedfs.def")
		include_directories(${unlimitedfs_SOURCE_DIR})
	elseif(MINGW)
		set_target_properties(unlimitedfs PROPERTIES
				LINK_FLAGS "-Wl,--kill-at --def ${CMAKE_CURRENT_SOURCE_DIR}/unlimitedfs.def")
	endif()
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

target_link_libraries(unlimitedfs sampgdk)
