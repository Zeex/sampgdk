cmake_minimum_required(VERSION 2.8)

project(helloworld)

set(PLUGIN_NAME "helloworld")
set(PLUGIN_SOURCES "helloworld.cpp")

include(SampPlugin)

target_link_libraries(${PLUGIN_TARGET} sampgdk)
