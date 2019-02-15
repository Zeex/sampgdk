include(AMXConfig)
include(AddSAMPPlugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(UFS_SOURCES
  plugin.cpp
  plugin.h
  script.cpp
  script.h
  ufs.cpp
  ufs.h
  ufs-plugin.cpp
  ${SAMPSDK_DIR}/amxplugin.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
)

if(WIN32)
  list(APPEND UFS_SOURCES
    ufs-plugin.def
    ${CMAKE_CURRENT_BINARY_DIR}/ufs.def
  )
endif()

add_samp_plugin(ufs ${UFS_SOURCES})

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
         ${CMAKE_CURRENT_BINARY_DIR}/callbacks.def
  COMMAND ${PYTHON_EXECUTABLE}
          ${CMAKE_BINARY_DIR}/scripts/python_wrapper.py
          ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py
          --idl ${CMAKE_SOURCE_DIR}/lib/sampgdk/a_samp.idl
          --source ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ufs.def
    COMMAND ${PYTHON_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/scripts/cat.py
            ${CMAKE_CURRENT_BINARY_DIR}/ufs.def
            ${CMAKE_CURRENT_SOURCE_DIR}/ufs-plugin.def
            ${CMAKE_CURRENT_BINARY_DIR}/callbacks.def
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ufs-plugin.def
            ${CMAKE_CURRENT_BINARY_DIR}/callbacks.def)

target_link_libraries(ufs sampgdk)
