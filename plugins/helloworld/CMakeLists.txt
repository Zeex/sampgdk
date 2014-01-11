project(helloworld)
cmake_minimum_required(VERSION 2.8)

include(GroupTargetSources)
include(Plugin)

find_package(SDK REQUIRED)

if(MSVC)
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

include_directories(${SDK_INCLUDE_DIR})

add_plugin(helloworld
  "helloworld.cpp"
  "helloworld.def"
  "${SDK_INCLUDE_DIR}/amxplugin.cpp"
)

group_target_sources(helloworld)

target_link_libraries(helloworld "sampgdk")
if(SAMPGDK_STATIC)
  target_link_libraries(helloworld "subhook")
endif()
