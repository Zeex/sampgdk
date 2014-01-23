project(sampgdk)

cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0022 NEW)

option(SAMPGDK_STATIC "Build static library instead" OFF)
option(SAMPGDK_BUILD_PLUGINS "Build example plugins" OFF)

set(SAMPGDK_VERSION_MAJOR 4)
set(SAMPGDK_VERSION_MINOR 0)
set(SAMPGDK_VERSION_PATCH 0)
set(SAMPGDK_VERSION_STRING 4.0-pre)

set(SAMPGDK_VERSION ${SAMPGDK_VERSION_MAJOR})
set(SAMPGDK_VERSION ${SAMPGDK_VERSION}.${SAMPGDK_VERSION_MINOR})
set(SAMPGDK_VERSION ${SAMPGDK_VERSION}.${SAMPGDK_VERSION_PATCH})

math(EXPR SAMPGDK_VERSION_ID "${SAMPGDK_VERSION_MAJOR} << 24 |\
                              ${SAMPGDK_VERSION_MINOR} << 16 |\
                              ${SAMPGDK_VERSION_PATCH} << 8")

configure_file(Doxyfile.in Doxyfile @ONLY)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
list(APPEND CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib)
list(APPEND CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/lib)

if(NOT (MSVC_IDE AND MSVC_VERSION LESS 1600))
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

find_package(SDK REQUIRED)
find_package(PythonInterp 2.7 REQUIRED)

include_directories(${SDK_INCLUDE_DIR})
include_directories(${SDK_INCLUDE_DIR}/amx)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/src)

macro(smapgdk_add_subproject name)
  add_subdirectory(${name})
  file(RELATIVE_PATH folder ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
  set_property(TARGET ${name} PROPERTY FOLDER ${folder})
endmacro()

macro(sampgdk_add_sources)
  foreach(file ${ARGN})
    if(NOT IS_ABSOLUTE ${file})
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${file})
    else()
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_SOURCES ${file})
    endif()
  endforeach()
endmacro()

macro(sampgdk_get_sources var)
  get_property(${var} DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY SAMPGDK_SOURCES)
endmacro()

macro(sampgdk_add_headers)
  foreach(file ${ARGN})
    if(NOT IS_ABSOLUTE ${file})
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
    else()
      set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                   SAMPGDK_HEADERS ${file})
    endif()
  endforeach()
endmacro()

macro(sampgdk_get_headers var)
  get_property(${var} DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY SAMPGDK_HEADERS)
endmacro()

macro(sampgdk_add_libraries)
  foreach(library ${ARGN})
    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
                 SAMPGDK_LIBRARIES ${library})
  endforeach()
endmacro()

macro(sampgdk_get_libraries var)
  get_property(${var} DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY SAMPGDK_LIBRARIES)
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

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${_path})
endmacro()

macro(sampgdk_add_api_gen module_name idl_file api_file)
  sampgdk_make_output_dir(${api_file})
  add_custom_command(OUTPUT ${api_file}
    COMMAND ${CMAKE_COMMAND}
      -DCODEGEN_MODULE_NAME=${module_name}
      -DCODEGEN_IDL_FILE=${idl_file}
      -DCODEGEN_API_FILE=${api_file}
      -P ${CMAKE_CURRENT_BINARY_DIR}/scripts/codegen.cmake
    DEPENDS ${idl_file} scripts/codegen.py)
  sampgdk_add_sources(${api_file})
endmacro()

macro(sampgdk_add_source_gen module_name idl_file source_file)
  sampgdk_make_output_dir(${source_file})
  add_custom_command(OUTPUT ${source_file}
    COMMAND ${CMAKE_COMMAND}
      -DCODEGEN_MODULE_NAME=${module_name}
      -DCODEGEN_IDL_FILE=${idl_file}
      -DCODEGEN_SOURCE_FILE=${source_file}
      -P ${PROJECT_BINARY_DIR}/scripts/codegen.cmake
    DEPENDS ${idl_file} ${PROJECT_SOURCE_DIR}/scripts/codegen.py)
  sampgdk_add_sources(${source_file})
