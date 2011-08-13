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

#if defined __cplusplus
	#define SAMPGDK_EXTERN extern "C"
#else
	#define SAMPGDK_EXTERN extern
#endif

#if defined WIN32 || defined _WIN32
	#define SAMPGDK_EXPORT SAMPGDK_EXTERN __declspec(dllexport) 
	#define SAMPGDK_CALL   __cdecl
#else
	#define SAMPGDK_EXPORT 
	#define SAMPGDK_CALL
#endif 

#endif
