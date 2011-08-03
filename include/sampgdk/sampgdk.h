#ifndef SAMPGDK_H
#define SAMPGDK_H

#if defined HAVE_MALLOC_H
    #include <malloc.h> // for _alloca()
#endif

#if defined HAVE_STDDEF_H
    #include <stddef.h> // fix for size_t issue on MinGW
#endif

// Plugin stuff
#include <sampgdk/logprintf.h>
#include <sampgdk/plugin.h>

// Wrapper
#include <sampgdk/eventhandler.h>
#include <sampgdk/objects.h>
#include <sampgdk/players.h>
#include <sampgdk/samp.h>
#include <sampgdk/vehicles.h>
#include <sampgdk/wrapper.h>

#endif