endmacro()

macro(sampgdk_add_header_gen module_name idl_file header_file)
  sampgdk_make_output_dir(${header_file})
  add_custom_command(OUTPUT ${header_file}
    COMMAND ${CMAKE_COMMAND}
      -DCODEGEN_MODULE_NAME=${module_name}
      -DCODEGEN_IDL_FILE=${idl_file}
      -DCODEGEN_HEADER_FILE=${header_file}
      -P ${PROJECT_BINARY_DIR}/scripts/codegen.cmake
    DEPENDS ${idl_file} ${PROJECT_SOURCE_DIR}/scripts/codegen.py)
  sampgdk_add_headers(${header_file})
endmacro()

macro(sampgdk_add_init_gen target list_file source_file)
  sampgdk_make_output_dir(${source_file})
  add_custom_target(${target} 
    COMMAND ${CMAKE_COMMAND}
      -DINITGEN_LIST_FILE=${list_file}
      -DINITGEN_SOURCE_FILE=${source_file}
      -P ${PROJECT_BINARY_DIR}/scripts/initgen.cmake
    DEPENDS ${list_file} ${PROJECT_SOURCE_DIR}/scripts/initgen.py)
  sampgdk_add_sources(${source_file})
endmacro()

set(PYTHONPATH
  ${PROJECT_SOURCE_DIR}/scripts
  ${PROJECT_SOURCE_DIR}/lib/python/ply
  ${PROJECT_SOURCE_DIR}/lib/python/cidl
)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(scripts)
add_subdirectory(src)
if(SAMPGDK_BUILD_PLUGINS)
  add_subdirectory(plugins)
endif()

sampgdk_get_sources(SAMPGDK_SOURCES)

foreach(file IN LISTS SAMPGDK_SOURCES)
  get_filename_component(extension ${file} EXT)

  if(extension STREQUAL ".idl")
    file(RELATIVE_PATH path ${PROJECT_SOURCE_DIR}/src ${file})

    get_filename_component(dir ${path} PATH)
    get_filename_component(name ${file} NAME_WE)

    sampgdk_add_api_gen(${name} ${file}
      ${PROJECT_BINARY_DIR}/src/${dir}/${name}.api)
    sampgdk_add_source_gen(${name} ${file}
      ${PROJECT_BINARY_DIR}/src/${dir}/${name}-impl.h)
    sampgdk_add_header_gen(${name} ${file}
      ${PROJECT_BINARY_DIR}/include/sampgdk/${dir}/${name}-decl.h)

    list(APPEND SAMPGDK_IDLS ${file})
  endif()
endforeach()

sampgdk_get_sources(SAMPGDK_SOURCES)

foreach(file IN LISTS SAMPGDK_SOURCES)
  get_filename_component(extension ${file} EXT)
  if(extension STREQUAL ".api")
    list(APPEND SAMPGDK_APIS ${file})
  endif()
endforeach()

if(SAMPGDK_DEF_FILE)
  add_custom_command(OUTPUT ${SAMPGDK_DEF_FILE}
    COMMAND ${CMAKE_COMMAND}
      -DDEFGEN_OUTPUT_FILE=${SAMPGDK_DEF_FILE}
      -DDEFGEN_SEARCH_DIRS="\"${PROJECT_BINARY_DIR};${PROJECT_SOURCE_DIR}\""
      -P ${PROJECT_BINARY_DIR}/scripts/defgen.cmake
    DEPENDS ${SAMPGDK_APIS})
endif()

if(SAMPGDK_SYM_FILE)
  add_custom_command(OUTPUT ${SAMPGDK_SYM_FILE}
    COMMAND ${CMAKE_COMMAND}
      -DSYMGEN_OUTPUT_FILE=${SAMPGDK_SYM_FILE}
      -DSYMGEN_SEARCH_DIRS="\"${PROJECT_BINARY_DIR};${PROJECT_SOURCE_DIR}\""
      -P ${PROJECT_BINARY_DIR}/scripts/symgen.cmake
    DEPENDS ${SAMPGDK_APIS})
