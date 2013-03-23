set(SUBHOOK_STATIC TRUE)
add_subdirectory("subhook")

file(RELATIVE_PATH folder ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET subhook PROPERTY FOLDER "${folder}")