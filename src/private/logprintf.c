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
#include <stdlib.h>
#include <string.h>

#include <sampgdk/core.h>

#include "call.h"
#include "logprintf.h"

void sampgdk_do_vlogprintf(const char *format, va_list va) {
  int i;
  int nargs;
  const void **args;

  assert(sampgdk_logprintf != NULL);

  nargs = 1;

  if (va != NULL) {
    for (i = 0; format[i] != '\0'; i++) {
      if (format[i] == '%' && format[i + 1] != '%') {
        nargs++;
      }
    }
  }

  args = malloc((nargs + 1) * sizeof(*args));
  if (args == NULL) {
    return;
  }

  args[0] = format;

  if (va != NULL) {
    for (i = 1; i <= nargs; i++) {
      args[i] = va_arg(va, const void *);
    }
  }

  sampgdk_call_func_cdecl((void*)sampgdk_logprintf, args, nargs);
  free((void*)args);
}
