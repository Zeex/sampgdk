set(SAMPGDK_VERSION_FILE "version.h")

configure_file("${SAMPGDK_VERSION_FILE}.in"
               "${SAMPGDK_VERSION_FILE}" @ONLY)

sampgdk_add_headers(
  "a_http.h"
  "a_objects.h"
  "a_objects.hpp"
  "a_players.h"
  "a_players.hpp"
  "a_samp.h"
  "a_samp.hpp"
  "a_vehicles.h"
  "a_vehicles.hpp"
  "amx.h"
  "bool.h"
  "compatibility.h"
  "core.h"
  "core.hpp"
  "export.h"
  "platform.h"
  "plugin.h"
  "plugincommon.h"
  "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_VERSION_FILE}"
)

add_subdirectory("sdk")