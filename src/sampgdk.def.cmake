cmake_minimum_required(VERSION 2.8)

set(def_path "${CMAKE_SOURCE_DIR}/sampgdk.def")
if(EXISTS ${def_path})
	file(REMOVE ${def_path})
endif()

file(GLOB_RECURSE files "${CMAKE_SOURCE_DIR}/*.exports")

file(APPEND ${def_path} "EXPORTS\n")
foreach(file IN LISTS files)
	file(STRINGS ${file} exports)
	foreach(name IN LISTS exports)
		file(APPEND ${def_path} "\t${name}\n")
	endforeach()
endforeach()
