cmake_minimum_required(VERSION 2.8.8)
project(sampgdk)

option(SAMPGDK_INSTALL       "Generate install target" OFF)
option(SAMPGDK_BUILD_PLUGINS "Generate package target" OFF)

set(SAMPGDK_VERSION_MAJOR "3")
set(SAMPGDK_VERSION_MINOR "2")
set(SAMPGDK_VERSION_PATCH "0")
set(SAMPGDK_VERSION_TWEAK "0")
set(SAMPGDK_VERSION_STRING "3.2")

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake"
	"${CMAKE_SOURCE_DIR}/cmake/Modules"
)

include(AddTargetCompileFlags)
include(AddTargetDefinitions)
include(AddTargetIncludeDirs)
include(AddTargetLinkFlags)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	if(WIN32)
		set(CMAKE_ASM_NASM_OBJECT_FORMAT "win32")
	elseif(UNIX)
		set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
	endif()
endif()
enable_language(ASM_NASM)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
	set(CMAKE_COMPILER_IS_GNUCC TRUE)
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	set(CMAKE_COMPILER_IS_GNUCXX TRUE)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	if(CMAKE_COMPILER_IS_GNUCC)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
	endif()
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
	endif()
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}/src") # FIXME: should be done from src

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
	"${CMAKE_SOURCE_DIR}/cidl"
	"${CMAKE_SOURCE_DIR}/python/ply"
)

add_subdirectory("include")
add_subdirectory("lib")
add_subdirectory("src")
if(SAMPGDK_BUILD_PLUGINS)
	add_subdirectory("plugins")
endif()

list(APPEND SAMPGDK_HEADERS
	"include/sampgdk/sdk/amx/amx.h"
	"include/sampgdk/sdk/amx/getch.h"
	"include/sampgdk/sdk/amx/sclinux.h"
	"include/sampgdk/sdk/plugincommon.h"
	"include/sampgdk/a_objects.h"
	"include/sampgdk/a_players.h"
	"include/sampgdk/a_samp.h"
	"include/sampgdk/a_vehicles.h"
	"include/sampgdk/amx.h"
	"include/sampgdk/bool.h"
	"include/sampgdk/core.h"
	"include/sampgdk/export.h"
	"include/sampgdk/platform.h"
	"include/sampgdk/plugin.h"
	"include/sampgdk/plugincommon.h"
	"${CMAKE_BINARY_DIR}/include/sampgdk/version.h"
)

list(APPEND SAMPGDK_SOURCES
	"src/sdk/amxplugin.c"
	"src/a_objects.c"
	"src/a_players.c"
	"src/a_samp.c"
	"src/a_vehicles.c"
	"src/amx-stack.c"
	"src/amx-stack.h"
	"src/array.c"
	"src/array.h"
	"src/call.asm"
	"src/call.h"
	"src/callback.c"
	"src/callback.h"
	"src/core.c"
	"src/fakeamx.c"
	"src/fakeamx.h"
	"src/hooks.c"
	"src/hooks.h"
	"src/likely.h"
	"src/log.c"
	"src/log.h"
	"src/logprintf.c"
	"src/logprintf.h"
	"src/native.c"
	"src/native.h"
	"src/plugin.c"
	"src/plugin.h"
	"src/server-cfg.c"
	"src/server-cfg.h"
	"src/timer.c"
	"src/timer.h"
	"src/version.c"
)

if(WIN32)
	list(APPEND SAMPGDK_SOURCES "${CMAKE_BINARY_DIR}/src/call.asm.obj")
	if("${CMAKE_ASM_NASM_COMPILER}" MATCHES "[yY][aA][sS][mM]")
		set(options "-f" "win32" "--prefix=_")
	else()
		set(options "-fwin32" "--prefix" "_")
	endif()
	add_custom_command(
		OUTPUT  "${CMAKE_BINARY_DIR}/src/call.asm.obj"
		COMMAND "${CMAKE_ASM_NASM_COMPILER}" ${options} "-o"
			"${CMAKE_BINARY_DIR}/src/call.asm.obj"
			"${CMAKE_SOURCE_DIR}/src/call.asm"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/src/call.asm"
	)
endif()

list(APPEND SAMPGDK_APIS
	"src/sdk/amxplugin.api"
	"src/core.api"
	"src/version.api"
)

if(WIN32)
	list(APPEND SAMPGDK_SOURCES
		"src/plugin-win32.c"
		"src/sampgdk.def"
		"src/sampgdk.rc"
		"src/timer-win32.c"
	)
elseif(UNIX)
	list(APPEND SAMPGDK_SOURCES
		"src/plugin-linux.c"
		"src/sampgdk.sym"
		"src/timer-linux.c"
	)
else()
	message(FATAL_ERROR "Unsupported operating system")
endif()

macro(directory_source_group path)
	string(REGEX REPLACE "/" "\\\\" win_path ${path})
	source_group(${win_path} REGULAR_EXPRESSION "${path}/[^/\\]+\\..*")
endmacro()

directory_source_group("src")
directory_source_group("src/generated")
directory_source_group("src/sdk")
directory_source_group("include/sampgdk")
directory_source_group("include/sampgdk/generated")
directory_source_group("include/sampgdk/sdk")
directory_source_group("include/sampgdk/sdk/amx")

