cmake_minimum_required(VERSION 2.8)

set(SUBHOOK_STATIC TRUE)
add_subdirectory("subhook")

list(APPEND libraries    "subhook")
list(APPEND include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/subhook")
list(APPEND compile_defs "SUBHOOK_STATIC")

set(lib_compile_defs ${compile_defs} PARENT_SCOPE)
set(lib_include_dirs ${include_dirs} PARENT_SCOPE)
set(lib_libraries    ${libraries}    PARENT_SCOPE)
