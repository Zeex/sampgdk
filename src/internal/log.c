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

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "logprintf.h"

enum _sampgdk_log_level {
  _SAMPGDK_LOG_NORMAL,
  _SAMPGDK_LOG_TRACE,
  _SAMPGDK_LOG_WARNING,
  _SAMPGDK_LOG_ERROR
};

static void _sampgdk_do_log(int level, const char *format, va_list args) {
  const char *prefix;
  char *real_format;

  switch (level) {
    case _SAMPGDK_LOG_TRACE:
      prefix = "trace: ";
      break;
    case _SAMPGDK_LOG_WARNING:
      prefix = "warning: ";
      break;
    case _SAMPGDK_LOG_ERROR:
      prefix = "error: ";
      break;
    default:
      prefix = "";
  }

  real_format = malloc(
    sizeof("[sampgdk] ") - 1
    + strlen(prefix)
    + strlen(format)
    + 1
  );
  if (real_format == NULL) {
    return;
  }

  strcpy_s(real_format, sizeof("[sampgdk] "), "[sampgdk] ");
  strcat_s(real_format, strlen(prefix), prefix);
  strcat_s(real_format, strlen(format), format);

  sampgdk_do_vlogprintf(real_format, args);

  free(real_format);
}

void sampgdk_log_message(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_NORMAL, format, args);
  va_end(args);
}

void sampgdk_log_trace(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_TRACE, format, args);
  va_end(args);
}

void sampgdk_log_warn(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_WARNING, format, args);
  va_end(args);
}

void sampgdk_log_error(const char *format, ...) {
  va_list args;

  va_start(args, format);
  _sampgdk_do_log(_SAMPGDK_LOG_ERROR, format, args);
  va_end(args);
}

void sampgdk_log_error_code(int error) {
	char buffer[36 + 1];
	strerror_s(buffer, 36, error);
	_sampgdk_do_log(_SAMPGDK_LOG_ERROR, buffer, NULL);
}
