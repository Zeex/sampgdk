set(PLUGIN_NAME "unlimitedfs")

set(PLUGIN_SOURCES 
	filterscript.cpp
	filterscript.h
	plugin.cpp
	plugin.h
	unlimitedfs.cpp
)

if(WIN32)
	set(PLUGIN_SOURCES ${PLUGIN_SOURCES} 
		dlfcn.c
		dlfcn.h
	)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include(SampPlugin)

set_property(TARGET ${PLUGIN_TARGET} PROPERTY FOLDER "sampgdk/samples")
target_link_libraries(${PLUGIN_TARGET} sampgdk)
