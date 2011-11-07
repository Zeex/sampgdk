cmake_minimum_required(VERSION 2.8)

project(helloworld)

add_library(helloworld MODULE 
	helloworld.cpp 
	helloworld.h)

set(def_file "${helloworld_SOURCE_DIR}/helloworld.def")

if(MSVC)
	set_target_properties(helloworld PROPERTIES 
		LINK_FLAGS "/DEF:${def_file}")
elseif(MINGW)
	set_target_properties(helloworld PROPERTIES 
		LINK_FLAGS "-Wl,--kill-at --def ${def_file}")
endif()

if (UNIX OR MINGW)
	set_target_properties(helloworld PROPERTIES PREFIX "")
endif()

target_link_libraries(helloworld sampgdk)
