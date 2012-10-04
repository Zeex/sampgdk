cmake_minimum_required(VERSION 2.8.8)

project(sampgdk)

set(SAMPGDK_VERSION_MAJOR "3")
set(SAMPGDK_VERSION_MINOR "1")
set(SAMPGDK_VERSION_PATCH "2")
set(SAMPGDK_VERSION_TWEAK "0")
set(SAMPGDK_VERSION_STRING "3.1.2")

if(${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Intel")
	set(CMAKE_COMPILER_IS_GNUCC TRUE)
endif()
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
	set(CMAKE_COMPILER_IS_GNUCXX TRUE)
endif()

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/cmake/Modules"
)

include(AddTargetCompileFlags)
include(AddTargetDefinitions)
include(AddTargetIncludeDirs)
include(AddTargetLinkFlags)
include(AmxConfig)

add_subdirectory("lib")

include_directories("include")
include_directories("include/sampgdk")

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
	"include/sampgdk/static-assert.h"
	"include/sampgdk/version.h"
)

list(APPEND SAMPGDK_SOURCE_FILES
	"src/sdk/amxplugin.c"
	"src/amx-stack.c"
	"src/amx-stack.h"
	"src/array.c"
	"src/array.h"
	"src/asm.h"
	"src/callback.c"
	"src/callback.h"
	"src/fakeamx.c"
	"src/fakeamx.h"
	"src/likely.h"
	"src/log.c"
	"src/log.h"
	"src/logprintf-impl.c"
	"src/logprintf-impl.h"
	"src/native.c"
	"src/native.h"
	"src/plugin.c"
	"src/plugin.h"
	"src/server-cfg.c"
	"src/server-cfg.h"
	"src/server-log.c"
	"src/server-log.h"
	"src/timer.c"
	"src/timer.h"
	"src/a_objects.c"
	"src/a_players.c"
	"src/a_samp.c"
	"src/a_vehicles.c"
	"src/core.c"
	"src/version.c"
)

list(APPEND SAMPGDK_EXPORTS_FILES
	"src/core.exports"
	"src/version.exports"
)

if(MSVC)
	list(APPEND SAMPGDK_SOURCE_FILES
		"src/asm-msvc.c"
	)
elseif(CMAKE_COMPILER_IS_GNUCC)
	list(APPEND SAMPGDK_SOURCE_FILES
		"src/asm-gcc.c"
	)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

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

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
	"${CMAKE_SOURCE_DIR}/cidl"
	"${CMAKE_SOURCE_DIR}/python/ply-3.4.zip"
)

file(MAKE_DIRECTORY "include/sampgdk/generated")

macro(add_header_gen idl_file header_file)
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
			${idl_file}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endmacro()

add_header_gen("${CMAKE_SOURCE_DIR}/src/a_objects.idl" "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_objects.h")
add_header_gen("${CMAKE_SOURCE_DIR}/src/a_players.idl" "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_players.h")
add_header_gen("${CMAKE_SOURCE_DIR}/src/a_samp.idl" "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_samp.h")
add_header_gen("${CMAKE_SOURCE_DIR}/src/a_vehicles.idl" "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_vehicles.h")

list(APPEND SAMPGDK_HEADER_FILES
	"include/sampgdk/generated/a_objects.h"
	"include/sampgdk/generated/a_players.h"
	"include/sampgdk/generated/a_samp.h"
	"include/sampgdk/generated/a_vehicles.h"
)

file(MAKE_DIRECTORY "src/generated")

macro(add_source_gen idl_file source_file)
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
			${idl_file}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endmacro()

add_source_gen("${CMAKE_SOURCE_DIR}/src/a_objects.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_objects.c")
add_source_gen("${CMAKE_SOURCE_DIR}/src/a_players.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_players.c")
add_source_gen("${CMAKE_SOURCE_DIR}/src/a_samp.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_samp.c")
add_source_gen("${CMAKE_SOURCE_DIR}/src/a_vehicles.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.c")

list(APPEND SAMPGDK_GENERATED_SOURCES
	"src/generated/a_objects.c"
	"src/generated/a_players.c"
	"src/generated/a_samp.c"
	"src/generated/a_vehicles.c"
)

