set(SAMPGDK_VERSION_FILE version.h)

configure_file(${SAMPGDK_VERSION_FILE}.in
               ${SAMPGDK_VERSION_FILE} @ONLY)

sampgdk_add_headers(
  a_http.h
  a_objects.h
  a_players.h
  a_samp.h
  a_vehicles.h
  bool.h
  core.h
  export.h
  interop.h
  platform.h
  sdk.h
  ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_VERSION_FILE}
)
