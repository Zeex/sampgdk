set(SAMPGDK_INIT_FILE "init.c")

sampgdk_add_sources(
	"amx-stack.c"
	"amx-stack.h"
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
		file(APPEND ${file} "extern int ${module}_init(void);\n")
	endforeach()
	file(APPEND ${file} "\nint module_init(void) {\n"
	                    "\tint error;\n")
	foreach(module IN LISTS SAMPGDK_INIT_MODULES)
		file(APPEND ${file} "\tif ((error = ${module}_init()) < 0)\n"
		                    "\t\treturn error;\n")
	endforeach()
	file(APPEND ${file} "\treturn 0;\n"
	                    "}\n\n")
endmacro()

sampgdk_write_module_init("${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}")

macro(sampgdk_write_module_cleanup file)
	foreach(module IN LISTS SAMPGDK_INIT_MODULES)
		file(APPEND ${file} "extern void ${module}_cleanup(void);\n")
	endforeach()
	file(APPEND ${file} "\nvoid module_cleanup(void) {\n")
	foreach(module IN LISTS SAMPGDK_INIT_MODULES)
		file(APPEND ${file} "\t${module}_cleanup();\n")
	endforeach()
	file(APPEND ${file} "}\n\n")
endmacro()

sampgdk_write_module_cleanup("${CMAKE_CURRENT_BINARY_DIR}/${SAMPGDK_INIT_FILE}")