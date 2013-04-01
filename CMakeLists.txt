cmake_minimum_required(VERSION 2.8.8)
project(sampgdk)

option(SAMPGDK_BUILD_PLUGINS "Build example plugins" OFF)
option(SAMPGDK_STATIC "Build static library instead" OFF)

set(SAMPGDK_VERSION_MAJOR "3")
set(SAMPGDK_VERSION_MINOR "3")
set(SAMPGDK_VERSION_PATCH "0")
set(SAMPGDK_VERSION_TWEAK "0")
set(SAMPGDK_VERSION_STRING "3.3")

list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/cmake"
	"${PROJECT_SOURCE_DIR}/cmake/Modules"
)

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

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_BINARY_DIR}/src")

find_package(PythonInterp 2.7 REQUIRED)

set(PYTHONPATH
	"${PROJECT_SOURCE_DIR}/cidl"
	"${PROJECT_SOURCE_DIR}/lib/python/ply"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(SAMPGDK_STATIC)
	add_definitions(-DSAMPGDK_STATIC)
	
endif()

add_subdirectory("include")
add_subdirectory("lib")
add_subdirectory("src")
if(SAMPGDK_BUILD_PLUGINS)
	add_subdirectory("plugins")
endif()

if(SAMPGDK_STATIC)
	get_property(libs DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	            PROPERTY LIBRARIES)
	foreach(lib IN LISTS libs)
		get_target_property(sources ${lib} SOURCES)
		foreach(file IN LISTS sources)
			list(APPEND SAMPGDK_SOURCES "${${lib}_SOURCE_DIR}/${file}")
		endforeach()
	endforeach()
endif()

list(APPEND SAMPGDK_HEADERS
	"include/sampgdk/sdk/amx/amx.h"
	"include/sampgdk/sdk/amx/getch.h"
	"include/sampgdk/sdk/amx/sclinux.h"
	"include/sampgdk/sdk/plugincommon.h"
	"include/sampgdk/a_objects.h"
	"include/sampgdk/a_objects.hpp"
	"include/sampgdk/a_players.h"
	"include/sampgdk/a_players.hpp"
	"include/sampgdk/a_samp.h"
	"include/sampgdk/a_samp.hpp"
	"include/sampgdk/a_vehicles.h"
	"include/sampgdk/a_vehicles.hpp"
	"include/sampgdk/amx.h"
	"include/sampgdk/bool.h"
	"include/sampgdk/callnative.hpp"
	"include/sampgdk/core.h"
	"include/sampgdk/core.hpp"
	"include/sampgdk/export.h"
	"include/sampgdk/platform.h"
	"include/sampgdk/plugin.h"
	"include/sampgdk/plugincommon.h"
	"${PROJECT_BINARY_DIR}/include/sampgdk/version.h"
)

list(APPEND SAMPGDK_SOURCES
	"src/sdk/amxplugin.c"
	"src/sdk/plugin.h"
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
	"src/init.h"
	"src/likely.h"
	"src/log.c"
	"src/log.h"
	"src/logprintf.c"
	"src/logprintf.h"
	"src/native.c"
	"src/native.h"
	"src/plugin.c"
	"src/plugin.h"
	"src/timer.c"
	"src/timer.h"
	"src/version.c"
)

if(WIN32)
	list(APPEND SAMPGDK_SOURCES "${PROJECT_BINARY_DIR}/src/call.asm.obj")
	if("${CMAKE_ASM_NASM_COMPILER}" MATCHES "[yY][aA][sS][mM]")
		set(options "-f" "win32" "--prefix=_")
	else()
		set(options "-fwin32" "--prefix" "_")
	endif()
	add_custom_command(
		OUTPUT  "${PROJECT_BINARY_DIR}/src/call.asm.obj"
		COMMAND "${CMAKE_ASM_NASM_COMPILER}" ${options} "-o"
			"${PROJECT_BINARY_DIR}/src/call.asm.obj"
			"${PROJECT_SOURCE_DIR}/src/call.asm"
		MAIN_DEPENDENCY "${PROJECT_SOURCE_DIR}/src/call.asm"
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

macro(sampgdk_add_api_gen module_name idl_file api_file)
	add_custom_command(OUTPUT ${api_file}
		COMMAND ${CMAKE_COMMAND}
			"-DCODEGEN_MODULE_NAME=${module_name}"
			"-DCODEGEN_IDL_FILE=${idl_file}"
			"-DCODEGEN_API_FILE=${api_file}"
			"-P" "${PROJECT_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS ${idl_file} "src/codegen.py")
	list(APPEND SAMPGDK_APIS ${api_file})
endmacro()

macro(sampgdk_add_header_gen module_name idl_file header_file)
	add_custom_command(OUTPUT ${header_file}
		COMMAND ${CMAKE_COMMAND}
			"-DCODEGEN_MODULE_NAME=${module_name}"
			"-DCODEGEN_IDL_FILE=${idl_file}"
			"-DCODEGEN_HEADER_FILE=${header_file}"
			"-P" "${PROJECT_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS ${idl_file} "src/codegen.py"
	)
	list(APPEND SAMPGDK_HEADERS ${header_file})
endmacro()

macro(sampgdk_add_source_gen module_name idl_file source_file)
	add_custom_command(OUTPUT ${source_file}
		COMMAND ${CMAKE_COMMAND}
			"-DCODEGEN_MODULE_NAME=${module_name}"
			"-DCODEGEN_IDL_FILE=${idl_file}"
			"-DCODEGEN_SOURCE_FILE=${source_file}"
			"-P" "${PROJECT_BINARY_DIR}/src/codegen.py.cmake"
		DEPENDS ${idl_file} "src/codegen.py")
	list(APPEND SAMPGDK_SOURCES ${source_file})
endmacro()

macro(sampgdk_add_module name)
	sampgdk_add_api_gen(${name}
		"${PROJECT_SOURCE_DIR}/src/${name}.idl"
		"${PROJECT_BINARY_DIR}/src/${name}.api"
	)
	sampgdk_add_source_gen(${name}
		"${PROJECT_SOURCE_DIR}/src/${name}.idl"
		"${PROJECT_BINARY_DIR}/src/${name}-impl.c"
	)
	sampgdk_add_header_gen(${name}
		"${PROJECT_SOURCE_DIR}/src/${name}.idl"
		"${PROJECT_BINARY_DIR}/include/sampgdk/${name}-decl.h"
	)
endmacro()

sampgdk_add_module("a_objects")
sampgdk_add_module("a_players")
sampgdk_add_module("a_samp")
sampgdk_add_module("a_vehicles")

if(WIN32)
	add_custom_command(
		OUTPUT  "${PROJECT_BINARY_DIR}/src/sampgdk.def"
		COMMAND "${CMAKE_COMMAND}" "-P" "${PROJECT_BINARY_DIR}/src/sampgdk.def.cmake"
		DEPENDS ${SAMPGDK_APIS}
	)
elseif(UNIX)
	add_custom_command(
		OUTPUT  "${PROJECT_BINARY_DIR}/src/sampgdk.sym"
		COMMAND "${CMAKE_COMMAND}" "-P" "${PROJECT_BINARY_DIR}/src/sampgdk.sym.cmake"
		DEPENDS ${SAMPGDK_APIS}
	)
endif()

list(APPEND SAMPGDK_SOURCES ${SAMPGDK_APIS})

if(SAMPGDK_STATIC)
	add_library(sampgdk STATIC ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
else()
	add_library(sampgdk SHARED ${SAMPGDK_HEADERS} ${SAMPGDK_SOURCES})
endif()

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
	set_property(TARGET sampgdk APPEND PROPERTY
	             COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
endif()

if(UNIX AND NOT WIN32)
	set_property(TARGET sampgdk APPEND_STRING PROPERTY
	             LINK_FLAGS " -Wl,--no-undefined")
	set_property(TARGET sampgdk APPEND_STRING PROPERTY
	             LINK_FLAGS " -Wl,--retain-symbols-file=${PROJECT_BINARY_DIR}/src/sampgdk.sym")
	if(NOT SAMPGDK_STATIC)
		target_link_libraries(sampgdk ${CMAKE_DL_LIBS} "rt")
	endif()
endif()

if(NOT SAMPGDK_STATIC)
	get_property(libs DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	            PROPERTY LIBRARIES)
	target_link_libraries(sampgdk ${libs})
endif()

foreach(header IN LISTS SAMPGDK_HEADERS)
	get_filename_component(path ${header} PATH)
	get_filename_component(abs_path ${path} ABSOLUTE)

	if(header MATCHES "${PROJECT_BINARY_DIR}")
		file(RELATIVE_PATH dir ${PROJECT_BINARY_DIR} ${abs_path})
	else()
		file(RELATIVE_PATH dir ${PROJECT_SOURCE_DIR} ${abs_path})
	endif()

	install(FILES ${header} DESTINATION ${dir})
endforeach()

install(TARGETS sampgdk
	RUNTIME DESTINATION "bin" COMPONENT "bin"
	ARCHIVE DESTINATION "lib" COMPONENT "dev"
	LIBRARY DESTINATION "lib" COMPONENT "bin"
)

set(CPACK_PACKAGE_NAME "sampgdk")
set(CPACK_PACKAGE_CONTACT "CPack")
set(CPACK_PACKAGE_VERSION ${SAMPGDK_VERSION_STRING})
set(CPACK_PACKAGE_VERSION_MAJOR ${SAMPGDK_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SAMPGDK_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SAMPGDK_VERSION_PATCH})

if(WIN32)
	set(CPACK_PACKAGE_INSTALL_DIRECTORY
	    "${CPACK_PACKAGE_NAME} ${SAMPGDK_VERSION_MAJOR}.${SAMPGDK_VERSION_MINOR}")
endif()

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
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
