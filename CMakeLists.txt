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

function(python script input_file output_file)
	execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMAND        ${PYTHON_EXECUTABLE} ${script} ${ARGN}
		INPUT_FILE     ${input_file}
		OUTPUT_FILE    ${output_file}
		ERROR_VARIABLE error)
	if(error)
		message(FATAL_ERROR ${error})
	endif()
endfunction()

function(generate_native_impl input output)
	python("scripts/generate_native_impl.py" ${input} ${output})
endfunction()

function(generate_native_def input output)
	python("scripts/generate_native_def.py" ${input} ${output})
endfunction()

function(generate_callback_handlers input output reg_func_name)
	python("scripts/generate_callback_handlers.py" ${input} ${output} ${reg_func_name})
endfunction()

file(MAKE_DIRECTORY "src/generated/")
generate_native_impl("include/sampgdk/a_objects.h" "src/generated/a_objects-impl.c")
generate_native_impl("include/sampgdk/a_players.h" "src/generated/a_players-impl.c")
generate_native_impl("include/sampgdk/a_samp.h" "src/generated/a_samp-impl.c")
generate_native_impl("include/sampgdk/a_vehicles.h" "src/generated/a_vehicles-impl.c")

file(MAKE_DIRECTORY "src/generated/core/")
generate_callback_handlers("include/sampgdk/a_samp.h" "src/generated/core/callback-handlers.c" "register_callback_handlers")

file(MAKE_DIRECTORY "include/sampgdk/generated/")
generate_native_def("include/sampgdk/a_objects.h" "include/sampgdk/generated/a_objects-def.h")
generate_native_def("include/sampgdk/a_players.h" "include/sampgdk/generated/a_players-def.h")
generate_native_def("include/sampgdk/a_samp.h" "include/sampgdk/generated/a_samp-def.h")
generate_native_def("include/sampgdk/a_vehicles.h" "include/sampgdk/generated/a_vehicles-def.h")

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

set_target_properties(sampgdk PROPERTIES DEBUG_POSTFIX "_d")
add_target_definitions(sampgdk "IN_SAMPGDK")

if(WIN32)
	# Generate a module definition (.def) file
	file(WRITE "src/sampgdk.def" "EXPORTS\n")
	file(GLOB_RECURSE exports_files "src/*.exports")
	foreach(file IN LISTS exports_files)
		file(STRINGS "${file}" functions)
		foreach(name IN LISTS functions)
			file(APPEND "src/sampgdk.def" "\t${name}\n")
		endforeach()
	endforeach()

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

