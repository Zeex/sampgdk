# AMX configuration

include(CheckIncludeFile)

check_include_file(alloca.h HAVE_ALLOCA_H)
if(HAVE_ALLOCA_H)
	add_definitions(-DHAVE_ALLOCA_H)
endif()
check_include_file(inttypes.h HAVE_INTTYPES_H)
if(HAVE_INTTYPES_H)
	add_definitions(-DHAVE_INTTYPES_H)
endif()
check_include_file(malloc.h HAVE_MALLOC_H)
if(HAVE_MALLOC_H)
	add_definitions(-DHAVE_MALLOC_H)
endif()
check_include_file(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
	add_definitions(-DHAVE_STDINT_H)
endif()

