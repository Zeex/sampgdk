# Find GDK 4.x library and headers.
# 
# Defined variables:
# 
#   GDK4_FOUND
#   GDK4_LIBRARY_DIRS
#   GDK4_LIBRARY (cached)
#   GDK4_LIBRARY_DEBUG
#   GDK4_LIBRARY_RELEASE
#   GDK4_LIBRARIES
#   GDK4_INCLUDE_DIR (cached)
#   GDK4_INCLUDE_DIRS
#   GDK4_VERSION
#   GDK4_VERSION_MAJOR
#   GDK4_VERSION_MINOR
#   GDK4_VERSION_PATCH
#   GDK4_VERSION_TWEAK
# 
# Using this module:
# 
#   find_package(GDK4 VERSION 3.2.1)
#   if(GDK4_FOUND)
#     include_directories(${GDK4_INCLUDE_DIRS})
#     target_link_libraries(foo ${GDK4_LIBRARIES})
#   endif()

include(FindPackageHandleStandardArgs)

find_path(GDK4_INCLUDE_DIR NAMES "sampgdk/version.h")

find_library(GDK4_LIBRARY_DEBUG   NAMES "sampgdk4_d" "sampgdk_d")
find_library(GDK4_LIBRARY_RELEASE NAMES "sampgdk4"   "sampgdk")

if(GDK4_LIBRARY_DEBUG AND GDK4_LIBRARY_RELEASE)
  if(CMAKE_CONFIGURATIONS OR CMAKE_BUILD_TYPE)
    set(GDK4_LIBRARY debug     ${GDK4_LIBRARY_DEBUG}
                     optimized ${GDK4_LIBRARY_RELEASE})
  else()
    set(GDK4_LIBRARY ${GDK4_LIBRARY_RELEASE})
  endif()
endif()

if(GDK4_LIBRARY_DEBUG AND NOT GDK4_LIBRARY_RELEASE)
  set(GDK4_LIBRARY         ${GDK4_LIBRARY_DEBUG})
  set(GDK4_LIBRARY_RELEASE ${GDK4_LIBRARY_DEBUG})
endif()

if(GDK4_LIBRARY_RELEASE AND NOT GDK4_LIBRARY_DEBUG)
  set(GDK4_LIBRARY         ${GDK4_LIBRARY_RELEASE})
  set(GDK4_LIBRARY_DEBUG   ${GDK4_LIBRARY_RELEASE})
endif()

set(GDK4_LIBRARY ${GDK4_LIBRARY} CACHE FILEPATH "GDK library")
set(GDK4_INCLUDE_DIR ${GDK4_INCLUDE_DIR} CACHE PATH "GDK include directory")

mark_as_advanced(
  GDK4_LIBRARY_DIRS
  GDK4_LIBRARY
  GDK4_LIBRARY_DEBUG
  GDK4_LIBRARY_RELEASE
  GDK4_INCLUDE_DIR
)

foreach(lib IN LISTS GDK4_LIBRARY)
  get_filename_component(path "${lib}" PATH)
  list(APPEND GDK4_LIBRARY_DIRS "${path}")
endforeach()

if(GDK4_LIBRARY_DIRS)
  list(REMOVE_DUPLICATES GDK4_LIBRARY_DIRS)
endif()

set(GDK4_LIBRARIES ${GDK4_LIBRARY})
set(GDK4_INCLUDE_DIRS ${GDK4_INCLUDE_DIR})

mark_as_advanced(
  GDK4_LIBRARIES
  GDK4_INCLUDE_DIRS
)

function(get_version_string var text)
  string(REGEX MATCH "#define[\\t ]+SAMPGDK_VERSION_STRING[\\t ]+\".*\""
         match "${text}")
  if(match)
    string(REGEX REPLACE ".*\"(.*)\"" "\\1" version_string "${match}")
    set(${var} ${version_string} PARENT_SCOPE)
  endif()
endfunction()

if(GDK4_INCLUDE_DIR)
  file(READ "${GDK4_INCLUDE_DIR}/sampgdk/version.h" text)
  get_version_string(GDK4_VERSION_STRING "${text}")
endif()

find_package_handle_standard_args(GDK4 REQUIRED_VARS GDK4_INCLUDE_DIRS
                                                     GDK4_LIBRARY_DIRS
                                                     GDK4_LIBRARIES
                                  VERSION_VAR GDK4_VERSION_STRING)
