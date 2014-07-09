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

enum log_msg_type {
  LOG_MSG_NORMAL,
  LOG_MSG_TRACE,
  LOG_MSG_WARNING,
  LOG_MSG_ERROR
};

static void do_log(enum log_msg_type type, const char *format, va_list args) {
  const char *prefix;
  char *real_format;

  switch (type) {
    case LOG_MSG_TRACE:
      prefix = "trace: ";
      break;
    case LOG_MSG_WARNING:
      prefix = "warning: ";
      break;
    case LOG_MSG_ERROR:
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

  strcpy(real_format, "[sampgdk] ");
  strcat(real_format, prefix);
  strcat(real_format, format);

  sampgdk_do_vlogprintf(real_format, args);

  free(real_format);
}

void sampgdk_log_message(const char *format, ...) {
  va_list args;

  va_start(args, format);
  do_log(LOG_MSG_NORMAL, format, args);
  va_end(args);
}

void sampgdk_log_trace(const char *format, ...) {
  va_list args;

  va_start(args, format);
  do_log(LOG_MSG_TRACE, format, args);
  va_end(args);
}

void sampgdk_log_warn(const char *format, ...) {
  va_list args;

  va_start(args, format);
  do_log(LOG_MSG_WARNING, format, args);
  va_end(args);
}

void sampgdk_log_error(const char *format, ...) {
  va_list args;

  va_start(args, format);
  do_log(LOG_MSG_ERROR, format, args);
  va_end(args);
}

void sampgdk_log_error_code(int error) {
  do_log(LOG_MSG_ERROR, strerror(-error), NULL);
}
