# Try to find Sampgdk3
#
# Defined variables:
# - Sampgdk3_FOUND
# - Sampgdk3_INCLUDE_DIRS
# - Sampgdk3_LIBRARIES
	
find_path(Sampgdk3_INCLUDE_DIR NAMES sampgdk/a_samp.h)
find_library(Sampgdk3_LIBRARY NAMES sampgdk3 libsampgdk3)

set(Sampgdk3_LIBRARIES ${Sampgdk3_LIBRARY})
set(Sampgdk3_INCLUDE_DIRS ${Sampgdk3_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sampgdk3 DEFAULT_MSG Sampgdk3_LIBRARY Sampgdk3_INCLUDE_DIR)

mark_as_advanced(Sampgdk3_LIBRARY Sampgdk3_INCLUDE_DIR)
