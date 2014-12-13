include(AmxConfig)
include(Plugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_plugin(ufs
  ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
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

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
                   COMMAND ${PYTHON_EXECUTABLE}
                           ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py
                           --idl ${CMAKE_SOURCE_DIR}/lib/sampgdk/a_samp.idl
                           --source ${CMAKE_CURRENT_BINARY_DIR}/callbacks.cpp
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_callbacks.py)

target_link_libraries(ufs sampgdk)
