set(PLUGIN_NAME "helloworld")
set(PLUGIN_SOURCES "helloworld.cpp")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include(SampPlugin)

set_property(TARGET ${PLUGIN_TARGET} PROPERTY FOLDER "sampgdk/samples")
target_link_libraries(${PLUGIN_TARGET} sampgdk)
