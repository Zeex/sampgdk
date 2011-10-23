// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H

#undef SAMPGDK_EXPORT
#undef SAMPGDK_CALL

#if defined _WIN32 || defined WIN32
	#define SAMPGDK_CALL __stdcall
#endif

#if defined IN_SAMPGDK 
	#if !defined SAMPGDK_STATIC
		#if defined WIN32 || defined _WIN32
			#define SAMPGDK_EXPORT __declspec(dllexport)
		#else
			#define SAMPGDK_EXPORT __attribute__((visibility("default")))
		#endif 
	#endif
#else // !IN_SAMPGDK
	#if !defined SAMPGDK_STATIC
		#if defined WIN32 || defined _WIN32
			#define SAMPGDK_EXPORT __declspec(dllimport)
		#endif
	#endif
#endif // IN_SAMPGDK

#if !defined SAMPGDK_EXPORT
	#define SAMPGDK_EXPORT
#endif
#if !defined SAMPGDK_CALL
	#define SAMPGDK_CALL
#endif

#endif // !SAMPGDK_EXPORT_H
