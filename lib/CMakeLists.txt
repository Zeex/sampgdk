cmake_minimum_required(VERSION 2.8)

set(SUBHOOK_ARCH "x86")
set(SUBHOOK_STATIC TRUE)

add_subdirectory("subhook")

list(APPEND LIB_LIBRARIES    "subhook")
list(APPEND LIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/subhook")
list(APPEND LIB_COMPILE_DEFS "SUBHOOK_STATIC")

function(lib_get_compile_defs var)
	set(${var} ${LIB_COMPILE_DEFS} PARENT_SCOPE)
endfunction()

function(lib_get_include_dirs var)
	set(${var} ${LIB_INCLUDE_DIRS} PARENT_SCOPE)
endfunction()

function(lib_get_libraries var)
	set(${var} ${LIB_LIBRARIES} PARENT_SCOPE)
endfunction()
