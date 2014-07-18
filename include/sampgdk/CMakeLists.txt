set(SAMPGDK_VERSION_FILE version.h)

configure_file(${SAMPGDK_VERSION_FILE}.in
               ${SAMPGDK_VERSION_FILE} @ONLY)

sampgdk_add_headers(
  bool.h
  core.h
  export.h
  interop.h
  platform.h
  sdk.h
  types.h
  ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_VERSION_FILE}
)
