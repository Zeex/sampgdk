cmake_minimum_required(VERSION 2.8)

project(helloworld)

add_library(helloworld MODULE helloworld.cpp)
set_target_properties(helloworld PROPERTIES PREFIX "")

if(WIN32)
	if(MSVC)
		set_target_properties(helloworld PROPERTIES 
				LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/helloworld.def")
	elseif(MINGW)
		set_target_properties(helloworld PROPERTIES
				LINK_FLAGS "--def=${CMAKE_CURRENT_SOURCE_DIR}/helloworld.def")
	endif()
endif()

target_link_libraries(helloworld sampgdk)
