project(helloworld)

cmake_minimum_required(VERSION 2.8)

include(AmxConfig)
include(Plugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_plugin(ufs
  callbacks.cpp
  plugin.cpp
  plugin.h
  script.cpp
  script.h
  ufs.cpp
  ufs.h
  ufs-plugin.def
  ufs-plugin.cpp
  ${SDK_INCLUDE_DIR}/amxplugin.cpp
)

target_link_libraries(ufs sampgdk)
