project(sampgdk)
cmake_minimum_required(VERSION 2.8.8)

option(SAMPGDK_STATIC "Build static library instead" OFF)
option(SAMPGDK_BUILD_PLUGINS "Build example plugins" OFF)

set(SAMPGDK_VERSION_MAJOR "3")
set(SAMPGDK_VERSION_MINOR "4")
set(SAMPGDK_VERSION_PATCH "0")
set(SAMPGDK_VERSION_TWEAK "0")
set(SAMPGDK_VERSION_STRING "3.4")

list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

if(NOT (MSVC_IDE AND MSVC_VERSION LESS 1600))
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

include(GroupTargetSources)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  if(WIN32)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT "win32")
  elseif(UNIX)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
  endif()
endif()

enable_language(ASM_NASM)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
  endif()
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
  endif()
endif()

if(SAMPGDK_STATIC)
  add_definitions(-DSAMPGDK_STATIC)
endif()

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
  "${PROJECT_SOURCE_DIR}/scripts"
  "${PROJECT_SOURCE_DIR}/lib/python/ply"
)

macro(sampgdk_add_sources)
  foreach(file ${ARGN})
    if(NOT IS_ABSOLUTE "${file}")
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    else()
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_SOURCES "${file}")
    endif()
  endforeach()
endmacro()

macro(sampgdk_add_headers)
  foreach(file ${ARGN})
    if(NOT IS_ABSOLUTE "${file}")
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    else()
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_HEADERS "${file}")
    endif()
  endforeach()
endmacro()

macro(sampgdk_add_libraries)
  foreach(library ${ARGN})
    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                 SAMPGDK_LIBRARIES "${library}")
  endforeach()
endmacro()

macro(sampgdk_make_output_dir file)
  if(NOT IS_ABSOLUTE file)
    get_filename_component(_file ${file} ABSOLUTE)
  else()
    set(_file ${file})
  endif()

  get_filename_component(_path ${_file} PATH)
  if(_path MATCHES ${PROJECT_BINARY_DIR})
    file(RELATIVE_PATH _path ${CMAKE_CURRENT_BINARY_DIR} ${_path})
  else()  
    file(RELATIVE_PATH _path ${CMAKE_CURRENT_SOURCE_DIR} ${_path})
  endif()

  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${_path}")
endmacro()

