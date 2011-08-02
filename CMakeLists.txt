# SA:MP Gamemode SDK for C++ 
# CmakeLists.txt for building GDK as a static library

cmake_minimum_required (VERSION 2.8)
project (sampgdk)

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

include_directories (include)

if (UNIX)
    add_definitions (-DLINUX)
    include_directories (include/sampgdk/amx) # amx.h includes <sclinux.h>
endif (UNIX)

if (WIN32)
    add_definitions (-DWIN32)
endif (WIN32)

add_library (sampgdk STATIC 
    src/amxapihooks.cpp
    src/amxplugin.cpp
    src/callbacks.cpp
    src/eventhandler.cpp
    src/fakeamx.cpp
    src/funcidx.cpp
    src/gamemode.cpp
    src/jump.cpp
    src/logprintf.cpp
    src/objects.cpp
    src/players.cpp
    src/samp.cpp
    src/vehicles.cpp
    src/wrapper.cpp
)
