cmake_minimum_required(VERSION 2.8)
project(sampgdk)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 9)
set(VERSION_PATCH 9)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

include(CheckIncludeFile)

include_directories("${sampgdk_SOURCE_DIR}/include")
include_directories("${sampgdk_SOURCE_DIR}/include/sampgdk/amx")

function(check_include_and_define include_file define)
	check_include_file(${include_file} HAVE_${include_file})
	if(HAVE_${include_file})
		add_definitions(-D${define})
	endif()
endfunction()

check_include_and_define(alloca.h HAVE_ALLOCA_H)
check_include_and_define(inttypes.h HAVE_INTTYPES_H)
check_include_and_define(malloc.h HAVE_MALLOC_H)
check_include_and_define(stdint.h HAVE_STDINT_H)

# AMX definitions
add_definitions(
	-DAMX_NODYNLOAD # Disable dynamically loaded modules 
)

# OS definitions
if(UNIX)
	add_definitions(-DUNIX)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		add_definitions(-DLINUX)
	endif()
	if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		add_definitions(-DFREEBSD)
	endif()
elseif(WIN32)
	add_definitions(-DWIN32 -D_WIN32)
endif()

set(SOURCES
	src/amx/amx.c
	src/amxapihooks.cpp
	src/callbacks.cpp
	src/eventhandler.cpp
	src/fakeamx.cpp
	src/funcidx.cpp
	src/gamemode.cpp
	src/gpci.cpp
	src/hooknative.cpp
	src/jump.cpp
	src/objects.cpp
	src/players.cpp
	src/samp.cpp
	src/vehicles.cpp
	src/wrapper.cpp
	src/wrapperimpl.cpp
)

add_library(sampgdk-shared SHARED ${SOURCES})
set_target_properties(sampgdk-shared PROPERTIES 
	OUTPUT_NAME "sampgdk"
	COMPILE_DEFINITIONS "IN_SAMPGDK"
	VERSION ${VERSION}
	SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
if(WIN32)
	# Set DLL exports file on Windows
	set(DEF_FILE "${sampgdk_SOURCE_DIR}/src/sampgdk.def")
	if(MINGW)
		set_property(TARGET sampgdk-shared APPEND PROPERTY LINK_FLAGS "-Wl,--kill-at --def=${DEF_FILE}")
	else()
		set_property(TARGET sampgdk-shared APPEND PROPERTY LINK_FLAGS "/DEF:${DEF_FILE}")
	endif()
endif()

add_library(sampgdk-static STATIC ${SOURCES})
set_target_properties(sampgdk-static  PROPERTIES 
	COMPILE_DEFINITIONS "IN_SAMPGDK; SAMPGDK_STATIC")
if(WIN32 AND NOT MINGW)
	set_target_properties(sampgdk-static PROPERTIES OUTPUT_NAME "sampgdkS")
else()
	set_target_properties(sampgdk-static PROPERTIES OUTPUT_NAME "sampgdk")
endif()

if(UNIX OR MINGW)
	set_target_properties(sampgdk-shared sampgdk-static PROPERTIES
		COMPILE_FLAGS "-m32 -Wno-attibutes" LINK_FLAGS "-m32")
endif()

if(WIN32)
	set_target_properties(sampgdk-shared sampgdk-static PROPERTIES DEBUG_POSTFIX "D")
	if(MSVC)
		if(MSVC10)
			set(VC "VC10")
		elseif(MSVC90)
			set(VC "VC9")
		elseif(MSVC80)
			set(VC "VC9")
		elseif(MSVC71)
			set(VC "VC71")
		elseif(MSVC70)
			set(VC "VC7")
		elseif(MSVC60)
			set(VC "VC6")
		else()
			message(FATAL_ERROR "Unknown MSVC version")
		endif()
		set_target_properties(sampgdk-shared sampgdk-static PROPERTIES 
			SUFFIX        "${VC}.dll"
			IMPORT_SUFFIX "${VC}.lib")
	elseif(MINGW)
		set_target_properties(sampgdk-shared PROPERTIES
			PREFIX        ""
			SUFFIX        "G.dll"
			IMPORT_PREFIX ""
			IMPORT_SUFFIX "G.dll.a")
		set_target_properties(sampgdk-static PROPERTIES
			PREFIX        ""
			SUFFIX        "G.a")
	else()
		message(FATAL_ERROR "Unsupported compiler")
	endif()
endif()

install(TARGETS sampgdk-shared sampgdk-static
	RUNTIME DESTINATION "bin" COMPONENT runtime
	LIBRARY DESTINATION "lib" COMPONENT libraries
	ARCHIVE DESTINATION "lib" COMPONENT libraries
)

install(DIRECTORY "include" DESTINATION "." COMPONENT headers)

