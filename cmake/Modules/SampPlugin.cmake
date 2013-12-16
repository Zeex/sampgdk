# SampPlugin.cmake
#
# Functions:
#   add_samp_plugin(name [sources...])
#
# Supported platforms:
#   Windows
#   Linux
#
# Supported compilers:
#   GCC
#   MinGW
#   Microsoft Visual C++

function(add_samp_plugin name)
  add_library(${name} MODULE ${ARGN})

  set_target_properties(${name} PROPERTIES PREFIX "")

  if(CMAKE_COMPILER_IS_GNUCC)
    set_property(TARGET ${name} APPEND_STRING PROPERTY COMPILE_FLAGS " -m32")
    set_property(TARGET ${name} APPEND_STRING PROPERTY LINK_FLAGS    " -m32")
  endif()

  if(WIN32 AND CMAKE_COMPILER_IS_GNUCC)
    set_property(TARGET ${name} APPEND_STRING PROPERTY
                 LINK_FLAGS " -Wl,--enable-stdcall-fixup")
  endif()

  if(UNIX AND NOT WIN32)
    set_property(TARGET ${name} APPEND PROPERTY COMPILE_DEFINITIONS "LINUX")
  endif()
endfunction()
