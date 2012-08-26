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

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "likely.h"
#include "server-cfg.h"

struct config {
	int   timestamp;
	char *timeformat;
#ifdef SAMPGDK_LINUX
	int   output;
#endif
};

static struct {
	FILE          *fp;
	struct config  cfg;
	int            cfg_loaded;
} log = {
	NULL,
	{
		1,
		"[%H:%M:%S]",
#ifdef SAMPGDK_LINUX
		0
#endif
	}
};

static int cfg_callback(const char *key, const char *value, void *param) {
	struct config *cfg = (struct config *)param;

	if (strcmp(key, "timestamp") == 0) {
		cfg->timestamp = (strtol(value, NULL, 10) != 0);
		return 0;
	}

	if (strcmp(key, "logtimeformat") == 0) {
		int size = strlen(value) + 1;

		if ((cfg->timeformat = malloc(size * sizeof(char))) != NULL)
			strncpy(cfg->timeformat, value, size);
		return 0;
	}

#ifdef SAMPGDK_LINUX
	if (strcmp(key, "output") == 0) {
		cfg->output = (strtol(value, NULL, 10) != 0);
		return 0;
	}
#endif

	return 0;
}

static int get_timestamp(char *buffer, int size, const struct config *cfg) {
	time_t now;
	struct tm *time_info;

	time(&now);
	time_info = localtime(&now);

	return strftime(buffer, size, cfg->timeformat, time_info);
}

void server_log_vprintf(const char *format, va_list args) {
	struct {
		char string[256];
		int  length;
	} ts;

	if (unlikely(!log.cfg_loaded))
		log.cfg_loaded = server_cfg_parse(cfg_callback, (void*)&log.cfg, 0);

	if (unlikely(log.fp == NULL))
		log.fp = fopen("server_log.txt", "a");

	if (log.cfg.timestamp != 0) {
		ts.length = get_timestamp(ts.string, sizeof(ts.string), &log.cfg);

		if (log.fp != NULL) {
			fputs(ts.string, log.fp);
			fputs(" ", log.fp);
		}
	}

	if (likely(log.fp != NULL)) {
		vfprintf(log.fp, format, args);
		fflush(log.fp);
	}

#ifdef SAMPGDK_LINUX
	if (log.cfg.output) {
#endif
		vfprintf(stdout, format, args);
		fflush(stdout);
#ifdef SAMPGDK_LINUX
	}
#endif
}

void server_log_printf(const char *format, ...) {
	va_list args;

	va_start(args, format);
	server_log_vprintf(format, args);
	va_end(args);
}
