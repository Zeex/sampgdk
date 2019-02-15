include(AMXConfig)
include(AddSAMPPlugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_samp_plugin(blank
  ${CMAKE_CURRENT_BINARY_DIR}/blank.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/blank.def
  ${SAMPSDK_DIR}/amxplugin.cpp
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/blank.cpp
         ${CMAKE_CURRENT_BINARY_DIR}/blank.def
  COMMAND ${PYTHON_EXECUTABLE}
          ${CMAKE_BINARY_DIR}/scripts/python_wrapper.py
          ${CMAKE_CURRENT_SOURCE_DIR}/generate_blank_plugin.py
          --idl ${CMAKE_SOURCE_DIR}/lib/sampgdk/a_samp.idl
          --source ${CMAKE_CURRENT_BINARY_DIR}/blank.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_blank_plugin.py)

target_link_libraries(blank sampgdk)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/blank.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/blank.def
  DESTINATION share/sampgdk/plugins/blank)
