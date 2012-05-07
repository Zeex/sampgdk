set(PLUGIN_NAME "helloworld")
set(PLUGIN_SOURCES "helloworld.cpp")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include(SampPlugin)

target_link_libraries(${PLUGIN_TARGET} sampgdk)
