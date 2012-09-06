project(sampgdk)
cmake_minimum_required(VERSION 2.8.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(AddTargetCompileFlags)
include(AddTargetDefinitions)
include(AddTargetLinkFlags)
include(AmxConfig)
include(ReadVersionFromFile)

include_directories("include")
include_directories("include/sampgdk")

find_package(PythonInterp 2.6 REQUIRED)

set(PYTHONPATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cidl"
	"${CMAKE_CURRENT_SOURCE_DIR}/python/ply-3.4.zip"
)

foreach(path IN LISTS PYTHONPATH)
	set(ENV{PYTHONPATH} "${path};$ENV{PYTHONPATH}")
endforeach()

function(run_codegen idl header source exports)
	execute_process(
		COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/src/codegen.py" "-all"
		        "-idl=${CMAKE_CURRENT_SOURCE_DIR}/${idl}"
		        "-header=${CMAKE_CURRENT_SOURCE_DIR}/${header}"
		        "-source=${CMAKE_CURRENT_SOURCE_DIR}/${source}"
		        "-exports=${CMAKE_CURRENT_SOURCE_DIR}/${exports}"
		ERROR_VARIABLE error
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cidl"
	)
	if(error)
		message(FATAL_ERROR ${error})
	endif()
endfunction()

file(MAKE_DIRECTORY "src/generated/")
file(MAKE_DIRECTORY "include/sampgdk/generated")

run_codegen("src/a_objects.idl"  "include/sampgdk/generated/a_objects.h"  "src/generated/a_objects.c"  "src/generated/a_objects.exports")
run_codegen("src/a_players.idl"  "include/sampgdk/generated/a_players.h"  "src/generated/a_players.c"  "src/generated/a_players.exports")
run_codegen("src/a_samp.idl"     "include/sampgdk/generated/a_samp.h"     "src/generated/a_samp.c"     "src/generated/a_samp.exports")
run_codegen("src/a_vehicles.idl" "include/sampgdk/generated/a_vehicles.h" "src/generated/a_vehicles.c" "src/generated/a_vehicles.exports")

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

set(SAMPGDK_SOURCES
	"src/sdk/amxplugin.c"
	"src/support/amx-stack.c"
	"src/support/amx-stack.h"
	"src/support/array.c"
	"src/support/array.h"
	"src/support/asm.h"
	"src/support/callback.c"
	"src/support/callback.h"
	"src/support/fakeamx.c"
	"src/support/fakeamx.h"
	"src/support/likely.h"
	"src/support/log.c"
	"src/support/log.h"
	"src/support/logprintf-impl.c"
	"src/support/logprintf-impl.h"
	"src/support/native.c"
	"src/support/native.h"
	"src/support/plugin.c"
	"src/support/plugin.h"
	"src/support/server-cfg.c"
	"src/support/server-cfg.h"
	"src/support/server-log.c"
	"src/support/server-log.h"
	"src/support/timer.c"
	"src/support/timer.h"
	"src/a_objects.c"
	"src/a_players.c"
	"src/a_samp.c"
	"src/a_vehicles.c"
	"src/core.c"
	"src/sampgdk.def"
	"src/sampgdk.rc"
	"src/version.c"
)

if(MSVC)
	list(APPEND SAMPGDK_SOURCES
		"src/support/asm-msvc.c"
	)
elseif(CMAKE_COMPILER_IS_GNUCC)
	list(APPEND SAMPGDK_SOURCES
		"src/support/asm-gcc.c"
	)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

if(WIN32)
	list(APPEND SAMPGDK_SOURCES
		"src/support/plugin-win32.c"
		"src/support/timer-win32.c"
	)
elseif(UNIX)
	list(APPEND SAMPGDK_SOURCES
		"src/support/plugin-linux.c"
		"src/support/timer-linux.c"
	)
else()
	message(FATAL_ERROR "Unsupported operating system")
endif()

function(directory_source_group path)
	string(REGEX REPLACE "/" "\\\\" win_path ${path})
	source_group(${win_path} REGULAR_EXPRESSION "${path}/[^/\\]+\\..*")
endfunction()

directory_source_group("src")
directory_source_group("src/sdk")
directory_source_group("src/support")
directory_source_group("include/sampgdk")
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

if(WIN32)
	set(def_path "src/sampgdk.def")
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${def_path}")
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
	elseif(CMAKE_COMPILER_IS_GNUCC)
		add_target_compile_flags(sampgdk "-Wno-attributes")
	endif()

	add_target_definitions(sampgdk "ASM_PREFIX=\"_\"")

	set_target_properties(sampgdk PROPERTIES 
		PREFIX      ""
		OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}"
	)
endif()

if(UNIX)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   "${SAMPGDK_VERSION_STRING}"
		SOVERSION "${SAMPGDK_VERSION_MAJOR}"
	)

	add_target_definitions(sampgdk "ASM_PREFIX=")

	if(CMAKE_COMPILER_IS_GNUCC)
		add_target_link_flags(sampgdk 
			"-Wl,--export-dynamic"
			"-Wl,--no-undefined"
		)
	endif()

	# Find librt (POSIX realtime extensions), needed for clock_gettime().
	find_library(LIBRT_PATH NAMES "rt")

	if(LIBRT_PATH)
		list(APPEND SAMPGDK_LINK_LIBS ${LIBRT_PATH})
	else()
		message(WARNING "Could not find librt")
	endif()
endif()

add_subdirectory("lib")

include_directories(${SAMPGDK_INCLUDE_DIRS})

foreach(def IN LISTS SAMPGDK_COMPILE_DEFS)
	add_target_definitions(sampgdk ${def})
endforeach()

foreach(flag IN LISTS SAMPGDK_COMPILE_FLAGS)
	set_property(TARGET sampgdk APPEND_STRING PROPERTY COMPILE_FLAGS " ${flag}")
endforeach()

foreach(flag IN LISTS SAMPGDK_LINK_FLAGS)
	add_target_link_flags(sampgdk ${flag})
endforeach()

target_link_libraries(sampgdk ${SAMPGDK_LINK_LIBS})

option(SAMPGDK_INSTALL "Include installation and packaging rules" OFF)
if(SAMPGDK_INSTALL)
	install(TARGETS sampgdk 
		RUNTIME DESTINATION "bin" COMPONENT "bin"
		ARCHIVE DESTINATION "lib" COMPONENT "dev"
	)

	foreach(header IN LISTS SAMPGDK_HEADERS)
		file(RELATIVE_PATH header_relative_to_include
			"${CMAKE_CURRENT_SOURCE_DIR}/include"
			"${CMAKE_CURRENT_SOURCE_DIR}/${header}"
		)
		get_filename_component(header_directory ${header_relative_to_include} PATH)
		install(FILES ${header} DESTINATION "include/${header_directory}" COMPONENT "dev")
	endforeach()

	set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
	set(CPACK_PACKAGE_VERSION_MAJOR "${SAMPGDK_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR" ${SAMPGDK_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH "${SAMPGDK_VERSION_PATCH}")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "sampgdk ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
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
	endif()

	include(CPack)
endif()

option(SAMPGDK_BUILD_SAMPLES "Build sample gamemodes" OFF)
if(SAMPGDK_BUILD_SAMPLES)
	add_subdirectory("samples")
endif()

