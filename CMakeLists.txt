cmake_minimum_required(VERSION 2.8.8)
project(sampgdk)

option(SAMPGDK_INSTALL "Install library and headers" OFF)
option(SAMPGDK_BUILD_PLUGINS "Build example plugins" OFF)

set(SAMPGDK_VERSION_MAJOR "3")
set(SAMPGDK_VERSION_MINOR "1")
set(SAMPGDK_VERSION_PATCH "3")
set(SAMPGDK_VERSION_TWEAK "0")
set(SAMPGDK_VERSION_STRING "3.1.3")

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake"
	"${CMAKE_SOURCE_DIR}/cmake/Modules"
)

include(AddTargetCompileFlags)
include(AddTargetDefinitions)
include(AddTargetIncludeDirs)
include(AddTargetLinkFlags)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
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

include_directories("include")
include_directories("include/sampgdk")

add_subdirectory("lib")
if(SAMPGDK_BUILD_PLUGINS)
	add_subdirectory("plugins")
endif()

list(APPEND SAMPGDK_HEADER_FILES
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
	"include/sampgdk/version.h"
)

list(APPEND SAMPGDK_SOURCE_FILES
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

list(APPEND SAMPGDK_API_FILES
	"src/sdk/amxplugin.api"
	"src/core.api"
	"src/version.api"
)

if(WIN32)
	list(APPEND SAMPGDK_SOURCE_FILES
		"src/plugin-win32.c"
		"src/sampgdk.def"
		"src/sampgdk.rc"
		"src/timer-win32.c"
	)
elseif(UNIX)
	list(APPEND SAMPGDK_SOURCE_FILES
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

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
	"${CMAKE_SOURCE_DIR}/cidl"
	"${CMAKE_SOURCE_DIR}/python/ply"
)

function(add_header_gen idl_file header_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(header_file ${header_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${header_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DPYTHON=${PYTHON_EXECUTABLE}"
				"-DPYTHONPATH=\"${PYTHONPATH}\""
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_HEADER_FILE=${header_file}"
			"-P" "${CMAKE_SOURCE_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endfunction()

add_header_gen("src/a_objects.idl"  "include/sampgdk/generated/a_objects.h")
add_header_gen("src/a_players.idl"  "include/sampgdk/generated/a_players.h")
add_header_gen("src/a_samp.idl"     "include/sampgdk/generated/a_samp.h")
add_header_gen("src/a_vehicles.idl" "include/sampgdk/generated/a_vehicles.h")

list(APPEND SAMPGDK_HEADER_FILES
	"include/sampgdk/generated/a_objects.h"
	"include/sampgdk/generated/a_players.h"
	"include/sampgdk/generated/a_samp.h"
	"include/sampgdk/generated/a_vehicles.h"
)

function(add_source_gen idl_file source_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(source_file ${source_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${source_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DPYTHON=${PYTHON_EXECUTABLE}"
				"-DPYTHONPATH=\"${PYTHONPATH}\""
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_SOURCE_FILE=${source_file}"
			"-P" "${CMAKE_SOURCE_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endfunction()

add_source_gen("src/a_objects.idl"  "src/generated/a_objects.c")
add_source_gen("src/a_players.idl"  "src/generated/a_players.c")
add_source_gen("src/a_samp.idl"     "src/generated/a_samp.c")
add_source_gen("src/a_vehicles.idl" "src/generated/a_vehicles.c")

list(APPEND SAMPGDK_GENERATED_SOURCES
	"src/generated/a_objects.c"
	"src/generated/a_players.c"
	"src/generated/a_samp.c"
	"src/generated/a_vehicles.c"
)

set_source_files_properties(${SAMPGDK_GENERATED_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
list(APPEND SAMPGDK_SOURCE_FILES ${SAMPGDK_GENERATED_SOURCES})

function(add_api_gen idl_file api_file)
	get_filename_component(idl_file ${idl_file} ABSOLUTE)
	get_filename_component(api_file ${api_file} ABSOLUTE)
	add_custom_command(
		OUTPUT
			${api_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DPYTHON=${PYTHON_EXECUTABLE}"
				"-DPYTHONPATH=\"${PYTHONPATH}\""
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_API_FILE=${api_file}"
			"-P" "${CMAKE_SOURCE_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file} "src/codegen.py"
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endfunction()

add_api_gen("src/a_objects.idl"  "src/generated/a_objects.api")
add_api_gen("src/a_players.idl"  "src/generated/a_players.api")
add_api_gen("src/a_samp.idl"     "src/generated/a_samp.api")
add_api_gen("src/a_vehicles.idl" "src/generated/a_vehicles.api")

list(APPEND SAMPGDK_API_FILES
	"src/generated/a_objects.api"
	"src/generated/a_players.api"
	"src/generated/a_samp.api"
	"src/generated/a_vehicles.api"
)

list(APPEND SAMPGDK_SOURCE_FILES ${SAMPGDK_API_FILES})

if(WIN32)
	add_custom_command(
		OUTPUT
			"${CMAKE_SOURCE_DIR}/src/sampgdk.def"
		COMMAND
			${CMAKE_COMMAND}
			"-P" "${CMAKE_SOURCE_DIR}/src/sampgdk.def.cmake"
		DEPENDS
			${SAMPGDK_API_FILES}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
elseif(UNIX)
	add_custom_command(
		OUTPUT
			"${CMAKE_SOURCE_DIR}/src/sampgdk.sym"
		COMMAND
			${CMAKE_COMMAND}
			"-P" "${CMAKE_SOURCE_DIR}/src/sampgdk.sym.cmake"
		DEPENDS
			${SAMPGDK_API_FILES}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endif()

add_custom_command(
	OUTPUT
		"${CMAKE_SOURCE_DIR}/include/sampgdk/version.h"
	COMMAND
		${CMAKE_COMMAND}
			"-DVERSION_MAJOR=${SAMPGDK_VERSION_MAJOR}"
			"-DVERSION_MINOR=${SAMPGDK_VERSION_MINOR}"
			"-DVERSION_PATCH=${SAMPGDK_VERSION_PATCH}"
			"-DVERSION_TWEAK=${SAMPGDK_VERSION_TWEAK}"
			"-DVERSION_STRING=${SAMPGDK_VERSION_STRING}"
		"-P" "${CMAKE_SOURCE_DIR}/include/sampgdk/version.h.cmake"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/include/sampgdk/version.h.in"
	WORKING_DIRECTORY
		"${CMAKE_SOURCE_DIR}/include/sampgdk"
)

add_library(sampgdk SHARED ${SAMPGDK_HEADER_FILES} ${SAMPGDK_SOURCE_FILES})

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
	if(CMAKE_COMPILER_IS_GNUCC)
		add_target_link_flags(sampgdk
			"-Wl,--no-undefined"
			"-Wl,--retain-symbols-file=${CMAKE_SOURCE_DIR}/src/sampgdk.sym"
		)
		target_link_libraries(sampgdk "dl" "rt")
	endif()
endif()

target_link_libraries(sampgdk "subhook")

if(SAMPGDK_INSTALL)
	install(DIRECTORY "include" DESTINATION "." COMPONENT "dev" FILES_MATCHING PATTERN "*.h")
	install(TARGETS sampgdk RUNTIME DESTINATION "bin" COMPONENT "bin"
	                        ARCHIVE DESTINATION "lib" COMPONENT "dev"
	                        LIBRARY DESTINATION "lib" COMPONENT "bin")
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
