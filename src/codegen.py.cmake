# Work around unability to set environment variables for custom commands.

foreach(path IN LISTS PYTHONPATH)
	if(WIN32)
		set(ENV{PYTHONPATH} "${path};$ENV{PYTHONPATH}")
	else()
		set(ENV{PYTHONPATH} "${path}:$ENV{PYTHONPATH}")
	endif()
endforeach()

if(NOT PYTHON)
	find_package(PythonInterp 2.7 REQUIRED)
	set(PYTHON ${PYTHON_EXECUTABLE})
endif()

if(CODEGEN_IDL_FILE)
	list(APPEND ARGS "--idl=${CODEGEN_IDL_FILE}")
endif()
if(CODEGEN_HEADER_FILE)
	list(APPEND ARGS "--header=${CODEGEN_HEADER_FILE}")
endif()
if(CODEGEN_SOURCE_FILE)
	list(APPEND ARGS "--source=${CODEGEN_SOURCE_FILE}")
endif()
if(CODEGEN_EXPORTS_FILE)
	list(APPEND ARGS "--exports=${CODEGEN_EXPORTS_FILE}")
endif()

execute_process(COMMAND ${PYTHON} "${CMAKE_SOURCE_DIR}/codegen.py" "--all" ${ARGS}
	ERROR_VARIABLE PYTHON_ERRORS OUTPUT_VARIABLE PYTHON_OUTPUT)

if(OUTPUT_VARIABLE)
	message(${PYTHON_OUTPUT})
endif()
if(PYTHON_ERRORS)
	message(FATAL_ERROR ${PYTHON_ERRORS})
endif()
