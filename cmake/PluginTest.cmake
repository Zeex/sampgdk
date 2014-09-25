# PluginTest - add tests for SA-MP plugins.
# 
# This module reuires the samp-server-cli script to be present in PATH in
# order to be able to run the tests. The script can be downloaded here:
# 
#   https://github.com/Zeex/samp-server-cli
# 
# Additionally the SAMP_SERVER_ROOT environment variable must be defined and
# must point to the SA-MP server's root directory.

include(CMakeParseArguments)

function(add_plugin_test)
  set(name "${ARGV0}")

  set(options TARGET OUT_FILE SCRIPT TIMEOUT CONFIG)
  cmake_parse_arguments(ARG "" "${options}" "" ${ARGN})

  if(ARG_SCRIPT)
    list(APPEND args --gamemode ${ARG_SCRIPT})
  endif()

  if(ARG_TIMEOUT)
    list(APPEND args --timeout ${ARG_TIMEOUT})
  endif()

  if(ARG_CONFIG)
    list(APPEND args --exec ${ARG_CONFIG})
  endif()

  if(WIN32)
    set(command samp-server-cli.bat)
  else()
    set(command samp-server-cli)
  endif()

  add_test(NAME ${name} COMMAND ${command} ${args} --output
           --plugin $<TARGET_FILE:${ARG_TARGET}>)

  set(AMX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${name})
  set_tests_properties(${name} PROPERTIES ENVIRONMENT AMX_PATH=${AMX_PATH})

  if(ARG_OUT_FILE)
    file(READ ${ARG_OUT_FILE} output)
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION ${output})
  endif()
endfunction()
