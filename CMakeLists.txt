project(sampgdk)
cmake_minimum_required(VERSION 2.8.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(AmxConfig)
include(ParseVersionString)

include_directories("include")
include_directories("include/sampgdk")
include_directories("lib/subhook")

set(SUBHOOK_ARCH   x86)
set(SUBHOOK_STATIC TRUE)

add_subdirectory("lib/subhook")
list(APPEND SAMPGDK_LINK_LIBRARIES subhook)

find_package(PythonInterp 2.6 REQUIRED)

function(run_python_script script input_file output_file)
	execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMAND        ${PYTHON_EXECUTABLE} ${script}
		INPUT_FILE     ${input_file}
		OUTPUT_FILE    ${output_file}
		ERROR_VARIABLE error)
	if(error)
		message(FATAL_ERROR ${error})
	endif()
endfunction()

file(MAKE_DIRECTORY "src/generated/")
run_python_script("scripts/generate_native_impl.py" "include/sampgdk/a_objects.h" "src/generated/a_objects-impl.c")
run_python_script("scripts/generate_native_impl.py" "include/sampgdk/a_players.h" "src/generated/a_players-impl.c")
run_python_script("scripts/generate_native_impl.py" "include/sampgdk/a_samp.h" "src/generated/a_samp-impl.c")
run_python_script("scripts/generate_native_impl.py" "include/sampgdk/a_vehicles.h" "src/generated/a_vehicles-impl.c")
run_python_script("scripts/generate_callback_handlers.py" "include/sampgdk/a_samp.h" "src/generated/callback-handlers.c")

file(MAKE_DIRECTORY "include/sampgdk/generated/")
run_python_script("scripts/generate_native_def.py" "include/sampgdk/a_objects.h" "include/sampgdk/generated/a_objects-defs.h")
run_python_script("scripts/generate_native_def.py" "include/sampgdk/a_players.h" "include/sampgdk/generated/a_players-defs.h")
run_python_script("scripts/generate_native_def.py" "include/sampgdk/a_samp.h" "include/sampgdk/generated/a_samp-defs.h")
run_python_script("scripts/generate_native_def.py" "include/sampgdk/a_vehicles.h" "include/sampgdk/generated/a_vehicles-defs.h")

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

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" VERSION_txt LIMIT_COUNT 1)

list(LENGTH VERSION_txt length)
if(length EQUAL 0)
	message(FATAL_ERROR "VERSION.txt is empty?")
endif()

list(GET VERSION_txt 0 SAMPGDK_VERSION_STRING)
set(SAMPGDK_VERSION_MAJOR 0)
set(SAMPGDK_VERSION_MINOR 0)
set(SAMPGDK_VERSION_PATCH 0)
set(SAMPGDK_VERSION_TWEAK 0)

parse_version_string(${SAMPGDK_VERSION_STRING} version)

list(LENGTH version length)
if(length GREATER 0)
	list(GET version 0 SAMPGDK_VERSION_MAJOR)
endif()
if(length GREATER 1)
	list(GET version 1 SAMPGDK_VERSION_MINOR)
endif()
if(length GREATER 2)
	list(GET version 2 SAMPGDK_VERSION_PATCH)
endif()
if(length GREATER 3)
	list(GET version 3 SAMPGDK_VERSION_TWEAK)
endif()

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/include/sampgdk/version.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/sampgdk/version.h"
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.rc.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sampgdk.rc"
)

set_property(TARGET sampgdk PROPERTY DEBUG_POSTFIX "_d")

list(APPEND SAMPGDK_COMPILE_DEFS
	"IN_SAMPGDK"
	"SUBHOOK_STATIC"
)

if(WIN32)
	if(MSVC)
		list(APPEND SAMPGDK_COMPILE_DEFS "_CRT_SECURE_NO_WARNINGS")
	elseif(CMAKE_COMPILER_IS_GNUCC)
		list(APPEND SAMPGDK_COMPILE_FLAGS "-Wno-attributes")
	endif()

	list(APPEND SAMPGDK_COMPILE_DEFS "ASM_PREFIX=\"_\"")

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

	list(APPEND SAMPGDK_COMPILE_DEFS "ASM_PREFIX=")

	if(CMAKE_COMPILER_IS_GNUCC)
		list(APPEND SAMPGDK_LINNK_FLAGS
			"-Wl,--export-dynamic"
			"-Wl,--no-undefined"
		)
	endif()

	# Find librt (POSIX realtime extensions), needed for clock_gettime().
	find_library(LIBRT_PATH NAMES "rt")

	if(LIBRT_PATH)
		list(APPEND SAMPGDK_LINK_LIBRARIES ${LIBRT_PATH})
	else()
		message(WARNING "Could not find librt")
	endif()
endif()

foreach(def IN LISTS SAMPGDK_COMPILE_DEFS)
	set_property(TARGET sampgdk APPEND PROPERTY COMPILE_DEFINITIONS "${def}")
endforeach()

foreach(flag IN LISTS SAMPGDK_COMPILE_FLAGS)
	set_property(TARGET sampgdk APPEND_STRING PROPERTY COMPILE_FLAGS " ${flag}")
endforeach()

foreach(flag IN LISTS SAMPGDK_LINK_FLAGS)
	set_property(TARGET sampgdk APPEND_STRING PROPERTY LINK_FLAGS " ${flag}")
endforeach()

target_link_libraries(sampgdk ${SAMPGDK_LINK_LIBRARIES})

install(TARGETS sampgdk 
	RUNTIME DESTINATION "bin" COMPONENT "runtime"
	LIBRARY DESTINATION "lib" COMPONENT "libraries"
	ARCHIVE DESTINATION "lib" COMPONENT "libraries"
)

foreach(header IN LISTS SAMPGDK_HEADERS)
	file(RELATIVE_PATH header_relative_to_include
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/${header}"
	)
	get_filename_component(header_directory ${header_relative_to_include} PATH)
	install(FILES ${header} DESTINATION "include/${header_directory}")
endforeach()

if(MSVC)
	set(CONFIG_NAME "\${CMAKE_INSTALL_CONFIG_NAME}")
	get_target_property(OUTPUT_NAME sampgdk OUTPUT_NAME)
	set(PDB_NAME "${OUTPUT_NAME}.pdb")
	set(PDB_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_NAME}/${PDB_NAME}")
	install(FILES ${PDB_PATH} DESTINATION "bin" COMPONENT "runtime")
endif()

set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "sampgdk ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
if(WIN32)
	set(CPACK_GENERATOR NSIS)
	set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
	set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime library")
	set(CPACK_COMPONENT_RUNTIME_INSTALL_TYPES "Full" "Runtime Only")
	set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
	set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Import library")
	set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
	set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES "Full")
	set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C/C++ headers")
	set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C/C++ header files for developers")
	set(CPACK_COMPONENT_HEADERS_GROUP "Development")
	set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES "Full")
	set(CPACK_COMPONENT_HEADERS_DEPENDS "libraries")
	set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
	set(CPACK_NSIS_MODIFY_PATH ON)
elseif(UNIX)
	set(CPACK_GENERATOR STGZ)
endif()

include(CPack)

option(SAMPGDK_BUILD_SAMPLES "Build sample gamemodes" OFF)
if(SAMPGDK_BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

