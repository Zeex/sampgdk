file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/init.c "")

sampgdk_add_sources(
  amx.c
  amx.h
  amxhooks.c
  array.c
  array.h
  callback.c
  callback.h
  fakeamx.c
  fakeamx.h
  hook.c
  hook.h
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
  types.h
)

sampgdk_add_init_gen(sampgdk_init ${CMAKE_CURRENT_SOURCE_DIR}/init.list
                                  ${CMAKE_CURRENT_BINARY_DIR}/init.c)
