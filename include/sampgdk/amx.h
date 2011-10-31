// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This file wraps amx/amx.h 

#ifndef SAMPGDK_AMX_H 
#define SAMPGDK_AMX_H 

#if !defined HAVE_STDINT_H 
	// Attempt to detect stdint.h
	#if (!defined __STDC__ && __STDC_VERSION__ >= 199901L /* C99 or newer */)\
		|| (defined _MSC_VER_ && _MSC_VER >= 1600 /* Visual Studio 2010 and later */)\
		|| defined __GNUC__ /* GCC, MinGW, etc */
		#define HAVE_STDINT_H
	#endif
#endif

#include <stddef.h> // Fix for undefined size_t 

#if defined HAVE_MALLOC_H || defined WIN32 || defined _WIN32 || defined __WIN32__ 
	#include <malloc.h> // For _alloca() on Windows 
#elif defined __GNUC__ || defined HAVE_ALLOCA_H
	#include <alloca.h> // For alloca() on Linux
#endif

#include "amx/amx.h"

#endif // !SAMPGDK_AMX_H
