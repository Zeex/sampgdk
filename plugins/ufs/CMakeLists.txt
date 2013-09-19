project(ufs)
cmake_minimum_required(VERSION 2.8)

include(SampPlugin)
include(GroupTargetSources)

if(MSVC)
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_samp_plugin(ufs
  "callbacks.cpp"
  "plugin.cpp"
  "plugin.h"
  "script.cpp"
  "script.h"
  "ufs.cpp"
  "ufs.h"
  "ufs-plugin.def"
  "ufs-plugin.cpp"
)

group_target_sources(ufs)
target_link_libraries(ufs "sampgdk")
