cmake_minimum_required (VERSION 2.8)

project (sampgdk)
include (CheckIncludeFile)

set (LIBRARY_NAME sampgdk)

set (VERSION_MAJOR 2)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)
	
set (VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

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

add_definitions (-DIN_SAMPGDK)
include_directories ("include")

if (UNIX)
	include_directories ("src/amx") 
	if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		add_definitions (-DLINUX)
	endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		add_definitions (-DFREEBSD)
	endif (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
endif (UNIX)

if (WIN32)
	add_definitions (-DWIN32)
endif (WIN32)

set (SOURCES
	src/amxplugin.cpp
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

add_library (sampgdk SHARED ${SOURCES})
set_target_properties (sampgdk PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})

if (WIN32 AND NOT UNIX)
	include_directories (${DYNCALL_INCLUDE_DIR})
	target_link_libraries (sampgdk ${DYNCALL_LIBRARY_DIR}/libdyncall_s.lib)
endif (WIN32 AND NOT UNIX)

if (WIN32)
	set_target_properties (sampgdk PROPERTIES PREFIX "")
	set_target_properties (sampgdk PROPERTIES SUFFIX ${VERSION_MAJOR}${VERSION_MINOR}.dll)
endif (WIN32)

set_target_properties (sampgdk PROPERTIES 
	VERSION   ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)

install (TARGETS sampgdk 
	RUNTIME DESTINATION bin COMPONENT runtime
	LIBRARY DESTINATION lib COMPONENT libraries
	ARCHIVE DESTINATION lib COMPONENT libraries
)

install (DIRECTORY "include" DESTINATION "." COMPONENT headers)

set (CPACK_PACKAGE_NAME sampgdk) 
set (CPACK_PACKAGE_VENDOR "Zeex")
set (CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA:MP Gamemode Development Kit for C++")
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set (CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set (CPACK_NSIS_MODIFY_PATH ON)

set (CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set (CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime library")
set (CPACK_COMPONENT_RUNTIME_INSTALL_TYPES "Full" "Runtime Only")
set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set (CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Import library")
set (CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set (CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES "Full")
set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ headers")
set (CPACK_COMPONENT_HEADERS_DESCRIPTION "C++ header files for plugin developers")
set (CPACK_COMPONENT_HEADERS_GROUP "Development")
set (CPACK_COMPONENT_HEADERS_INSTALL_TYPES "Full")
set (CPACK_COMPONENT_HEADERS_DEPENDS libraries)

include (CPack)

