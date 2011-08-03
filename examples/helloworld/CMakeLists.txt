cmake_minimum_required (VERSION 2.8)
project (helloworld)

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
check_include_file (stddef.h HAVE_STDDEF_H)
if (HAVE_STDDEF_H)
    add_definitions (-DHAVE_STDDEF_H)
endif (HAVE_STDDEF_H)
check_include_file (stdint.h HAVE_STDINT_H)     
if (HAVE_STDINT_H)
    add_definitions (-DHAVE_STDINT_H)
endif (HAVE_STDINT_H)

set (GDKPATH ../../)
set (DEFFILE ${helloworld_SOURCE_DIR}/helloworld.def)

include_directories (${GDKPATH}/include)

if (UNIX)
    add_definitions (-DLINUX)
    include_directories (${GDKPATH}/include/sampgdk/amx) # amx.h includes <sclinux.h>
    set (CMAKE_MODULE_LINKER_FLAGS -Wl,--no-undefined)
endif (UNIX)

if (WIN32)
    add_definitions (-DWIN32)
    if (MSVC)
        set (CMAKE_MODULE_LINKER_FLAGS /DEF:${DEFFILE})
    endif (MSVC)
endif (WIN32)

set (CMAKE_SHARED_MODULE_PREFIX "")
add_library (helloworld MODULE helloworld.cpp)

add_subdirectory (${GDKPATH} ${CMAKE_CURRENT_BINARY_DIR}/sampgdk)
target_link_Libraries (helloworld sampgdk)
