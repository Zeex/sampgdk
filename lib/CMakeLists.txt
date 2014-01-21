sampgdk_add_libraries(subhook)

if(SAMPGDK_STATIC)
  set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY
               COMPILE_DEFINITIONS SUBHOOK_STATIC)
else()
  set(SUBHOOK_STATIC TRUE)
endif()

smapgdk_add_subproject(subhook)
