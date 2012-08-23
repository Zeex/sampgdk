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

#include <sampgdk/config.h>

#include <stdarg.h>

#include "server-log.h"

void log(const char *format, ...) {
	va_list args;

	va_start(args, format);
	server_log_printf("[sampgdk] ");
	server_log_vprintf(format, args);
	server_log_printf("\n");
	va_end(args);
}

void trace(const char *format, ...) {
	va_list args;

	va_start(args, format);
	server_log_printf("[sampgdk] TRACE: ");
	server_log_vprintf(format, args);
	server_log_printf("\n");
	va_end(args);
}

void error(const char *format, ...) {
	va_list args;

	va_start(args, format);
	server_log_printf("[sampgdk] ERROR: ");
	server_log_vprintf(format, args);
	server_log_printf("\n");
	va_end(args);
}

void warning(const char *format, ...) {
	va_list args;

	va_start(args, format);
	server_log_printf("[sampgdk] WARNING: ");
	server_log_vprintf(format, args);
	server_log_printf("\n");
	va_end(args);
}
