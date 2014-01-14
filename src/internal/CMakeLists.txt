file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/init.c "")

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

sampgdk_add_init_gen(sampgdk_init ${CMAKE_CURRENT_SOURCE_DIR}/init.list
                                  ${CMAKE_CURRENT_BINARY_DIR}/init.c)
