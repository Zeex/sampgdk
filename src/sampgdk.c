#include "sampgdk.h"

#if SAMPGDK_WINDOWS
  #undef CreateMenu
  #undef DestroyMenu
  #undef GetTickCount
  #undef KillTimer
  #undef SelectObject
  #undef SetTimer
  #include <windows.h>
#endif
