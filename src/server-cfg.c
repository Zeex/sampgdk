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

#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "server-cfg.h"

#define DEFAULT_BUFFER_SIZE 128

int is_space(char c) {
	return (c == ' ' || c == '\t');
}

int is_newline(char c) {
	return (c == '\r' || c == '\n');
}

int server_cfg_parse(server_cfg_callback callback, void *param, int buffer_size) {
	FILE *fp;
	char *buffer;
	int size;
	int pos;
	int length;
	char *key;
	char *value;
	int ret_code;

	if ((fp = fopen("server.cfg", "r")) == NULL)
		return -ENOENT;

	size = (buffer_size > 0)
		? buffer_size
		: DEFAULT_BUFFER_SIZE;

	buffer = malloc(size);
	if (buffer == NULL) {
		fclose(fp);
		return -ENOMEM;
	}

	while (fgets(buffer, size, fp) != NULL) {
		pos = 0;
		length = strlen(buffer);

		/* skip whitespace at the beginning */
		while (pos < length && is_space(buffer[pos]))
			pos++;

		if (pos == length) {
			key = NULL;
		} else {
			key = buffer + pos;

			while (pos < length && !is_space(buffer[pos]))
				pos++;

			/* terminate the key */
			buffer[pos++] = '\0';

			/* skip whitespace again */
			while (pos < length && is_space(buffer[pos]))
				pos++;

			if (pos == length) {
				value = NULL;
			} else {
				value = buffer + pos;

				/* strip newline */
				pos = length - 1;
				while (pos >= 0 && is_newline(buffer[pos]))
					buffer[pos--] = '\0';
			}
		}

		ret_code = callback(key, value, param);

		if (ret_code > 0)
			break;
	}
	
	free(buffer);
	fclose(fp);

	if (ret_code > 0)
		return ret_code;

	return 0;
}

