include(AMXConfig)
include(AddSAMPPlugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_samp_plugin(helloworld
  helloworld.cpp
  helloworld.def
  ${SAMPSDK_DIR}/amxplugin.cpp
)

target_link_libraries(helloworld sampgdk)