set_source_files_properties(${SAMPGDK_GENERATED_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
list(APPEND SAMPGDK_SOURCE_FILES ${SAMPGDK_GENERATED_SOURCES})

file(MAKE_DIRECTORY "src/generated")

macro(add_exports_gen idl_file exports_file)
	add_custom_command(
		OUTPUT
			${exports_file}
		COMMAND
			${CMAKE_COMMAND}
				"-DPYTHON=${PYTHON_EXECUTABLE}"
				"-DPYTHONPATH=\"${PYTHONPATH}\""
				"-DCODEGEN_IDL_FILE=${idl_file}"
				"-DCODEGEN_EXPORTS_FILE=${exports_file}"
			"-P" "${CMAKE_SOURCE_DIR}/src/codegen.py.cmake"
		DEPENDS
			${idl_file}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endmacro()

add_exports_gen("${CMAKE_SOURCE_DIR}/src/a_objects.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_objects.exports")
add_exports_gen("${CMAKE_SOURCE_DIR}/src/a_players.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_players.exports")
add_exports_gen("${CMAKE_SOURCE_DIR}/src/a_samp.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_samp.exports")
add_exports_gen("${CMAKE_SOURCE_DIR}/src/a_vehicles.idl" "${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.exports")

list(APPEND SAMPGDK_EXPORTS_FILES
	"src/generated/a_objects.exports"
	"src/generated/a_players.exports"
	"src/generated/a_samp.exports"
	"src/generated/a_vehicles.exports"
)

list(APPEND SAMPGDK_SOURCE_FILES ${SAMPGDK_EXPORTS_FILES})

if(WIN32)
	add_custom_command(
		OUTPUT
			"${CMAKE_SOURCE_DIR}/src/sampgdk.def"
		COMMAND
			${CMAKE_COMMAND}
			"-P" "${CMAKE_SOURCE_DIR}/src/sampgdk.def.cmake"
		DEPENDS
			${SAMPGDK_EXPORTS_FILES}
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
			${SAMPGDK_EXPORTS_FILES}
		WORKING_DIRECTORY
			"${CMAKE_SOURCE_DIR}/src"
	)
endif()

macro(directory_source_group path)
	string(REGEX REPLACE "/" "\\\\" win_path ${path})
	source_group(${win_path} REGULAR_EXPRESSION "${path}/[^/\\]+\\..*")
endmacro()

directory_source_group("src")
directory_source_group("src/generated")
directory_source_group("src/sdk")
directory_source_group("src/support")
directory_source_group("include/sampgdk")
directory_source_group("include/sampgdk/generated")
directory_source_group("include/sampgdk/sdk")
directory_source_group("include/sampgdk/sdk/amx")

add_library(sampgdk SHARED ${SAMPGDK_HEADER_FILES} ${SAMPGDK_SOURCE_FILES})

set_target_properties(sampgdk PROPERTIES DEBUG_POSTFIX "_d")

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

if(WIN32)
	set_target_properties(sampgdk OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}")
elseif(UNIX)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   "${SAMPGDK_VERSION_STRING}"
		SOVERSION "${SAMPGDK_VERSION_MAJOR}"
	)
endif()

add_target_definitions(sampgdk "IN_SAMPGDK")

if(WIN32)
	if(MSVC)
		add_target_definitions(sampgdk "_CRT_SECURE_NO_WARNINGS")
	endif()
	add_target_definitions(sampgdk "ASM_PREFIX=\"_\"")
elseif(UNIX)
	add_target_definitions(sampgdk "ASM_PREFIX=")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	add_target_compile_flags(sampgdk "-Wno-attributes")
	if(UNIX)
		add_target_link_flags(sampgdk
			"-Wl,--no-undefined"
			"-Wl,--retain-symbols-file=${CMAKE_SOURCE_DIR}/src/sampgdk.sym"
		)
	endif()
endif()

if(UNIX)
	# Find librt (POSIX realtime extensions), needed for clock_gettime().
	find_library(LIBRT_PATH NAMES "rt")
	if(LIBRT_PATH)
		target_link_libraries(sampgdk ${LIBRT_PATH})
	else()
		message(WARNING "Could not find librt")
	endif()

	find_library(LIBDL_PATH NAMES "dl")
	if(LIBDL_PATH)
		target_link_libraries(sampgdk ${LIBDL_PATH})
	else()
		message(WARNING "Could not find libdl")
	endif()
endif()

target_link_libraries(sampgdk "subhook")

option(SAMPGDK_INSTALL "Include installation and packaging rules" OFF)
if(SAMPGDK_INSTALL)
	install(TARGETS sampgdk 
		RUNTIME DESTINATION "bin" COMPONENT "bin"
		ARCHIVE DESTINATION "lib" COMPONENT "dev"
		LIBRARY DESTINATION "lib" COMPONENT "bin"
	)
	install(DIRECTORY "include" DESTINATION "." COMPONENT "dev" FILES_MATCHING PATTERN "*.h")

	if(UNIX)
		set(CPACK_PACKAGE_NAME "lib${CMAKE_PROJECT_NAME}")
	else()
		set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
	endif()

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

	if(WIN32)
		set(DEFAULT_CPACK_GENERATOR "NSIS")
	else()
		set(DEFAULT_CPACK_GENERATOR "STGZ")
	endif()

	set(SAMPGDK_CPACK_GENERATOR "${DEFAULT_CPACK_GENERATOR}" CACHE STRING "CPack generator to use")
	if(NOT SAMPGDK_CPACK_GENERATOR)
		set(SAMPGDK_CPACK_GENERATOR "${DEFAULT_CPACK_GENERATOR}")
	endif()

	set(CPACK_GENERATOR "${SAMPGDK_CPACK_GENERATOR}")

	if(SAMPGDK_CPACK_GENERATOR STREQUAL "NSIS")
		set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
		set(CPACK_NSIS_MODIFY_PATH ON)
	elseif(SAMPGDK_CPACK_GENERATOR STREQUAL "DEB")
		set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
		set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-0_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
	elseif(SAMPGDK_CPACK_GENERATOR STREQUAL "RPM")
		set(CPACK_RPM_PACKAGE_RELEASE "0")
		set(CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
		set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-0.${CPACK_RPM_PACKAGE_ARCHITECTURE}")
	endif()

	include(CPack)
endif()

option(SAMPGDK_BUILD_SAMPLES "Build sample gamemodes" OFF)
if(SAMPGDK_BUILD_SAMPLES)
	add_subdirectory("samples")
endif()
