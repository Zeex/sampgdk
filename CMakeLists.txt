cmake_minimum_required(VERSION 2.8)

project(sampgdk)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CheckIncludeFile)

set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

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

add_definitions(-DIN_SAMPGDK)

include_directories(
	"${sampgdk_SOURCE_DIR}/include"
	"${sampgdk_SOURCE_DIR}/include/sampgdk/amx"
)

if(UNIX)
	include_directories("src/amx") 
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		add_definitions(-DLINUX)
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		add_definitions(-DFREEBSD)
	endif()
elseif(WIN32)
	add_definitions(-DWIN32 -D_WIN32)
endif()

set(SOURCES
	src/amx/amx.c
	src/callbacks.cpp
	src/core.cpp
	src/fakeamx.cpp
	src/funcidx.cpp
	src/gamemode.cpp
	src/gpci.cpp
	src/hooknative.cpp
	src/jump.cpp
	src/natives.cpp
	src/objects.cpp
	src/players.cpp
	src/samp.cpp
	src/vehicles.cpp
)

add_library(sampgdk SHARED ${SOURCES})

set_target_properties(sampgdk PROPERTIES 
	OUTPUT_NAME   "sampgdk"
	SUFFIX        "${VERSION_MAJOR}.dll"
	IMPORT_SUFFIX "${VERSION_MAJOR}.lib"
	DEBUG_POSTFIX "D"
)

if(WIN32)
	set(DEF_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.def")
	if(MINGW)
		set_target_properties(sampgdk PROPERTIES LINK_FLAGS "-Wl,--kill-at --def=${DEF_FILE}")
	else()
		set_target_properties(sampgdk PROPERTIES LINK_FLAGS "/DEF:${DEF_FILE}")
	endif()
	set_target_properties(sampgdk PROPERTIES PREFIX "")
endif()

set_target_properties(sampgdk PROPERTIES 
	VERSION   ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)

find_package(DynCall REQUIRED)
include_directories(${DYNCALL_INCLUDE_DIRS})
target_link_libraries(sampgdk ${DYNCALL_LIBRARIES})

install(TARGETS sampgdk 
	RUNTIME DESTINATION "bin" COMPONENT runtime
	LIBRARY DESTINATION "lib" COMPONENT libraries
	ARCHIVE DESTINATION "lib" COMPONENT libraries
)

install(DIRECTORY "include" DESTINATION "." COMPONENT headers)

set(CPACK_PACKAGE_NAME sampgdk) 
set(CPACK_PACKAGE_VENDOR "Zeex")
set(CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA:MP Gamemode Development Kit for C++")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_NSIS_MODIFY_PATH ON)

set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime library")
set(CPACK_COMPONENT_RUNTIME_INSTALL_TYPES "Full" "Runtime Only")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Import library")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES "Full")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ headers")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C++ header files for plugin developers")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES "Full")
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

include(CPack)

# Build sample projects
add_subdirectory(samples)
