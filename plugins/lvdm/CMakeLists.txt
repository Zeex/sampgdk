cmake_minimum_required(VERSION 2.8)
project(lvdm)

include(SampPlugin)

if(MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_samp_plugin(lvdm
	"lvdm.cpp"
	"lvdm.def"
)

target_link_libraries(lvdm "sampgdk")
