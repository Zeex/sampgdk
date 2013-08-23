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

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <sampgdk/core.h>

#include "logprintf.h"

#define LOGPRINTF_BUFFER_SIZE 1024

#ifdef _MSC_VER
  #define vsnprintf vsprintf_s
#endif

static char *escape_format_string(const char *format) {
  int i, j;
  int nr_percents;
  char *new_format;

  nr_percents = 0;
  for (i = 0; format[i] != '\0'; i++) {
    if (format[i] == '%') {
      nr_percents++;
    }
  }

  new_format = calloc(nr_percents + i + 1, sizeof(char));
  if (new_format != NULL) {
    for (i = 0, j = 0; format[i] != '\0'; i++, j++) {
      new_format[j] = format[i];
      if (format[i] == '%') {
        new_format[++j] = '%';
      }
    }
  }

  return new_format;
}

void sampgdk_do_vlogprintf(const char *format, va_list va) {
  char buffer[LOGPRINTF_BUFFER_SIZE];
  char *escaped;

  vsnprintf(buffer, sizeof(buffer), format, va);
  escaped = escape_format_string(buffer);

  if (escaped != NULL) {
    sampgdk_logprintf(escaped);
    free(escaped);
  }
}
