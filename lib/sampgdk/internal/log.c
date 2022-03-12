/* Copyright (C) 2012-2019 Zeex
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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sampgdk/bool.h>

#include "init.h"
#include "log.h"
#include "logprintf.h"

#ifdef _MSC_VER
  #define snprintf sprintf_s
#endif

static bool _sampgdk_log_enabled[] = {
  false, /* _SAMPGDK_LOG_DEBUG */
  false, /* _SAMPGDK_LOG_INFO */
  true,  /* _SAMPGDK_LOG_WARNING */
  true , /* _SAMPGDK_LOG_ERROR */
};

static void _sampgdk_log_init_enabled() {
  char *levels;
  char c;
  char op = '\0';

  if ((levels = getenv("SAMPGDK_LOG")) == NULL) {
    return;
  }

  while ((c = *levels++) != '\0') {
    int level = -1;

    switch (c) {
      case '+':
      case '-':
        op = c;
        break;
      case 'd':
        level = SAMPGDK_LOG_DEBUG;
        break;
      case 'i':
        level = SAMPGDK_LOG_INFO;
        break;
      case 'w':
        level = SAMPGDK_LOG_WARNING;
        break;
      case 'e':
        level = SAMPGDK_LOG_ERROR;
        break;
    }

    if (level >= 0) {
      if (op == '+') {
        _sampgdk_log_enabled[level] = true;
      } else if (op == '-') {
        _sampgdk_log_enabled[level] = false;
      }
    }
  }
}

SAMPGDK_MODULE_INIT(log) {
  _sampgdk_log_init_enabled();
  return 0;
}

SAMPGDK_MODULE_CLEANUP(log) {
  /* nothing to do here */
}

void sampgdk_log_message(int level, const char *format, ...) {
  va_list args;
  char level_char;
  char real_format[SAMPGDK_LOGPRINTF_BUFFER_SIZE];

  assert(level >= SAMPGDK_LOG_DEBUG &&
         level <= SAMPGDK_LOG_ERROR);

  if (!_sampgdk_log_enabled[level]) {
    return;
  }

  switch (level) {
    case SAMPGDK_LOG_DEBUG:
      level_char = 'd';
      break;
    case SAMPGDK_LOG_INFO:
      level_char = 'i';
      break;
    case SAMPGDK_LOG_WARNING:
      level_char = 'w';
      break;
    case SAMPGDK_LOG_ERROR:
      level_char = 'e';
      break;
    default:
      return;
  }

  if (real_format == NULL) {
    return;
  }

  snprintf(real_format,
           sizeof(real_format),
           "[sampgdk:%c] %s",
           level_char,
           format);
  va_start(args, format);
  sampgdk_do_vlogprintf(real_format, args);
  va_end(args);
}
