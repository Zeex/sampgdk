cmake_minimum_required(VERSION 2.8.8)

project(sampgdk)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(AddTargetCompileFlags)
include(AddTargetDefinitions)
include(AddTargetIncludeDirs)
include(AddTargetLinkFlags)
include(AmxConfig)
include(ReadVersionFromFile)

include_directories("include")
include_directories("include/sampgdk")

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cidl"
	"${CMAKE_CURRENT_SOURCE_DIR}/python/ply-3.4.zip"
)

foreach(path IN LISTS PYTHONPATH)
	if(WIN32)
		set(ENV{PYTHONPATH} "${path};$ENV{PYTHONPATH}")
	else()
		set(ENV{PYTHONPATH} "${path}:$ENV{PYTHONPATH}")
	endif()
endforeach()

file(MAKE_DIRECTORY "src/generated")
file(MAKE_DIRECTORY "include/sampgdk/generated")

add_custom_command(
	OUTPUT
		"${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_objects.h"
		"${CMAKE_SOURCE_DIR}/src/generated/a_objects.c"
		"${CMAKE_SOURCE_DIR}/src/generated/a_objects.exports"
	COMMAND
		${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/codegen.py" "--all"
			"--idl"     "${CMAKE_SOURCE_DIR}/src/a_objects.idl"
			"--header"  "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_objects.h"
			"--source"  "${CMAKE_SOURCE_DIR}/src/generated/a_objects.c"
			"--exports" "${CMAKE_SOURCE_DIR}/src/generated/a_objects.exports"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/src/a_objects.idl"
)

add_custom_command(
	OUTPUT
		"${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_players.h"
		"${CMAKE_SOURCE_DIR}/src/generated/a_players.c"
		"${CMAKE_SOURCE_DIR}/src/generated/a_players.exports"
	COMMAND
		${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/codegen.py" "--all"
			"--idl"     "${CMAKE_SOURCE_DIR}/src/a_players.idl"
			"--header"  "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_players.h"
			"--source"  "${CMAKE_SOURCE_DIR}/src/generated/a_players.c"
			"--exports" "${CMAKE_SOURCE_DIR}/src/generated/a_players.exports"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/src/a_players.idl"
)

add_custom_command(
	OUTPUT
		"${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_samp.h"
		"${CMAKE_SOURCE_DIR}/src/generated/a_samp.c"
		"${CMAKE_SOURCE_DIR}/src/generated/a_samp.exports"
	COMMAND
		${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/codegen.py" "--all"
			"--idl"     "${CMAKE_SOURCE_DIR}/src/a_samp.idl"
			"--header"  "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_samp.h"
			"--source"  "${CMAKE_SOURCE_DIR}/src/generated/a_samp.c"
			"--exports" "${CMAKE_SOURCE_DIR}/src/generated/a_samp.exports"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/src/a_samp.idl"
)

add_custom_command(
	OUTPUT
		"${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_vehicles.h"
		"${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.c"
		"${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.exports"
	COMMAND
		${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/codegen.py" "--all"
			"--idl"     "${CMAKE_SOURCE_DIR}/src/a_vehicles.idl"
			"--header"  "${CMAKE_SOURCE_DIR}/include/sampgdk/generated/a_vehicles.h"
			"--source"  "${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.c"
			"--exports" "${CMAKE_SOURCE_DIR}/src/generated/a_vehicles.exports"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/src/a_vehicles.idl"
)

set(SAMPGDK_HEADERS
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

set(SAMPGDK_GENERATED_HEADERS
	"include/sampgdk/generated/a_objects.h"
	"include/sampgdk/generated/a_players.h"
	"include/sampgdk/generated/a_samp.h"
	"include/sampgdk/generated/a_vehicles.h"
)

set(SAMPGDK_SOURCES
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

set(SAMPGDK_GENERATED_SOURCES
	"src/generated/a_objects.c"
	"src/generated/a_players.c"
	"src/generated/a_samp.c"
	"src/generated/a_vehicles.c"
)

if(MSVC)
	list(APPEND SAMPGDK_SOURCES
		"src/asm-msvc.c"
	)
elseif(CMAKE_COMPILER_IS_GNUCC)
	list(APPEND SAMPGDK_SOURCES
		"src/asm-gcc.c"
	)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

if(WIN32)
	list(APPEND SAMPGDK_SOURCES
		"src/sampgdk.def"
		"src/sampgdk.rc"
		"src/plugin-win32.c"
		"src/timer-win32.c"
	)
elseif(UNIX)
	list(APPEND SAMPGDK_SOURCES
		"src/plugin-linux.c"
		"src/timer-linux.c"
	)
else()
	message(FATAL_ERROR "Unsupported operating system")
endif()

set_source_files_properties(${SAMPGDK_GENERATED_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${SAMPGDK_GENERATED_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND SAMPGDK_HEADERS ${SAMPGDK_GENERATED_HEADERS})
list(APPEND SAMPGDK_SOURCES ${SAMPGDK_GENERATED_SOURCES})

function(directory_source_group path)
	string(REGEX REPLACE "/" "\\\\" win_path ${path})
	source_group(${win_path} REGULAR_EXPRESSION "${path}/[^/\\]+\\..*")
endfunction()

directory_source_group("src")
directory_source_group("src/generated")
directory_source_group("src/sdk")
directory_source_group("src/support")
directory_source_group("include/sampgdk")
directory_source_group("include/sampgdk/generated")
directory_source_group("include/sampgdk/sdk")
directory_source_group("include/sampgdk/sdk/amx")

add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET sampgdk PROPERTY FOLDER "sampgdk")

read_version_from_file("${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt"
	SAMPGDK_VERSION_STRING
	SAMPGDK_VERSION_MAJOR
	SAMPGDK_VERSION_MINOR
	SAMPGDK_VERSION_PATCH
	SAMPGDK_VERSION_TWEAK
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/include/sampgdk/version.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/sampgdk/version.h"
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.rc.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.rc"
)

function(get_exports var)
	file(GLOB_RECURSE files "src/*.exports")
	foreach(file IN LISTS files)
		file(STRINGS ${file} exports)
		list(APPEND all_exports ${exports})
	endforeach()
	set(${var} ${all_exports} PARENT_SCOPE)
endfunction()

set_target_properties(sampgdk PROPERTIES DEBUG_POSTFIX "_d")
add_target_definitions(sampgdk "IN_SAMPGDK")

if(CMAKE_COMPILER_IS_GNUCC)
	add_target_compile_flags(sampgdk "-Wno-attributes")
endif()

if(WIN32)
	set(def_path "${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.def")
	if(EXISTS "${def_path}")
		file(REMOVE ${def_path})
	endif()

	get_exports(exports)
	if(exports)
		file(APPEND ${def_path} "EXPORTS\n")
		foreach(name IN LISTS exports)
			file(APPEND ${def_path} "\t${name}\n")
		endforeach()
	endif()

	if(MSVC)
		add_target_definitions(sampgdk "_CRT_SECURE_NO_WARNINGS")
	endif()

	add_target_definitions(sampgdk "ASM_PREFIX=\"_\"")

	set_target_properties(sampgdk PROPERTIES 
		PREFIX      ""
		OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}"
	)
endif()

if(UNIX)
	set(sym_path "${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.sym")
	if(EXISTS ${sym_path})
		file(REMOVE ${sym_path})
	endif()

	get_exports(exports)
	if(exports)
		foreach(name IN LISTS exports)
			file(APPEND ${sym_path} "${name}\n")
		endforeach()
	endif()

	set_target_properties(sampgdk PROPERTIES 
		VERSION   "${SAMPGDK_VERSION_STRING}"
		SOVERSION "${SAMPGDK_VERSION_MAJOR}"
	)

	add_target_definitions(sampgdk "ASM_PREFIX=")

	if(CMAKE_COMPILER_IS_GNUCC)
		add_target_link_flags(sampgdk
			"-Wl,--no-undefined"
			"-Wl,--retain-symbols-file=${sym_path}"
		)
	endif()

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

add_subdirectory("lib")
add_target_definitions(sampgdk ${lib_compile_defs})
add_target_include_dirs(sampgdk ${lib_include_dirs})
target_link_libraries(sampgdk ${lib_libraries})

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

