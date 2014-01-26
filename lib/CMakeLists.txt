sampgdk_add_libraries(subhook)

set(SUBHOOK_STATIC TRUE)
smapgdk_add_subproject(subhook)

# This should rather be set by subhook itself.
target_compile_definitions(subhook INTERFACE SUBHOOK_STATIC)
target_include_directories(subhook INTERFACE subhook)
