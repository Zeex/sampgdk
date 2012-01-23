# check_header, check_header_cxx - Check if a header file exists and 
# define HAVE_<header_in_upper_case> if found.

include(CheckIncludeFile)
include(CheckIncludeFileCXX)

function(check_header _hdrname)
	string(TOUPPER ${_hdrname} _hdrname_upper)
	string(REGEX REPLACE "[\\./]" "_" define ${_hdrname_upper})
	set(define "HAVE_${define}")
	check_include_file(${_hdrname} ${define})
	if(${define})
		add_definitions(-D${define})
	endif()
endfunction()

function(check_header_cxx _hdrname)
	string(TOUPPER ${_hdrname} _hdrname_upper)
	string(REGEX REPLACE "[\\./]" "_" define ${_hdrname_upper})
	set(define "HAVE_${define}")
	check_include_file_cxx(${_hdrname} ${define})
	if(${define})
		add_definitions(-D${define})
	endif()
endfunction()
