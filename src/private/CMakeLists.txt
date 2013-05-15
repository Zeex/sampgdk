set(SAMPGDK_INIT_FILE "init.c")

sampgdk_add_sources(
  "amx.h"
  "arg.c"
  "arg.h"
  "array.c"
  "array.h"
  "call.asm"
  "call.h"
  "callback.c"
  "callback.h"
  "fakeamx.c"
  "fakeamx.h"
  "hooks.c"
  "init.h"
  "likely.h"
  "log.c"
  "log.h"
  "logprintf.c"
  "logprintf.h"
  "native.c"
  "native.h"
  "plugin.c"
  "plugin.h"
  "timer.c"
  "timer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}"
)

if(WIN32)
  sampgdk_add_sources(
    "plugin-win32.c"
    "timer-win32.c"
  )
elseif(UNIX)
  sampgdk_add_sources(
    "plugin-glibc.c"
    "timer-posix.c"
  )
endif()

file(REMOVE "${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}")

macro(sampgdk_write_module_init file)
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
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
    file(APPEND ${file} "extern void sampgdk_${module}_cleanup(void);\n")
  endforeach()
  file(APPEND ${file} "\nvoid sampgdk_module_cleanup(void) {\n")
  foreach(module IN LISTS SAMPGDK_INIT_MODULES)
    file(APPEND ${file} "  sampgdk_${module}_cleanup();\n")
  endforeach()
  file(APPEND ${file} "}\n\n")
endmacro()

sampgdk_write_module_cleanup("${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}")