macro(sampgdk_add_nasm_source file)
  if(file MATCHES "${CMAKE_CURRENT_SOURCE_DIR}")
    file(RELATIVE_PATH _file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
  else()
    set(_file ${file})
  endif()

  set(_asm_file "${CMAKE_CURRENT_SOURCE_DIR}/${_file}")
  set(_obj_file "${CMAKE_CURRENT_BINARY_DIR}/${_file}.obj")

  sampgdk_add_sources(${_obj_file})

  if(CMAKE_ASM_NASM_COMPILER MATCHES "[yY][aA][sS][mM]")
    set(SAMPGDK_NASM_OPTIONS "-f" "win32" "--prefix=_")
  else()
    set(SAMPGDK_NASM_OPTIONS "-fwin32" "--prefix" "_")
  endif()

  sampgdk_make_output_dir(${_obj_file})

  add_custom_command(OUTPUT ${_obj_file}
    COMMAND "${CMAKE_ASM_NASM_COMPILER}" ${SAMPGDK_NASM_OPTIONS} "-o"
      "${_obj_file}"
      "${_asm_file}"
    MAIN_DEPENDENCY ${_asm_file}
  )
endmacro()

macro(sampgdk_add_api_gen module_name idl_file api_file)
  sampgdk_make_output_dir(${api_file})
  add_custom_command(OUTPUT ${api_file}
    COMMAND ${CMAKE_COMMAND}
      "-DCODEGEN_MODULE_NAME=${module_name}"
      "-DCODEGEN_IDL_FILE=${idl_file}"
      "-DCODEGEN_API_FILE=${api_file}"
      "-P" "${CMAKE_CURRENT_BINARY_DIR}/scripts/codegen.py.cmake"
    DEPENDS ${idl_file} "scripts/codegen.py")
  sampgdk_add_sources(${api_file})
endmacro()

macro(sampgdk_add_header_gen module_name idl_file header_file)
  sampgdk_make_output_dir(${header_file})
  add_custom_command(OUTPUT ${header_file}
    COMMAND ${CMAKE_COMMAND}
      "-DCODEGEN_MODULE_NAME=${module_name}"
      "-DCODEGEN_IDL_FILE=${idl_file}"
      "-DCODEGEN_HEADER_FILE=${header_file}"
      "-P" "${PROJECT_BINARY_DIR}/scripts/codegen.py.cmake"
    DEPENDS ${idl_file} "scripts/codegen.py"
  )
  sampgdk_add_headers(${header_file})
endmacro()

macro(sampgdk_add_source_gen module_name idl_file source_file)
  sampgdk_make_output_dir(${source_file})
  add_custom_command(OUTPUT ${source_file}
    COMMAND ${CMAKE_COMMAND}
      "-DCODEGEN_MODULE_NAME=${module_name}"
      "-DCODEGEN_IDL_FILE=${idl_file}"
      "-DCODEGEN_SOURCE_FILE=${source_file}"
      "-P" "${PROJECT_BINARY_DIR}/scripts/codegen.py.cmake"
    DEPENDS ${idl_file} "scripts/codegen.py")
  sampgdk_add_sources(${source_file})
endmacro()

macro(sampgdk_add_init_module name)
  list(APPEND SAMPGDK_INIT_MODULES ${name})
endmacro()

file(GLOB_RECURSE list_files "init-modules.list")
foreach(file IN LISTS list_files)
  file(STRINGS ${file} modules)
  foreach(module IN LISTS modules)
    sampgdk_add_init_module(${module})
  endforeach()
endforeach()

macro(sampgdk_add_module name)
  sampgdk_add_api_gen(${name}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/${name}.idl"
    "${CMAKE_CURRENT_BINARY_DIR}/src/${name}.api"
  )
  sampgdk_add_source_gen(${name}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/${name}.idl"
    "${CMAKE_CURRENT_BINARY_DIR}/src/${name}-impl.c"
  )
  sampgdk_add_header_gen(${name}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/${name}.idl"
    "${CMAKE_CURRENT_BINARY_DIR}/include/sampgdk/${name}-decl.h"
  )
  sampgdk_add_init_module(${name})
endmacro()

file(GLOB_RECURSE list_files "modules.list")
foreach(file IN LISTS list_files)
  file(STRINGS ${file} modules)
  foreach(module IN LISTS modules)
    sampgdk_add_module(${module})
  endforeach()
endforeach()

add_subdirectory("include")
add_subdirectory("lib")
add_subdirectory("scripts")
add_subdirectory("src")
if(SAMPGDK_BUILD_PLUGINS)
  add_subdirectory("plugins")
endif()

get_property(SAMPGDK_SOURCES DIRECTORY ${PROJECT_SOURCE_DIR}
             PROPERTY SAMPGDK_SOURCES)
get_property(SAMPGDK_HEADERS DIRECTORY ${PROJECT_SOURCE_DIR}
             PROPERTY SAMPGDK_HEADERS)
get_property(SAMPGDK_LIBRARIES DIRECTORY ${PROJECT_SOURCE_DIR}
             PROPERTY SAMPGDK_LIBRARIES)

foreach(file IN LISTS SAMPGDK_SOURCES)
  if(file MATCHES "\\.api")
    list(APPEND SAMPGDK_APIS ${file})
  endif()
  if(WIN32 AND file MATCHES "\\.asm")
    sampgdk_add_nasm_source(${file})
  endif()
endforeach()

if(SAMPGDK_STATIC)
  foreach(lib IN LISTS SAMPGDK_LIBRARIES)
    get_target_property(sources ${lib} SOURCES)
    foreach(file IN LISTS sources)
      sampgdk_add_sources("${${lib}_SOURCE_DIR}/${file}")
    endforeach()
  endforeach()
endif()

# Have to do this one more time because of added .obj files.
get_property(SAMPGDK_SOURCES DIRECTORY ${PROJECT_SOURCE_DIR}
             PROPERTY SAMPGDK_SOURCES)

if(SAMPGDK_DEF_FILE)
  add_custom_command(OUTPUT ${SAMPGDK_DEF_FILE}
    COMMAND "${CMAKE_COMMAND}" 
      "-DDEFGEN_OUTPUT_FILE=${SAMPGDK_DEF_FILE}"
      "-DDEFGEN_SEARCH_DIRS=\"${CMAKE_CURRENT_BINARY_DIR};${CMAKE_CURRENT_SOURCE_DIR}\""
      "-P" "${CMAKE_CURRENT_BINARY_DIR}/scripts/defgen.py.cmake")
endif()

if(SAMPGDK_SYM_FILE)
  add_custom_command(OUTPUT ${SAMPGDK_SYM_FILE}
    COMMAND "${CMAKE_COMMAND}"
      "-DSYMGEN_OUTPUT_FILE=${SAMPGDK_SYM_FILE}"
      "-DSYMGEN_SEARCH_DIRS=\"${CMAKE_CURRENT_BINARY_DIR};${CMAKE_CURRENT_SOURCE_DIR}\""
      "-P" "${CMAKE_CURRENT_BINARY_DIR}/scripts/symgen.py.cmake")
endif()

if(SAMPGDK_STATIC)
  add_library(sampgdk STATIC ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
else()
  add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
endif()

group_target_sources(sampgdk)

set_target_properties(sampgdk PROPERTIES
  VERSION       "${SAMPGDK_VERSION_STRING}"
  SOVERSION     "${SAMPGDK_VERSION_MAJOR}"
  DEBUG_POSTFIX "_d"
  DEFINE_SYMBOL "IN_SAMPGDK"
)

if(WIN32)
  set_property(TARGET sampgdk PROPERTY
               OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}")
  if(MSVC)
    set_property(TARGET sampgdk APPEND PROPERTY
                 COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
  endif()
elseif(UNIX)
  set_property(TARGET sampgdk APPEND_STRING PROPERTY
               LINK_FLAGS " -Wl,--no-undefined")
  set_property(TARGET sampgdk APPEND_STRING PROPERTY
               LINK_FLAGS " -Wl,--retain-symbols-file=${SAMPGDK_SYM_FILE}")
endif()

if(NOT SAMPGDK_STATIC)
  target_link_libraries(sampgdk ${SAMPGDK_LIBRARIES})
  if(UNIX)
    target_link_libraries(sampgdk ${CMAKE_DL_LIBS} "rt")
  endif()
endif()

foreach(header IN LISTS SAMPGDK_HEADERS)
  get_filename_component(path ${header} PATH)
  get_filename_component(abs_path ${path} ABSOLUTE)

  if(header MATCHES ${CMAKE_CURRENT_BINARY_DIR})
    file(RELATIVE_PATH dir ${CMAKE_CURRENT_BINARY_DIR} ${abs_path})
  else()
    file(RELATIVE_PATH dir ${CMAKE_CURRENT_SOURCE_DIR} ${abs_path})
  endif()

  install(FILES ${header} DESTINATION ${dir} COMPONENT "dev")
endforeach()

install(TARGETS sampgdk
  RUNTIME DESTINATION "bin" COMPONENT "bin"
  ARCHIVE DESTINATION "lib" COMPONENT "dev"
  LIBRARY DESTINATION "lib" COMPONENT "bin"
)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${SAMPGDK_VERSION_STRING})
set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})

if(WIN32)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY
      "${CPACK_PACKAGE_NAME} ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
endif()

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_COMPONENT_BIN_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_BIN_DESCRIPTION "Runtime library needed to run plugins")
set(CPACK_COMPONENT_BIN_INSTALL_TYPES "Full" "Minimal")
set(CPACK_COMPONENT_DEV_DISPLAY_NAME "Development files")
set(CPACK_COMPONENT_DEV_DESCRIPTION "Import library and C/C++ headers")
set(CPACK_COMPONENT_DEV_INSTALL_TYPES "Full")
set(CPACK_COMPONENT_DEV_DEPENDS "bin")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)
