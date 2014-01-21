project(helloworld)

cmake_minimum_required(VERSION 2.8)

include(Plugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_plugin(helloworld
  helloworld.cpp
  helloworld.def
  ${SDK_INCLUDE_DIR}/amxplugin.cpp
)

target_link_libraries(helloworld sampgdk)
