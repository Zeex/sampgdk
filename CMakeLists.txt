# SA:MP Gamemode SDK for C++ 
# CmakeLists.txt for building GDK as a static library

cmake_minimum_required (VERSION 2.8)
project (sampgdk)

set (GDK_VERSION_MAJOR 1)
set (GDK_VERSION_MINOR 0)
set (GDK_VERSION_PATCH 0)

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
    if (MINGW)
        add_definitions (-DMINGW)
    endif (MINGW)
endif (WIN32)

set (SOURCES
    src/amxapihooks.cpp
    src/amxplugin.cpp
    src/callbacks.cpp
    src/eventhandler.cpp
    src/fakeamx.cpp
    src/funcidx.cpp
    src/gamemode.cpp
    src/hooknative.cpp
    src/jump.cpp
    src/objects.cpp
    src/players.cpp
    src/samp.cpp
    src/vehicles.cpp
    src/wrapper.cpp
    src/wrapperimpl.cpp
)

add_library (sampgdk SHARED ${SOURCES})
add_library (sampgdk_static STATIC ${SOURCES})

set_target_properties (sampgdk PROPERTIES 
    VERSION   ${GDK_VERSION_MAJOR}.${GDK_VERSION_MINOR}.${GDK_VERSION_PATCH}
    SOVERSION ${GDK_VERSION_MAJOR}.${GDK_VERSION_MINOR}
)

if (WIN32)
    if (MSVC)
        set_target_properties (sampgdk PROPERTIES SUFFIX "${GDK_VERSION_MAJOR}.dll")
    endif (MSVC)
    if (MINGW)
        set_target_properties (sampgdk PROPERTIES SUFFIX "${GDK_VERSION_MAJOR}-gcc.dll")
    endif (MINGW)
endif (WIN32)

install (TARGETS sampgdk sampgdk_static
    RUNTIME DESTINATION bin COMPONENT Runtime
    LIBRARY DESTINATION lib COMPONENT Development
    ARCHIVE DESTINATION lib COMPONENT Development
)

install (DIRECTORY include/sampgdk DESTINATION include COMPONENT Development)

set (CPACK_PACKAGE_NAME sampgdk)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "SA:MP Gamemode Development Kit for C/C++")
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR ${GDK_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${GDK_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${GDK_VERSION_PATCH})

if (WIN32)
    set (CPACK_PACKAGE_FILE_NAME 
        "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
    if (MINGW)
        set (CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}-gcc)
    endif (MINGW)
    set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-install")
endif (WIN32)

include (CPack)

