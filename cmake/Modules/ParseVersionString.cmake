# parse_version_string - parse a version string.
# 
# Usage:
#   parse_version_string(string, list)
# 
# The string should be in one of the following forms:
#   a.b.c.d
#   a.b.c
#   a.b
# where a, b, c, d are numbers.
#
# The last component of "list" is set to any unmatched text that follows
# the last version number.
function(parse_version_string input output)
	if(input MATCHES "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+")
		string(REGEX REPLACE "([0-9])+\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)"
			"\\1;\\2;\\3;\\4" version ${input})
	elseif(input MATCHES "[0-9]+\\.[0-9]+\\.[0-9]+")
		string(REGEX REPLACE "([0-9])+\\.([0-9]+)\\.([0-9]+)"
			"\\1;\\2;\\3" version ${input})
	elseif(input MATCHES "[0-9]+\\.[0-9]+")
		string(REGEX REPLACE "([0-9])+\\.([0-9]+)"
			"\\1;\\2" version ${input})
	elseif(input MATCHES "[0-9]+")
		string(REGEX REPLACE "([0-9])+"
			"\\1" version ${input})
	endif()
	set(${output} ${version} PARENT_SCOPE)
endfunction()
