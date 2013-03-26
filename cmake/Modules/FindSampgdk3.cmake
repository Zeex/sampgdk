# Find sampgdk 3.x library and headers
#
# Recognized user-defind variables:
# 
#   Sampgdk3_USE_STATIC_LIB
#
# Variables defined by this module:
#
#   Sampgdk3_FOUND
#   Sampgdk3_LIBRARY_DIRS
#   Sampgdk3_LIBRARY (cached)
#   Sampgdk3_LIBRARY_DEBUG
#   Sampgdk3_LIBRARY_RELEASE
#   Sampgdk3_LIBRARIES
#   Sampgdk3_INCLUDE_DIR (cached)
#   Sampgdk3_INCLUDE_DIRS
#   Sampgdk3_VERSION
#   Sampgdk3_VERSION_MAJOR
#   Sampgdk3_VERSION_MINOR
#   Sampgdk3_VERSION_PATCH
#   Sampgdk3_VERSION_TWEAK
#
# Using this module:
#
#   set(Sampgdk3_USE_STATIC_LIB FALSE)
#   find_package(Sampgdk3 VERSION 3.2.1)
#
#   if(Sampgdk3_FOUND)
#     include_directories(${Sampgdk3_INCLUDE_DIRS})
#     target_link_libraries(foo ${Sampgdk_LIBRARIES})
#   endif()
	
find_path(Sampgdk3_INCLUDE_DIR NAMES "sampgdk/version.h")

if(Sampgdk3_USE_STATIC_LIB)
	set(Sampgdk3_LIBRARY_NAMES_DEBUG "sampgdk3_d" "libsampgdk_d.a")
	set(Sampgdk3_LIBRARY_NAMES_RELEASE "sampgdk3" "libsampgdk.a")
else()
	set(Sampgdk3_LIBRARY_NAMES_DEBUG "sampgdk3_d" "libsampgdk_d.so.3")
	set(Sampgdk3_LIBRARY_NAMES_RELEASE "sampgdk3" "libsampgdk.so.3")
endif()

find_library(Sampgdk3_LIBRARY_DEBUG NAMES ${Sampgdk3_LIBRARY_NAMES_DEBUG})
find_library(Sampgdk3_LIBRARY_RELEASE NAMES ${Sampgdk3_LIBRARY_NAMES_RELEASE})

if(Sampgdk3_LIBRARY_DEBUG AND Sampgdk3_LIBRARY_RELEASE)
	if(CMAKE_CONFIGURATIONS OR CMAKE_BUILD_TYPE)
		set(Sampgdk3_LIBRARY debug ${Sampgdk3_LIBRARY_DEBUG} optimized ${Sampgdk3_LIBRARY_RELEASE})
	else()
		set(Sampgdk3_LIBRARY ${Sampgdk3_LIBRARY_RELEASE})
	endif()
endif()

if(Sampgdk3_LIBRARY_DEBUG AND NOT Sampgdk3_LIBRARY_RELEASE)
	set(Sampgdk3_LIBRARY         ${Sampgdk3_LIBRARY_DEBUG})
	set(Sampgdk3_LIBRARY_RELEASE ${Sampgdk3_LIBRARY_DEBUG})
endif()

if(Sampgdk3_LIBRARY_RELEASE AND NOT Sampgdk3_LIBRARY_DEBUG)
	set(Sampgdk3_LIBRARY         ${Sampgdk3_LIBRARY_RELEASE})
	set(Sampgdk3_LIBRARY_DEBUG   ${Sampgdk3_LIBRARY_RELEASE})
endif()

set(Sampgdk3_LIBRARY ${Sampgdk3_LIBRARY} CACHE FILEPATH "SA-MP GDK library")
set(Sampgdk3_INCLUDE_DIR ${Sampgdk3_INCLUDE_DIR} CACHE PATH "SA-MP GDK include directory")

mark_as_advanced(
	Sampgdk3_LIBRARY_DIRS
	Sampgdk3_LIBRARY
	Sampgdk3_LIBRARY_DEBUG
	Sampgdk3_LIBRARY_RELEASE
	Sampgdk3_INCLUDE_DIR
)

foreach(lib IN LISTS Sampgdk3_LIBRARY)
	get_filename_component(path "${lib}" PATH)
	list(APPEND Sampgdk3_LIBRARY_DIRS "${path}")
endforeach()
list(REMOVE_DUPLICATES Sampgdk3_LIBRARY_DIRS)

set(Sampgdk3_LIBRARIES ${Sampgdk3_LIBRARY})
set(Sampgdk3_INCLUDE_DIRS ${Sampgdk3_INCLUDE_DIR})

mark_as_advanced(
	Sampgdk3_LIBRARIES
	Sampgdk3_INCLUDE_DIRS
)

function(get_version name text)
	string(REGEX MATCH "#define[ \t]+SAMPGDK_VERSION_${name}[ \t]+[0-9]+" match "${text}")
	if(match)
		string(REGEX REPLACE ".* ([0-9]+)" "\\1" number "${match}")
		set(Sampgdk3_VERSION_${name} ${number} PARENT_SCOPE)
	endif()
endfunction()

if(Sampgdk3_INCLUDE_DIR)
	file(READ "${Sampgdk3_INCLUDE_DIR}/sampgdk/version.h" text)
	
	get_version(MAJOR "${text}")
	get_version(MINOR "${text}")
	get_version(PATCH "${text}")
	get_version(TWEAK "${text}")
	
	if(NOT Sampgdk3_VERSION_TWEAK OR Sampgdk3_VERSION_TWEAK EQUAL 0)
		if(NOT Sampgdk3_VERSION_PATCH OR Sampgdk3_VERSION_PATCH EQUAL 0)
			set(Sampgdk3_VERSION "${Sampgdk3_VERSION_MAJOR}.${Sampgdk3_VERSION_MINOR}")
		else()
			set(Sampgdk3_VERSION "${Sampgdk3_VERSION_MAJOR}.${Sampgdk3_VERSION_MINOR}.${Sampgdk3_VERSION_PATCH}")
		endif()
	else()
		set(Sampgdk3_VERSION "${Sampgdk3_VERSION_MAJOR}.${Sampgdk3_VERSION_MINOR}.${Sampgdk3_VERSION_PATCH}.${Sampgdk3_VERSION_TWEAK}")
	endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sampgdk3
	REQUIRED_VARS Sampgdk3_INCLUDE_DIRS Sampgdk3_LIBRARY_DIRS Sampgdk3_LIBRARIES
	VERSION_VAR Sampgdk3_VERSION
)
