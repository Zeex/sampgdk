set(SAMPGDK_RC_FILE  "sampgdk.rc")

configure_file("${SAMPGDK_RC_FILE}.in"
               "${SAMPGDK_RC_FILE}" @ONLY)

set(SAMPGDK_DEF_FILE "sampgdk.def")
set(SAMPGDK_SYM_FILE "sampgdk.sym")

sampgdk_add_sources(
	"core.api"
	"core.c"
	"a_objects.c"
	"a_players.c"
	"a_samp.c"
	"a_vehicles.c"
	"version.api"
	"version.c"
)

if(WIN32)
	sampgdk_add_sources(
		"${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_RC_FILE}"
		"${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_DEF_FILE}"
	)
elseif(UNIX)
	sampgdk_add_sources(
		"${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_SYM_FILE}"
	)
endif()

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY INCLUDE_DIRECTORIES
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory("private")
add_subdirectory("sdk")

# Export theese two variables to the parent scope for add_custom_command().
#
# I would define the custom command in this directory but targets recognize
# custom command's output files only for those commands that are defined
# in the current directory (the CMake devs said it's not a bug...).
if(WIN32)
	set(SAMPGDK_DEF_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_DEF_FILE}" PARENT_SCOPE)
elseif(UNIX)
	set(SAMPGDK_SYM_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_DEF_FILE}" PARENT_SCOPE)
endif()