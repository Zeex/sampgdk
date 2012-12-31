/* Copyright (C) 2012 Zeex
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

enum log_type {
	log_default,
	log_trace,
	log_warning,
	log_error
};

static void do_log(enum log_type type, const char *format, va_list args) {
	const char *prefix;
	char *real_format;

	switch (type) {
		case log_trace:
			prefix = "TRACE: ";
			break;
		case log_warning:
			prefix = "WARNING: ";
			break;
		case log_error:
			prefix = "ERROR: ";
			break;
		default:
			prefix = "";
	}

	real_format = malloc(
		sizeof("[sampgdk] ") - 1
		+ strlen(prefix)
		+ strlen(format)
		+ sizeof("\n") - 1
		+ 1
	);
	if (real_format == NULL)
		return;

	strcpy(real_format, "[sampgdk] ");
	strcat(real_format, prefix);
	strcat(real_format, format);
	strcat(real_format, "\n");

	vlogprintf(real_format, args);

	free(real_format);
}

void message(const char *format, ...) {
	va_list args;

	va_start(args, format);
	do_log(log_default, format, args);
	va_end(args);
}

void trace(const char *format, ...) {
	va_list args;

	va_start(args, format);
	do_log(log_trace, format, args);
	va_end(args);
}

void warning(const char *format, ...) {
	va_list args;

	va_start(args, format);
	do_log(log_warning, format, args);
	va_end(args);
}

void error(const char *format, ...) {
	va_list args;

	va_start(args, format);
	do_log(log_error, format, args);
	va_end(args);
}