endif()

sampgdk_get_sources(SAMPGDK_SOURCES)
sampgdk_get_headers(SAMPGDK_HEADERS)

list(REMOVE_ITEM SAMPGDK_SOURCES ${SAMPGDK_IDLS})

if(SAMPGDK_STATIC)
  add_library(sampgdk STATIC ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
else()
  add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
endif()

get_target_property(SAMPGDK_OUTPUT_NAME sampgdk OUTPUT_NAME)

if(NOT SAMPGDK_OUTPUT_NAME)
  set(SAMPGDK_OUTPUT_NAME sampgdk)
endif()

if(WIN32)
  set(SAMPGDK_OUTPUT_NAME ${SAMPGDK_OUTPUT_NAME}${SAMPGDK_VERSION_MAJOR})
  if(SAMPGDK_STATIC)
    set(SAMPGDK_OUTPUT_NAME ${SAMPGDK_OUTPUT_NAME}s)
  endif()
endif()

set_target_properties(sampgdk PROPERTIES
  VERSION       ${SAMPGDK_VERSION}
  SOVERSION     ${SAMPGDK_VERSION_MAJOR}
  DEFINE_SYMBOL IN_SAMPGDK
  OUTPUT_NAME   ${SAMPGDK_OUTPUT_NAME}
  DEBUG_POSTFIX d
)

if(SAMPGDK_STATIC)
  target_compile_definitions(sampgdk PUBLIC SAMPGDK_STATIC)
endif()

if(MSVC)
  target_compile_definitions(sampgdk PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(UNIX)
  target_compile_options(sampgdk PRIVATE -fvisibility=hidden)
  if(NOT SAMPGDK_STATIC)
    target_link_libraries(sampgdk PRIVATE
                  -Wl,--no-undefined,--retain-symbols-file=${SAMPGDK_SYM_FILE})
  endif()
endif()

if(UNIX)
  sampgdk_add_libraries(${CMAKE_DL_LIBS})
  find_library(RT_LIB rt)
  if(RT_LIB)
    sampgdk_add_libraries(${RT_LIB})
  endif()
endif()

sampgdk_get_libraries(SAMPGDK_LIBRARIES)

if(SAMPGDK_STATIC)
  target_link_libraries(sampgdk INTERFACE ${SAMPGDK_LIBRARIES})
else()
  target_link_libraries(sampgdk PRIVATE ${SAMPGDK_LIBRARIES})
endif()

add_dependencies(sampgdk sampgdk_init)

foreach(header IN LISTS SAMPGDK_HEADERS)
  get_filename_component(path ${header} PATH)
  get_filename_component(abs_path ${path} ABSOLUTE)

  if(header MATCHES ${PROJECT_BINARY_DIR})
    file(RELATIVE_PATH dir ${PROJECT_BINARY_DIR} ${abs_path})
  else()
    file(RELATIVE_PATH dir ${PROJECT_SOURCE_DIR} ${abs_path})
  endif()

  install(FILES ${header} DESTINATION ${dir} COMPONENT dev)
endforeach()

install(TARGETS sampgdk RUNTIME DESTINATION bin COMPONENT bin
                        ARCHIVE DESTINATION lib COMPONENT dev
                        LIBRARY DESTINATION lib COMPONENT bin)

if(WIN32)
  set(CPACK_PACKAGE_FILE_NAME sampgdk-${SAMPGDK_VERSION}-win32)
  set(CPACK_GENERATOR ZIP)
elseif(UNIX)
  set(CPACK_PACKAGE_FILE_NAME sampgdk-${SAMPGDK_VERSION}-linux)
  set(CPACK_GENERATOR TGZ)
endif()

if(SAMPGDK_STATIC)
  set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}-static)
endif()

include(CPack)
