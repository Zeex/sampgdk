include(FindPackageHandleStandardArgs)

find_path(SDK_INCLUDE_DIR NAMES "plugin.h" "plugincommon.h"
          PATHS ENV "SAMP_SDK_DIR"
          PATH_SUFFIXES "SDK"
          DOC "Path to SA-MP plugin SDK"
          NO_SYSTEM_ENVIRONMENT_PATH
          NO_CMAKE_SYSTEM_PATH)

find_package_handle_standard_args(SDK REQUIRED_VARS SDK_INCLUDE_DIR)
