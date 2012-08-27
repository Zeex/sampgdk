/* Copyright (C) 2011-2012 Zeex
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

#ifndef SAMPGDK_PLATFORM_H
#define SAMPGDK_PLATFORM_H

#if !(defined _M_IX86 || defined __i386__)
	#error Unsupported architecture
#endif

#if defined WIN32 || defined _WIN32 || defined __WIN32__
	#define SAMPGDK_WINDOWS 1
#endif

#if defined __linux__ || defined __linux || defined linux
	#if !defined LINUX
		#define LINUX
	#endif
	#define SAMPGDK_LINUX 1
#endif

#endif /* !SAMPGDK_PLATFORM_H */
