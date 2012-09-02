# This module provides the following functions:
#
#   add_target_definitions(
#     <target> [def1 [def2 [def3 ...]]]
#   )

cmake_minimum_required(VERSION 2.8)

function(add_target_definitions target)
	foreach(arg IN LISTS ARGN)
		set_property(TARGET "${target}" APPEND PROPERTY "COMPILE_DEFINITIONS" "${arg}")
	endforeach()
endfunction()

