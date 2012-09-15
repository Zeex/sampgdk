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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "server-log.h"

void logprintf_impl(const char *format, ...) {
	char *real_format;
	va_list args;

	if ((real_format = malloc(strlen(format) + 2)) == NULL)
		return;

	strcpy(real_format, format);
	strcat(real_format, "\n");
	
	va_start(args, format);
	server_log_vprintf(real_format, args);
	va_end(args);

	free(real_format);
}

