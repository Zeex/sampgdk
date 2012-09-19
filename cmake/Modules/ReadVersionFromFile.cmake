# read_version_from_file() reads a version string from a file and 
# splits it into four components (major.minor.patch.tweak) using
# the ParseVersionString module.

include(ParseVersionString)

function(read_version_from_file filename string_var major_var minor_var patch_var tweak_var)
	file(STRINGS ${filename} version_string LIMIT_COUNT 1)

	set(${string_var} ${version_string} PARENT_SCOPE)

	set(major 0)
	set(minor 0)
	set(patch 0)
	set(tweak 0)

	parse_version_string(${version_string} version)

	list(LENGTH version length)
	if(length GREATER 0)
		list(GET version 0 major)
	endif()
	if(length GREATER 1)
		list(GET version 1 minor)
	endif()
	if(length GREATER 2)
		list(GET version 2 patch)
	endif()
	if(length GREATER 3)
		list(GET version 3 tweak)
	endif()

	set(${major_var} ${major} PARENT_SCOPE)
	set(${minor_var} ${minor} PARENT_SCOPE)
	set(${patch_var} ${patch} PARENT_SCOPE)
	set(${tweak_var} ${tweak} PARENT_SCOPE)
endfunction()

