//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2006 SA:MP Team
//
//----------------------------------------------------------

// This is a modified version of the original plugincommon.h which is aimed
// to fix some compiling issues when including amx/amx.h on Windows.

#ifndef SAMPGDK_AMX_H 
#define SAMPGDK_AMX_H 

// detect stdint.h
#if !defined HAVE_STDINT_H 
	#if (!defined __STDC__ && __STDC_VERSION__ >= 199901L)\
			|| (defined _MSC_VER_ && _MSC_VER >= 1600  /*VS 2010 and later */)\
			|| (defined __GNUC__)
		#define HAVE_STDINT_H
	#endif
#endif

#include <stddef.h> // fix for size_t 

#if defined WIN32 || defined _WIN32 || defined __WIN32__ || defined HAVE_MALLOC_H
	#include <malloc.h> // for _alloca() on Windows 
#elif defined __GNUC__ || defined HAVE_ALLOCA_H
	#include <alloca.h> // for alloca() on *nix
#endif

#include "amx/amx.h"

#endif // !SAMPGDK_AMX_H
