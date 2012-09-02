# This module provides the following functions:
#
#   add_target_compile_flags(
#     <target> [flag1 [flag2 [flag3 ...]]]
#   )

cmake_minimum_required(VERSION 2.8.6)

function(add_target_compile_flags target)
	foreach(arg IN LISTS ARGN)
		set_property(TARGET "${target}" APPEND_STRING PROPERTY "COMPILE_FLAGS" " ${arg}")
	endforeach()
endfunction()

