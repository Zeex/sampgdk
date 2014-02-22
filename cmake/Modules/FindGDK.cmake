include(FindPackageHandleStandardArgs)

find_package(SAMPGDK QUIET CONFIG NAMES SAMPGDK)

set(GDK_VERSION     ${SAMPGDK_VERSION})
set(GDK_INCLUDE_DIR ${SAMPGDK_INCLUDE_DIR})
set(GDK_LIBRARY_DIR ${SAMPGDK_LIBRARY_DIR})

set(GDK_INCLUDE_DIRS ${GDK_INCLUDE_DIR})
set(GDK_LIBRARY_DIRS ${GDK_LIBRARY_DIR})

find_package_handle_standard_args(GDK REQUIRED_VARS GDK_INCLUDE_DIRS
                                                    GDK_LIBRARY_DIRS
                                      VERSION_VAR GDK_VERSION)
