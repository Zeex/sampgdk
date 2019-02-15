set(PYTHONPATH
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
  string(REPLACE ";" ":" PYTHONPATH "${PYTHONPATH}")
endif()

configure_file(python_wrapper.py.in python_wrapper.py @ONLY)
