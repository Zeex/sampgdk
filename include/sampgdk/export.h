/* Copyright (c) 2011 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H

#undef SAMPGDK_EXPORT
#undef SAMPGDK_CALL

#include <sampgdk/config.h>

#ifdef __cplusplus
	#define SAMPGDK_EXTERN_C extern "C"
#else
	#define SAMPGDK_EXTERN_C
#endif

#if defined SAMPGDK_LINUX
	#define SAMPGDK_CALL 
	#define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __attribute__((visibility("default")))
#elif defined SAMPGDK_WINDOWS
	#define SAMPGDK_CALL __cdecl
	#if defined IN_SAMPGDK
		#define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __declspec(dllexport)
	#else
		#define SAMPGDK_EXPORT SAMPGDK_EXTERN_C __declspec(dllimport)
	#endif
#else
	#error Usupported operating system
#endif

#endif /* SAMPGDK_EXPORT_H */
