cmake_minimum_required (VERSION 2.8)
project (sampgdk)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 9)
set (VERSION_PATCH 9)

set (VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

include (CheckIncludeFile)

check_include_file (alloca.h HAVE_ALLOCA_H)
if (HAVE_ALLOCA_H)
	add_definitions (-DHAVE_ALLOCA_H)
endif (HAVE_ALLOCA_H)
check_include_file (inttypes.h HAVE_INTTYPES_H)
if (HAVE_INTTYPES_H)
	add_definitions (-DHAVE_INTTYPES_H)
endif (HAVE_INTTYPES_H)
check_include_file (malloc.h HAVE_MALLOC_H)
if (HAVE_MALLOC_H)
	add_definitions (-DHAVE_MALLOC_H)
endif (HAVE_MALLOC_H)
check_include_file (stdint.h HAVE_STDINT_H)	 
if (HAVE_STDINT_H)
	add_definitions (-DHAVE_STDINT_H)
endif (HAVE_STDINT_H)

include_directories ("include")
include_directories ("include/sampgdk/amx") # amx.h includes <sclinux.h>

add_definitions (-DIN_SAMPGDK)

if (UNIX)
	add_definitions (-DUNIX)
	if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		add_definitions (-DLINUX)
	endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		add_definitions (-DFREEBSD)
	endif (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
endif (UNIX)

if (WIN32)
	add_definitions (-DWIN32 -D_WIN32)
endif (WIN32)

set (SOURCES
	src/amxapihooks.cpp
	src/amxplugin.cpp
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

if (UNIX OR MINGW)
	set (CMAKE_CXX_FLAGS "-m32")
endif (UNIX OR MINGW)

add_library (sampgdk-shared SHARED ${SOURCES})
set_target_properties (sampgdk-shared PROPERTIES OUTPUT_NAME sampgdk)

if (WIN32)
	set (DEF_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.def")
	if (MINGW OR CYGWIN)
		set (CMAKE_SHARED_LINKER_FLAGS "--def=${DEF_FILE}")
	else (MINGW OR CYGWIN)
		set (CMAKE_SHARED_LINKER_FLAGS "/DEF:${DEF_FILE}")
	endif (MINGW OR CYGWIN)
endif (WIN32)

add_library (sampgdk-static STATIC ${SOURCES})
set_target_properties (sampgdk-static PROPERTIES OUTPUT_NAME "sampgdk")
set_target_properties (sampgdk-static PROPERTIES COMPILE_DEFINITIONS "SAMPGDK_STATIC")

if (MSVC)
	set_target_properties (sampgdk-static PROPERTIES OUTPUT_NAME "sampgdk_static")
endif (MSVC)

set_target_properties (sampgdk-shared PROPERTIES 
	VERSION   ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)

install (TARGETS sampgdk-shared sampgdk-static
	RUNTIME DESTINATION "bin" COMPONENT runtime
	LIBRARY DESTINATION "lib" COMPONENT libraries
	ARCHIVE DESTINATION "lib" COMPONENT libraries
)

install (DIRECTORY "src"     DESTINATION "." COMPONENT sources)
install (DIRECTORY "include" DESTINATION "." COMPONENT headers)

set (CPACK_PACKAGE_NAME sampgdk) 
set (CPACK_PACKAGE_VENDOR "Zeex")
set (CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA:MP Gamemode Development Kit for C++")
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set (CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set (CPACK_NSIS_MODIFY_PATH ON)

set (CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set (CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime library")
set (CPACK_COMPONENT_RUNTIME_INSTALL_TYPES "Full" "Runtime Only")
set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set (CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Static and import libraries")
set (CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set (CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES "Full")
set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ headers")
set (CPACK_COMPONENT_HEADERS_DESCRIPTION "C++ header files for developers")
set (CPACK_COMPONENT_HEADERS_GROUP "Development")
set (CPACK_COMPONENT_HEADERS_INSTALL_TYPES "Full")
set (CPACK_COMPONENT_HEADERS_DEPENDS libraries)
set (CPACK_COMPONENT_SOURCES_DISPLAY_NAME "Source")
set (CPACK_COMPONENT_SOURCES_DESCRIPTION "Source code")
set (CPACK_COMPONENT_SOURCES_INSTALL_TYPES "Full")

if (WIN32)
	if (MSVC)
		set (COMPILER "msvc")
	elseif (MINGW)
		set (COMPILER "mingw")
	endif (MSVC) 
	set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VERSION}-${COMPILER}")
endif (WIN32)

include (CPack)