function(add_header_gen idl_file header_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(header_file ${header_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${header_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_HDR_FILE=${header_file}"
			"-P" "${CMAKE_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
	)
endfunction()

add_header_gen("src/a_objects.idl"  "${CMAKE_BINARY_DIR}/include/sampgdk/a_objects-decl.h")
add_header_gen("src/a_players.idl"  "${CMAKE_BINARY_DIR}/include/sampgdk/a_players-decl.h")
add_header_gen("src/a_samp.idl"     "${CMAKE_BINARY_DIR}/include/sampgdk/a_samp-decl.h")
add_header_gen("src/a_vehicles.idl" "${CMAKE_BINARY_DIR}/include/sampgdk/a_vehicles-decl.h")

list(APPEND SAMPGDK_GENERATED_HEADERS
	"${CMAKE_BINARY_DIR}/include/sampgdk/a_objects-decl.h"
	"${CMAKE_BINARY_DIR}/include/sampgdk/a_players-decl.h"
	"${CMAKE_BINARY_DIR}/include/sampgdk/a_samp-decl.h"
	"${CMAKE_BINARY_DIR}/include/sampgdk/a_vehicles-decl.h"
)

list(APPEND SAMPGDK_HEADERS ${SAMPGDK_GENERATED_HEADERS})

function(add_source_gen idl_file source_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(source_file ${source_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${source_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_SRC_FILE=${source_file}"
			"-P" "${CMAKE_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
	)
endfunction()

add_source_gen("src/a_objects.idl"  "${CMAKE_BINARY_DIR}/src/a_objects-impl.c")
add_source_gen("src/a_players.idl"  "${CMAKE_BINARY_DIR}/src/a_players-impl.c")
add_source_gen("src/a_samp.idl"     "${CMAKE_BINARY_DIR}/src/a_samp-impl.c")
add_source_gen("src/a_vehicles.idl" "${CMAKE_BINARY_DIR}/src/a_vehicles-impl.c")

list(APPEND SAMPGDK_GENERATED_SOURCES
	"${CMAKE_BINARY_DIR}/src/a_objects-impl.c"
	"${CMAKE_BINARY_DIR}/src/a_players-impl.c"
	"${CMAKE_BINARY_DIR}/src/a_samp-impl.c"
	"${CMAKE_BINARY_DIR}/src/a_vehicles-impl.c"
)

set_source_files_properties(${SAMPGDK_GENERATED_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
list(APPEND SAMPGDK_SOURCES ${SAMPGDK_GENERATED_SOURCES})

function(add_api_gen idl_file api_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(api_file ${api_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${api_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_API_FILE=${api_file}"
			"-P" "${CMAKE_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
	)
endfunction()

add_api_gen("src/a_objects.idl"  "${CMAKE_BINARY_DIR}/src/a_objects.api")
add_api_gen("src/a_players.idl"  "${CMAKE_BINARY_DIR}/src/a_players.api")
add_api_gen("src/a_samp.idl"     "${CMAKE_BINARY_DIR}/src/a_samp.api")
add_api_gen("src/a_vehicles.idl" "${CMAKE_BINARY_DIR}/src/a_vehicles.api")

list(APPEND SAMPGDK_APIS
	"${CMAKE_BINARY_DIR}/src/a_objects.api"
	"${CMAKE_BINARY_DIR}/src/a_players.api"
	"${CMAKE_BINARY_DIR}/src/a_samp.api"
	"${CMAKE_BINARY_DIR}/src/a_vehicles.api"
)

list(APPEND SAMPGDK_SOURCES ${SAMPGDK_APIS})

if(WIN32)
	add_custom_command(
		OUTPUT  "${CMAKE_BINARY_DIR}/src/sampgdk.def"
		COMMAND "${CMAKE_COMMAND}" "-P" "${CMAKE_BINARY_DIR}/src/sampgdk.def.cmake"
		DEPENDS ${SAMPGDK_APIS}
	)
elseif(UNIX)
	add_custom_command(
		OUTPUT  "${CMAKE_BINARY_DIR}/src/sampgdk.sym"
		COMMAND "${CMAKE_COMMAND}" "-P" "${CMAKE_BINARY_DIR}/src/sampgdk.sym.cmake"
		DEPENDS ${SAMPGDK_APIS}
	)
endif()

add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})

set_target_properties(sampgdk PROPERTIES
	DEBUG_POSTFIX "_d"
	DEFINE_SYMBOL "IN_SAMPGDK"
)

if(WIN32)
	set_target_properties(sampgdk PROPERTIES
		OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}"
	)
elseif(UNIX)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   "${SAMPGDK_VERSION_STRING}"
		SOVERSION "${SAMPGDK_VERSION_MAJOR}"
	)
endif()

if(MSVC)
	add_target_definitions(sampgdk "_CRT_SECURE_NO_WARNINGS")
endif()

if(UNIX AND NOT WIN32)
	add_target_link_flags(sampgdk
		"-Wl,--no-undefined"
		"-Wl,--retain-symbols-file=${CMAKE_BINARY_DIR}/src/sampgdk.sym"
	)
	target_link_libraries(sampgdk "dl" "rt")
endif()

target_link_libraries(sampgdk "subhook")

if(SAMPGDK_INSTALL)
	install(
		DIRECTORY "include" "${CMAKE_BINARY_DIR}/include"
		DESTINATION "."
		COMPONENT "dev" FILES_MATCHING PATTERN "*.h"
	)
	install(
		TARGETS sampgdk
		RUNTIME DESTINATION "bin" COMPONENT "bin"
		ARCHIVE DESTINATION "lib" COMPONENT "dev"
		LIBRARY DESTINATION "lib" COMPONENT "bin"
	)
	set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
	set(CPACK_PACKAGE_CONTACT "CPack")
	set(CPACK_PACKAGE_VERSION ${SAMPGDK_VERSION_STRING})
	set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
	set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
	set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})
	if(WIN32)
		set(CPACK_PACKAGE_INSTALL_DIRECTORY "sampgdk ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
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
endif()
