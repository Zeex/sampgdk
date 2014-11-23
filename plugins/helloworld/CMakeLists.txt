include(AmxConfig)
include(Plugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_plugin(helloworld
  helloworld.cpp
  helloworld.def
  ${SDK_INCLUDE_DIR}/amxplugin.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(helloworld PRIVATE -Wno-attributes)
endif()

target_link_libraries(helloworld sampgdk)
