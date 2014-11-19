/* Copyright (C) 2012-2014 Zeex
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
#include <stdlib.h>
#include <string.h>

#include <sampgdk/bool.h>

#include "init.h"
#include "logprintf.h"

enum _sampgdk_log_level {
  _SAMPGDK_LOG_INFO,
  _SAMPGDK_LOG_TRACE,
  _SAMPGDK_LOG_WARNING,
  _SAMPGDK_LOG_ERROR
};

static bool _sampgdk_log_enabled[] = {
  false, /* _SAMPGDK_LOG_INFO */
  false, /* _SAMPGDK_LOG_TRACE */
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
      case 'i':
        level = _SAMPGDK_LOG_INFO;
        break;
      case 't':
        level = _SAMPGDK_LOG_TRACE;
        break;
      case 'w':
        level = _SAMPGDK_LOG_WARNING;
        break;
      case 'e':
        level = _SAMPGDK_LOG_ERROR;
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
}

SAMPGDK_MODULE_CLEANUP(log) {
  /* nothing to do here */
}

static void _sampgdk_log_message(int level, const char *format, va_list args) {
  const char *level_string;
  char *real_format;

  assert(level >= _SAMPGDK_LOG_INFO &&
         level <= _SAMPGDK_LOG_ERROR);

  if (!_sampgdk_log_enabled[level]) {
    return;
  }

  switch (level) {
    case _SAMPGDK_LOG_INFO:
      level_string = "info";
      break;
    case _SAMPGDK_LOG_TRACE:
      level_string = "trace";
      break;
    case _SAMPGDK_LOG_WARNING:
      level_string = "warning";
      break;
    case _SAMPGDK_LOG_ERROR:
      level_string = "error";
      break;
    default:
      level_string = "";
  }

  real_format = malloc(
    sizeof("[sampgdk:] ") - 1
    + strlen(level_string)
    + strlen(format)
    + 1
  );
  if (real_format == NULL) {
    return;
  }

  strcpy(real_format, "[sampgdk:");
  strcat(real_format, level_string);
  strcat(real_format, "] ");
  strcat(real_format, format);

  sampgdk_do_vlogprintf(real_format, args);

  free(real_format);
}

void sampgdk_log_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_INFO, format, args);
  va_end(args);
}

void sampgdk_log_trace(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_TRACE, format, args);
  va_end(args);
}

void sampgdk_log_warning(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_WARNING, format, args);
  va_end(args);
}

void sampgdk_log_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _sampgdk_log_message(_SAMPGDK_LOG_ERROR, format, args);
  va_end(args);
}

void sampgdk_log_error_code(int error) {
  _sampgdk_log_message(_SAMPGDK_LOG_ERROR, strerror(-error), NULL);
}
