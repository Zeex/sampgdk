cmake_minimum_required(VERSION 2.8)
project(lvdm)

include(SampPlugin)

if(MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_samp_plugin(${PROJECT_NAME}
	"lvdm.cpp"
	"lvdm.def"
)

file(RELATIVE_PATH folder ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${folder}")

target_link_libraries(${PROJECT_NAME} "sampgdk")
