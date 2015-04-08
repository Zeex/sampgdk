include(AMXConfig)
include(AddSAMPPlugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_samp_plugin(ufs
  ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
  plugin.cpp
  plugin.h
  script.cpp
  script.h
  ufs.cpp
  ufs.h
  ${CMAKE_CURRENT_BINARY_DIR}/ufs-plugin.def
  ufs-plugin.cpp
  ${SAMPSDK_DIR}/amxplugin.cpp
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ufs-plugin.def
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_CURRENT_SOURCE_DIR}/ufs-plugin.def
          ${CMAKE_CURRENT_BINARY_DIR}/ufs-plugin.def
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ufs-plugin.def)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
         ${CMAKE_CURRENT_BINARY_DIR}/callbacks.def
  COMMAND ${PYTHON_EXECUTABLE}
          ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py
          --idl ${CMAKE_SOURCE_DIR}/lib/sampgdk/a_samp.idl
          --source ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py
          ${CMAKE_CURRENT_BINARY_DIR}/ufs-plugin.def)

target_link_libraries(ufs sampgdk)
