# Find sampgdk 3.x library and headers.
#
# Defined variables:
#
#   SampGdk3_FOUND
#   SampGdk3_LIBRARY_DIRS
#   SampGdk3_LIBRARY (cached)
#   SampGdk3_LIBRARY_DEBUG
#   SampGdk3_LIBRARY_RELEASE
#   SampGdk3_LIBRARIES
#   SampGdk3_INCLUDE_DIR (cached)
#   SampGdk3_INCLUDE_DIRS
#   SampGdk3_VERSION
#   SampGdk3_VERSION_MAJOR
#   SampGdk3_VERSION_MINOR
#   SampGdk3_VERSION_PATCH
#   SampGdk3_VERSION_TWEAK
#
# Using this module:
#
#   find_package(SampGdk3 VERSION 3.2.1)
#   if(SampGdk3_FOUND)
#     include_directories(${SampGdk3_INCLUDE_DIRS})
#     target_link_libraries(foo ${Sampgdk_LIBRARIES})
#   endif()
  
find_path(SampGdk3_INCLUDE_DIR NAMES "sampgdk/version.h")

find_library(SampGdk3_LIBRARY_DEBUG NAMES "sampgdk3_d" "sampgdk_d")
find_library(SampGdk3_LIBRARY_RELEASE NAMES "sampgdk3" "sampgdk")

if(SampGdk3_LIBRARY_DEBUG AND SampGdk3_LIBRARY_RELEASE)
  if(CMAKE_CONFIGURATIONS OR CMAKE_BUILD_TYPE)
    set(SampGdk3_LIBRARY debug ${SampGdk3_LIBRARY_DEBUG} optimized ${SampGdk3_LIBRARY_RELEASE})
  else()
    set(SampGdk3_LIBRARY ${SampGdk3_LIBRARY_RELEASE})
  endif()
endif()

if(SampGdk3_LIBRARY_DEBUG AND NOT SampGdk3_LIBRARY_RELEASE)
  set(SampGdk3_LIBRARY         ${SampGdk3_LIBRARY_DEBUG})
  set(SampGdk3_LIBRARY_RELEASE ${SampGdk3_LIBRARY_DEBUG})
endif()

if(SampGdk3_LIBRARY_RELEASE AND NOT SampGdk3_LIBRARY_DEBUG)
  set(SampGdk3_LIBRARY         ${SampGdk3_LIBRARY_RELEASE})
  set(SampGdk3_LIBRARY_DEBUG   ${SampGdk3_LIBRARY_RELEASE})
endif()

set(SampGdk3_LIBRARY ${SampGdk3_LIBRARY} CACHE FILEPATH "SampGdk3 library")
set(SampGdk3_INCLUDE_DIR ${SampGdk3_INCLUDE_DIR} CACHE PATH "SampGdk3 include directory")

mark_as_advanced(
  SampGdk3_LIBRARY_DIRS
  SampGdk3_LIBRARY
  SampGdk3_LIBRARY_DEBUG
  SampGdk3_LIBRARY_RELEASE
  SampGdk3_INCLUDE_DIR
)

foreach(lib IN LISTS SampGdk3_LIBRARY)
  get_filename_component(path "${lib}" PATH)
  list(APPEND SampGdk3_LIBRARY_DIRS "${path}")
endforeach()

if(SampGdk3_LIBRARY_DIRS)
  list(REMOVE_DUPLICATES SampGdk3_LIBRARY_DIRS)
endif()

set(SampGdk3_LIBRARIES ${SampGdk3_LIBRARY})
set(SampGdk3_INCLUDE_DIRS ${SampGdk3_INCLUDE_DIR})

mark_as_advanced(
  SampGdk3_LIBRARIES
  SampGdk3_INCLUDE_DIRS
)

function(get_version name text)
  string(REGEX MATCH "#define[   ]+SAMPGDK_VERSION_${name}[   ]+[0-9]+" match "${text}")
  if(match)
    string(REGEX REPLACE ".* ([0-9]+)" "\\1" number "${match}")
    set(SampGdk3_VERSION_${name} ${number} PARENT_SCOPE)
  endif()
endfunction()

if(SampGdk3_INCLUDE_DIR)
  file(READ "${SampGdk3_INCLUDE_DIR}/sampgdk/version.h" text)
  
  get_version(MAJOR "${text}")
  get_version(MINOR "${text}")
  get_version(PATCH "${text}")
  get_version(TWEAK "${text}")
  
  if(NOT SampGdk3_VERSION_TWEAK OR SampGdk3_VERSION_TWEAK EQUAL 0)
    if(NOT SampGdk3_VERSION_PATCH OR SampGdk3_VERSION_PATCH EQUAL 0)
      set(SampGdk3_VERSION "${SampGdk3_VERSION_MAJOR}.${SampGdk3_VERSION_MINOR}")
    else()
      set(SampGdk3_VERSION "${SampGdk3_VERSION_MAJOR}.${SampGdk3_VERSION_MINOR}.${SampGdk3_VERSION_PATCH}")
    endif()
  else()
    set(SampGdk3_VERSION "${SampGdk3_VERSION_MAJOR}.${SampGdk3_VERSION_MINOR}.${SampGdk3_VERSION_PATCH}.${SampGdk3_VERSION_TWEAK}")
  endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SampGdk3
  REQUIRED_VARS SampGdk3_INCLUDE_DIRS SampGdk3_LIBRARY_DIRS SampGdk3_LIBRARIES
  VERSION_VAR SampGdk3_VERSION
)
