# Find GDK library and headers.
# 
# Defined variables:
# 
#   GDK_FOUND
#   GDK_LIBRARY_DIRS
#   GDK_LIBRARY (cached)
#   GDK_LIBRARY_DEBUG
#   GDK_LIBRARY_RELEASE
#   GDK_LIBRARIES
#   GDK_INCLUDE_DIR (cached)
#   GDK_INCLUDE_DIRS
#   GDK_VERSION
#   GDK_VERSION_MAJOR
#   GDK_VERSION_MINOR
#   GDK_VERSION_PATCH
#   GDK_VERSION_TWEAK
# 
# Using this module:
# 
#   find_package(GDK VERSION 1.2.3)
#   if(GDK_FOUND)
#     include_directories(${GDK_INCLUDE_DIRS})
#     target_link_libraries(foo ${GDK_LIBRARIES})
#   endif()

include(FindPackageHandleStandardArgs)

find_path(GDK_INCLUDE_DIR NAMES "sampgdk/version.h")

find_library(GDK_LIBRARY_DEBUG   NAMES "sampgdk4_d" "sampgdk_d")
find_library(GDK_LIBRARY_RELEASE NAMES "sampgdk4"   "sampgdk")

if(GDK_LIBRARY_DEBUG AND GDK_LIBRARY_RELEASE)
  if(CMAKE_CONFIGURATIONS OR CMAKE_BUILD_TYPE)
    set(GDK_LIBRARY debug     ${GDK_LIBRARY_DEBUG}
                     optimized ${GDK_LIBRARY_RELEASE})
  else()
    set(GDK_LIBRARY ${GDK_LIBRARY_RELEASE})
  endif()
endif()

if(GDK_LIBRARY_DEBUG AND NOT GDK_LIBRARY_RELEASE)
  set(GDK_LIBRARY         ${GDK_LIBRARY_DEBUG})
  set(GDK_LIBRARY_RELEASE ${GDK_LIBRARY_DEBUG})
endif()

if(GDK_LIBRARY_RELEASE AND NOT GDK_LIBRARY_DEBUG)
  set(GDK_LIBRARY         ${GDK_LIBRARY_RELEASE})
  set(GDK_LIBRARY_DEBUG   ${GDK_LIBRARY_RELEASE})
endif()

set(GDK_LIBRARY ${GDK_LIBRARY} CACHE FILEPATH "GDK library")
set(GDK_INCLUDE_DIR ${GDK_INCLUDE_DIR} CACHE PATH "GDK include directory")

mark_as_advanced(
  GDK_LIBRARY_DIRS
  GDK_LIBRARY
  GDK_LIBRARY_DEBUG
  GDK_LIBRARY_RELEASE
  GDK_INCLUDE_DIR
)

foreach(lib IN LISTS GDK_LIBRARY)
  get_filename_component(path "${lib}" PATH)
  list(APPEND GDK_LIBRARY_DIRS "${path}")
endforeach()

if(GDK_LIBRARY_DIRS)
  list(REMOVE_DUPLICATES GDK_LIBRARY_DIRS)
endif()

set(GDK_LIBRARIES ${GDK_LIBRARY})
set(GDK_INCLUDE_DIRS ${GDK_INCLUDE_DIR})

mark_as_advanced(
  GDK_LIBRARIES
  GDK_INCLUDE_DIRS
)

function(get_version_string var text)
  string(REGEX MATCH "#define[\\t ]+SAMPGDK_VERSION_STRING[\\t ]+\".*\""
         match "${text}")
  if(match)
    string(REGEX REPLACE ".*\"(.*)\"" "\\1" version_string "${match}")
    set(${var} ${version_string} PARENT_SCOPE)
  endif()
endfunction()

if(GDK_INCLUDE_DIR)
  file(READ "${GDK_INCLUDE_DIR}/sampgdk/version.h" text)
  get_version_string(GDK_VERSION_STRING "${text}")
endif()

find_package_handle_standard_args(GDK REQUIRED_VARS GDK_INCLUDE_DIRS
                                                    GDK_LIBRARY_DIRS
                                                    GDK_LIBRARIES
                                  VERSION_VAR GDK_VERSION_STRING)
