include(FindPackageHandleStandardArgs)

find_path(SAMPSDK_DIR
  NAMES plugin.h
        plugincommon.h
  HINTS ${SAMP_SDK_ROOT}
        ENV SAMP_SDK_ROOT
  PATH_SUFFIXES sdk SDK
  DOC "Path to SA-MP plugin SDK"
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PATH
)

set(SAMPSDK_INCLUDE_DIR ${SAMPSDK_DIR})

mark_as_advanced(
  SAMPSDK_DIR
  SAMPSDK_INCLUDE_DIR
)

find_package_handle_standard_args(SAMPSDK
  REQUIRED_VARS SAMPSDK_DIR
                SAMPSDK_INCLUDE_DIR
)
