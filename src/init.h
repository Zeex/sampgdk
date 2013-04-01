/* Copyright (C) 2013 Zeex
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

#ifndef SAMPGDK_INIT_H_
#define SAMPGDK_INIT_H_

#include <stdlib.h> /* for atexit() */

/* Thanks to Joe Lowe for his wonderful post on StackOverflow:
 * http://stackoverflow.com/a/2390626/249230
 */
#if defined _MSC_VER
	#pragma section(".CRT$XCU", read)
	#define DEFINE_INIT_FUNC(f) \
		static void __cdecl f(void); \
		__declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
		static void __cdecl f(void)
#elif defined(__GNUC__)
	#define DEFINE_INIT_FUNC(f) \
		static void f(void) __attribute__((constructor)); \
		static void f(void)
#else
	#error Unsupported compiler
#endif

/* Just for the sake of completeness. */
#define DEFINE_CLEANUP_FUNC(f) \
	static void f(void)

#endif /* !SAMPGDK_INIT_H_ */
