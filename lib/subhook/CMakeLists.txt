cmake_minimum_required(VERSION 2.8)

project(subhook)

set(SUBHOOK_HEADERS "subhook.h")
set(SUBHOOK_SOURCES "subhook.c" "subhook_private.h")

add_definitions(-DSUBHOOK_IMPLEMENTATION)

if(SUBHOOK_STATIC)
	add_definitions(-DSUBHOOK_STATIC)
	add_library(subhook STATIC ${SUBHOOK_HEADERS} ${SUBHOOK_SOURCES})
else()
	add_library(subhook SHARED ${SUBHOOK_HEADERS} ${SUBHOOK_SOURCES})
endif()

if(SUBHOOK_INSTALL)
	install(TARGETS subhook LIBRARY DESTINATION "lib")
	install(FILES ${SUBHOOK_HEADERS} DESTINATION "include")
endif()
