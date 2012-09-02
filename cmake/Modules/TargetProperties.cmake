# This module provides the following functions:
#
#   add_target_definitions(
#     <target> [def1 [def2 [def3 ...]]]
#   )
#
#   add_target_compile_flags(
#     <target> [flag1 [flag2 [flag3 ...]]]
#   )
#
#   add_target_link_flags(
#     <target> [flag1 [flag2 [flag3 ...]]]
#   )

cmake_minimum_required(VERSION 2.8.6)

function(add_target_definitions target)
	foreach(arg IN LISTS ARGN)
		set_property(TARGET "${target}" APPEND PROPERTY "COMPILE_DEFINITIONS" "${arg}")
	endforeach()
endfunction()

function(add_target_compile_flags target)
	foreach(arg IN LISTS ARGN)
		set_property(TARGET "${target}" APPEND_STRING PROPERTY "COMPILE_FLAGS" " ${arg}")
	endforeach()
endfunction()

function(add_target_link_flags target)
	foreach(arg IN LISTS ARGN)
		set_property(TARGET "${target}" APPEND_STRING PROPERTY "LINK_FLAGS" " ${arg}")
	endforeach()
endfunction()

