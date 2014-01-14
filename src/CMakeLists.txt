add_subdirectory(internal)

set(SAMPGDK_RC_FILE sampgdk.rc)

configure_file(${SAMPGDK_RC_FILE}.in
               ${SAMPGDK_RC_FILE} @ONLY)

set(SAMPGDK_DEF_FILE sampgdk.def)
set(SAMPGDK_SYM_FILE sampgdk.sym)

sampgdk_add_sources(
  a_samp.c
  core.api
  core.c
  version.api
  version.c
)

if(WIN32)
  sampgdk_add_sources(${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_RC_FILE}
                      ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_DEF_FILE})
elseif(UNIX)
  sampgdk_add_sources(${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_SYM_FILE})
endif()

# Add current directory to the include path so that generated code will be
# able to use the private headers.
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY
             INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

# Export theese two variables to the parent scope for add_custom_command().
#
# I would define the custom command in this directory but targets recognize
# custom command's output files only for those commands that are defined
# in the current directory (the CMake devs said it's not a bug...).
if(WIN32)
  set(SAMPGDK_DEF_FILE ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_DEF_FILE} PARENT_SCOPE)
elseif(UNIX)
  set(SAMPGDK_SYM_FILE ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_SYM_FILE} PARENT_SCOPE)
endif()
