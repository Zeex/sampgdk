cmake_minimum_required(VERSION 2.8)
project(helloworld)

include(GroupTargetSources)
include(SampPlugin)

if(MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_samp_plugin(helloworld
	"helloworld.cpp"
	"helloworld.def"
)

group_target_sources(unlimitedfs)
target_link_libraries(helloworld "sampgdk")
