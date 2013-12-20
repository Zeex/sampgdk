sampgdk_add_libraries("subhook")

if(SAMPGDK_STATIC)
  set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" APPEND PROPERTY
               COMPILE_DEFINITIONS "SUBHOOK_STATIC")
else()
  set(SUBHOOK_STATIC TRUE)
endif()

add_subdirectory("subhook")

file(RELATIVE_PATH folder ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET subhook PROPERTY FOLDER "${folder}")