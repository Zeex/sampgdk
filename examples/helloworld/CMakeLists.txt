cmake_minimum_required(VERSION 2.8)

project(helloworld)

add_library(helloworld MODULE helloworld.cpp helloworld.h)
if(MSVC)
	set_target_properties(helloworld PROPERTIES LINK_FLAGS 
		"/DEF:${helloworld_SOURCE_DIR}/helloworld.def")
elseif(UNIX OR MINGW)
	set_target_properties(helloworld PROPERTIES LINK_FLAGS 
		"-Wl,--kill-at, --def ${helloworld_SOURCE_DIR}/helloworld.def")
endif()

target_link_libraries(helloworld sampgdk)
