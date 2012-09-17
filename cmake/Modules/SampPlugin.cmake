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

include(AmxConfig)

function(add_samp_plugin name)
	add_library(${name} MODULE ${ARGN})

	set_target_properties(${name} PROPERTIES PREFIX "")

	if(CMAKE_COMPILER_IS_GNUCC)
		set_property(TARGET ${name} APPEND PROPERTY COMPILE_FLAGS "-m32")
		set_property(TARGET ${name} APPEND PROPERTY LINK_FLAGS    "-m32")
	endif()

	if(UNIX AND NOT WIN32)
		set_property(TARGET ${name} APPEND PROPERTY COMPILE_DEFINITIONS "LINUX")
	endif()
endfunction()
