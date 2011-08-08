cmake_minimum_required (VERSION 2.8)
project (sampgdk)

set (GDK_VERSION_MAJOR 1)
set (GDK_VERSION_MINOR 0)
set (GDK_VERSION_PATCH 1)

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
    add_definitions (-DWIN32 -DWINDOWS)
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

add_library (sampgdk-static STATIC ${SOURCES})
add_library (sampgdk-dynamic SHARED ${SOURCES})

if (UNIX AND NOT WIN32)
    set_target_properties (sampgdk-static PROPERTIES OUTPUT_NAME "sampgdk")
    set_target_properties (sampgdk-dynamic PROPERTIES OUTPUT_NAME "sampgdk")
elseif (WIN32)
    set_target_properties (sampgdk-static PROPERTIES OUTPUT_NAME "sampgdk_static")
    set_target_properties (sampgdk-dynamic PROPERTIES OUTPUT_NAME "sampgdk${GDK_VERSION_MAJOR}${GDK_VERSION_MINOR}")
endif (UNIX AND NOT WIN32)

set_target_properties (sampgdk-dynamic PROPERTIES 
    VERSION   ${GDK_VERSION_MAJOR}.${GDK_VERSION_MINOR}.${GDK_VERSION_PATCH}
    SOVERSION ${GDK_VERSION_MAJOR}.${GDK_VERSION_MINOR}
)

install (TARGETS sampgdk-dynamic sampgdk-static
    RUNTIME DESTINATION bin COMPONENT runtime
    LIBRARY DESTINATION lib COMPONENT libraries
    ARCHIVE DESTINATION lib COMPONENT libraries
)

install (DIRECTORY "include/sampgdk" DESTINATION "include" COMPONENT headers)

set (CPACK_PACKAGE_NAME "sampgdk")
set (CPACK_PACKAGE_VENDOR "Zeex")
set (CPACK_PACKAGE_CONTACT "zeex@rocketmail.com")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA:MP Gamemode Development Kit for C++")
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR ${GDK_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${GDK_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${GDK_VERSION_PATCH})
set (CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})

set (CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set (CPACK_COMPONENT_RUNTIME_DESCRIPTION "GDK's runtime libraries")
set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set (CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Static and import libraries")
set (CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ headers")
set (CPACK_COMPONENT_HEADERS_DESCRIPTION "C++ Header files for developing GDK-based plugins")
set (CPACK_COMPONENT_HEADERS_GROUP "Development")
set (CPACK_COMPONENT_HEADERS_DEPENDS libraries)

set (VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

if (WIN32)
    if (MSVC)
        set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VERSION}-msvc-install")
    elseif (MINGW)
        set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VERSION}-mingw-install")
    endif (MSVC) 
endif (WIN32)

include (CPack)

