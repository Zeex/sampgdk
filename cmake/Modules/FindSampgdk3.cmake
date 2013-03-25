# Find sampgdk 3.x library and headers
#
# Defined variables:
#   Sampgdk3_FOUND
#   Sampgdk3_LIBRARY_DIRS
#   Sampgdk3_LIBRARY (cached)
#   Sampgdk3_LIBRARY_DEBUG
#   Sampgdk3_LIBRARY_RELEASE
#   Sampgdk3_LIBRARIES
#   Sampgdk3_INCLUDE_DIR (cached)
#   Sampgdk3_INCLUDE_DIRS
	
find_path(Sampgdk3_INCLUDE_DIR NAMES "sampgdk/a_samp.h")

find_library(Sampgdk3_LIBRARY_DEBUG NAMES "sampgdk3_d" "libsampgdk_d.so.3")
find_library(Sampgdk3_LIBRARY_RELEASE NAMES "sampgdk3" "libsampgdk.so.3")

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

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sampgdk3
	REQUIRED_VARS Sampgdk3_INCLUDE_DIRS Sampgdk3_LIBRARY_DIRS Sampgdk3_LIBRARIES
)