#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #undef CreateMenu
  #undef DestroyMenu
  #undef GetTickCount
  #undef KillTimer
  #undef SelectObject
  #undef SetTimer
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#else
  #define _GNU_SOURCE
#endif
