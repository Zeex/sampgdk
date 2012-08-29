cmake_minimum_required(VERSION 2.8)

project(subhook)

include(CheckFunctionExists)

set(SUBHOOK_HEADERS "subhook.h" "subhook_private.h")
set(SUBHOOK_SOURCES "subhook.c")

add_definitions(-DSUBHOOK_IMPLEMENTATION)

function(get_machine_arch ARCH)
	if(WIN32)
		set(${ARCH} $ENV{PROCESSOR_ARCHITECTURE} PARENT_SCOPE)
	elseif(UNIX)
		execute_process(COMMAND uname -m RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_ARCH)
		if (UNAME_ARCH MATCHES "i[3-6]86")
			set(${ARCH} x86 PARENT_SCOPE)
		endif()
	endif()
endfunction()

if(WIN32)
	list(APPEND SUBHOOK_SOURCES "subhook_windows.c")
elseif(UNIX)
	list(APPEND SUBHOOK_SOURCES "subhook_linux.c")
endif()

if(NOT DEFINED SUBHOOK_ARCH)
	get_machine_arch(SUBHOOK_ARCH)
endif()

if(SUBHOOK_ARCH STREQUAL x86)
	add_definitions(-DSUBHOOK_ARCH_X86)
	list(APPEND SUBHOOK_SOURCES "subhook_x86.c")
else()
	message(FATAL_ERROR "Unsupported architecture \"${SUBHOOK_ARCH}\" (only x86 is supported")
endif()

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
