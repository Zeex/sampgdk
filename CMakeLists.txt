# Use this file to build GDK with CMake: http://cmake.org

project(sampgdk)
cmake_minimum_required(VERSION 2.8.6)

list(APPEND CMAKE_MODULE_PATH "${sampgdk_SOURCE_DIR}/cmake/Modules")

include(AmxConfig)
include(ParseVersionString)

include_directories("include")

set(SUBHOOK_STATIC TRUE)
add_definitions(-DSUBHOOK_STATIC)
add_subdirectory("lib/subhook")
include_directories("lib/subhook")
list(APPEND SAMPGDK_LINK_LIBRARIES subhook)

find_package(PythonInterp 2.6 REQUIRED)

function(run_python_script script input_file output_file)
	execute_process(WORKING_DIRECTORY ${sampgdk_SOURCE_DIR}
		COMMAND ${PYTHON_EXECUTABLE} ${script}
		INPUT_FILE ${input_file}
		OUTPUT_FILE ${output_file}
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
run_python_script("scripts/generate_native_defs.py" "include/sampgdk/a_objects.h" "include/sampgdk/generated/a_objects-defs.h")
run_python_script("scripts/generate_native_defs.py" "include/sampgdk/a_players.h" "include/sampgdk/generated/a_players-defs.h")
run_python_script("scripts/generate_native_defs.py" "include/sampgdk/a_samp.h" "include/sampgdk/generated/a_samp-defs.h")
run_python_script("scripts/generate_native_defs.py" "include/sampgdk/a_vehicles.h" "include/sampgdk/generated/a_vehicles-defs.h")

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
	"include/sampgdk/plugin.h"
	"include/sampgdk/config.h"
	"include/sampgdk/core.h"
	"include/sampgdk/export.h"
	"include/sampgdk/version.h"
)

set(SAMPGDK_SOURCES
	"src/sdk/amxplugin.c"
	"src/sdk/plugin.h"
	"src/a_objects.c"
	"src/a_players.c"
	"src/a_samp.c"
	"src/a_vehicles.c"
	"src/array.c"
	"src/array.h"
	"src/callback.c"
	"src/callback.h"
	"src/core.c"
	"src/fakeamx.c"
	"src/fakeamx.h"
	"src/native.c"
	"src/native.h"
	"src/plugin.c"
	"src/plugin.h"
	"src/sampgdk.rc"
	"src/timer.c"
	"src/timer.h"
	"src/util.c"
	"src/util.h"
	"src/version.c"
)

if(WIN32)
	list(APPEND SAMPGDK_SOURCES
		"src/plugin-win32.c"
		"src/timer-win32.c"
	)
elseif(UNIX)
	list(APPEND SAMPGDK_SOURCES
		"src/plugin-linux.c"
		"src/timer-linux.c"
	)
endif()

source_group("src" REGULAR_EXPRESSION "src/[^/\\]+\\..*")
source_group("src\\sdk" REGULAR_EXPRESSION "src/sdk/[^/\\]+\\..*")
source_group("include" REGULAR_EXPRESSION "include/sampgdk/[^/\\]+\\.h")
source_group("include\\sdk" REGULAR_EXPRESSION "include/sampgdk/sdk/[^/\\]+\\.h")
source_group("include\\sdk\\amx" REGULAR_EXPRESSION "include/sampgdk/sdk/amx/[^/\\]+\\.h")

add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET sampgdk PROPERTY FOLDER "sampgdk")

file(STRINGS "${sampgdk_SOURCE_DIR}/VERSION.txt" VERSION_txt LIMIT_COUNT 1)
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
	"${sampgdk_SOURCE_DIR}/include/sampgdk/version.h.in"
	"${sampgdk_SOURCE_DIR}/include/sampgdk/version.h"
)

set_target_properties(sampgdk PROPERTIES DEBUG_POSTFIX "_d")
add_definitions(-DIN_SAMPGDK)

if(WIN32)
	set(DEF_FILE "${sampgdk_SOURCE_DIR}/src/sampgdk.def")
	if(MINGW)
		set_property(TARGET sampgdk APPEND_STRING PROPERTY 
			LINK_FLAGS " -Wl,--kill-at --def ${DEF_FILE}")
	elseif(MSVC)
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)		
		set_property(TARGET sampgdk APPEND_STRING PROPERTY 
			LINK_FLAGS " /DEF:${DEF_FILE}")
	endif()
	set_target_properties(sampgdk PROPERTIES 
		PREFIX      ""
		OUTPUT_NAME "sampgdk${SAMPGDK_VERSION_MAJOR}")
endif()

if(UNIX OR MINGW)
	set_target_properties(sampgdk PROPERTIES 
		VERSION   ${SAMPGDK_VERSION_STRING}
		SOVERSION ${SAMPGDK_VERSION_MAJOR}
	)
	if(MINGW)
		set_property(TARGET sampgdk APPEND_STRING PROPERTY
			LINK_FLAGS " -Wl,--export-all-symbols")
	else()
		add_definitions(-DLINUX)
		set_property(TARGET sampgdk APPEND_STRING PROPERTY
			LINK_FLAGS " -Wl,--export-dynamic")
		list(APPEND SAMPGDK_LINK_LIBRARIES "-lrt")
	endif()
endif()

target_link_libraries(sampgdk ${SAMPGDK_LINK_LIBRARIES})

install(TARGETS sampgdk 
	RUNTIME DESTINATION "bin" COMPONENT "runtime"
	LIBRARY DESTINATION "lib" COMPONENT "libraries"
	ARCHIVE DESTINATION "lib" COMPONENT "libraries"
)
install(DIRECTORY "include" DESTINATION "." COMPONENT "headers" FILES_MATCHING PATTERN "*.h")

if(MSVC)
	option(SAMPGDK_INSTALL_PDB "Install program database (.pdb) file" OFF)
	if(SAMPGDK_INSTALL_PDB)
		set(CONFIG_NAME "\${CMAKE_INSTALL_CONFIG_NAME}")
		get_target_property(OUTPUT_NAME sampgdk OUTPUT_NAME)
		set(PDB_NAME "${OUTPUT_NAME}.pdb")
		set(PDB_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_NAME}/${PDB_NAME}")
		install(FILES ${PDB_PATH} DESTINATION "bin" COMPONENT "runtime")
	endif()
endif()

set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "sampgdk ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
set(CPACK_RESOURCE_FILE_LICENSE "${sampgdk_SOURCE_DIR}/LICENSE.txt")
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


option(SAMPGDK_BUILD_SAMPLES "Build sample plugins" OFF)
if(SAMPGDK_BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

