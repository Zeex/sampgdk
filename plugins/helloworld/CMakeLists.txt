project(helloworld)
cmake_minimum_required(VERSION 2.8)

include(GroupTargetSources)
include(Plugin)

if(MSVC)
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_plugin(helloworld
  "helloworld.cpp"
  "helloworld.def"
)

group_target_sources(helloworld)

target_link_libraries(helloworld "sampgdk")
if(SAMPGDK_STATIC)
  target_link_libraries(helloworld "subhook")
endif()
