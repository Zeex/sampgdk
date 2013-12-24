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
  "bool.h"
  "core.h"
  "core.hpp"
  "export.h"
  "platform.h"
  "sdk.h"
  "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_VERSION_FILE}"
)
