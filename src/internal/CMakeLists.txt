set(SAMPGDK_INIT_FILE init.c)

sampgdk_add_sources(
  amx.c
  amx.h
  array.c
  array.h
  callback.c
  callback.h
  fakeamx.c
  fakeamx.h
  hooks.c
  init.h
  likely.h
  log.c
  log.h
  logprintf.c
  logprintf.h
  native.c
  native.h
  param.c
  param.h
  plugin.c
  plugin.h
  timer.c
  timer.h
  utils.c
  utils.h
  ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}
)

if(WIN32)
  sampgdk_add_sources(
    plugin-win32.c
    timer-win32.c
  )
elseif(UNIX)
  sampgdk_add_sources(
    plugin-posix.c
    timer-posix.c
  )
endif()

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} APPEND PROPERTY INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE})

macro(sampgdk_ensure_module_name_ok module)
  if (module MATCHES "module")
    message(FATAL_ERROR "Module name cannot be \"module\"")
  endif()
endmacro()

macro(sampgdk_write_module_init file)
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
    sampgdk_ensure_module_name_ok(${module})
    file(APPEND ${file} "extern int sampgdk_${module}_init(void);\n")
  endforeach()
  file(APPEND ${file} "\nint sampgdk_module_init(void) {\n"
                      "  int error;\n")
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
    file(APPEND ${file} "  if ((error = sampgdk_${module}_init()) < 0) {\n"
                        "    return error;\n"
                        "  }\n")
  endforeach()
  file(APPEND ${file} "  return 0;\n"
                      "}\n\n")
endmacro()

sampgdk_write_module_init("${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}")

macro(sampgdk_write_module_cleanup file)
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
    sampgdk_ensure_module_name_ok(${module})
    file(APPEND ${file} "extern void sampgdk_${module}_cleanup(void);\n")
  endforeach()
  file(APPEND ${file} "\nvoid sampgdk_module_cleanup(void) {\n")
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
    file(APPEND ${file} "  sampgdk_${module}_cleanup();\n")
  endforeach()
  file(APPEND ${file} "}\n\n")
endmacro()

sampgdk_write_module_cleanup(${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE})
