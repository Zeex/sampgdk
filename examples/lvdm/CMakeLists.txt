cmake_minimum_required(VERSION 2.8)

project(lvdm)

add_library(lvdm MODULE lvdm.cpp)
set_target_properties(lvdm PROPERTIES PREFIX "")

if(WIN32)
	if(MSVC)
		set_target_properties(lvdm PROPERTIES 
				LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/lvdm.def")
	elseif(MINGW)
		set_target_properties(lvdm PROPERTIES
				LINK_FLAGS "-Wl,--kill-at --def ${CMAKE_CURRENT_SOURCE_DIR}/lvdm.def")
	endif()
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

target_link_libraries(lvdm sampgdk)
