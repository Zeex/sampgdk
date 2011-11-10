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

#ifndef SAMPGDK_CONFIG_H 
#define SAMPGDK_CONFIG_H 

// Windows
#if defined WIN32 || defined _WIN32 || defined __WIN32__ 
	#define SAMPGDK_WINDOWS 1
#endif

// Linux 
#if defined __linux__ || defined __linux || defined linux
	#if !defined LINUX
		#define LINUX
	#endif
	#define SAMPGDK_LINUX 1
#endif

// stdint.h
#if !defined HAVE_STDINT_H 
	#if (!defined __STDC__ && __STDC_VERSION__ >= 199901L /* C99 or newer */)\
		|| (defined _MSC_VER_ && _MSC_VER >= 1600 /* Visual Studio 2010 and later */)\
		|| defined __GNUC__ /* GCC, MinGW, etc */
		#define HAVE_STDINT_H 1
	#endif
#endif

// size_t
#include <stddef.h> 

// alloca()
#if SAMPGDK_WINDOWS
	#undef HAVE_ALLOCA_H
	#include <malloc.h> // For _alloca()
	#if !defined alloca
		#define alloca _alloca
	#endif
#elif SAMPGDK_LINUX 
	#if defined __GNUC__ 
		#define HAVE_ALLOCA_H 1
		#if !defined alloca
			#define alloca __builtin_alloca
		#endif
	#endif
#endif

#endif // !SAMPGDK_CONFIG_H
