/* Copyright (C) 2012-2013 Zeex
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

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include <sampgdk/core.h>

#include "logprintf.h"

/* Seems like a reasonable value (at least Y_Less used this in fixes2). */
#define LOGPRINTF_BUFFER_SIZE 1024

#ifdef _MSC_VER
  #define vsnprintf vsprintf_s
#endif

/* By the way, it's a bad idea to use something like %%s in the format
 * string because then logprintf will get %s and eventually crash the
 * server. 
 *
 * TODO: Escape % characters (replace with %%).
 */
void sampgdk_do_vlogprintf(const char *format, va_list va) {
  char buffer[LOGPRINTF_BUFFER_SIZE];
  vsnprintf(buffer, sizeof(buffer), format, va);
  sampgdk_logprintf(buffer);
}
