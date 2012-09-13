cmake_minimum_required(VERSION 2.8)

include(SampPlugin)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_samp_plugin(unlimitedfs
	filterscript.cpp
	filterscript.h
	plugin.cpp
	plugin.h
	unlimitedfs.cpp
	unlimitedfs.def
)

target_link_libraries(unlimitedfs sampgdk)
