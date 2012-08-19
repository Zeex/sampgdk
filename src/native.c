/* Copyright (C) 2011-2012 Zeex
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
#include <sampgdk/amx.h>
#include <sampgdk/core.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

static struct array natives;

void native_init() {
	array_new(&natives, 100, sizeof(AMX_NATIVE_INFO));
}

void native_cleanup() {
	array_free(&natives);
}

bool native_register(const char *name, AMX_NATIVE func) {
	AMX_NATIVE_INFO native;

	native.name = name;
	native.func = func;

	return array_append(&natives, &native);
}

AMX_NATIVE native_lookup(const char *name) {
	size_t index = 0;
	AMX_NATIVE_INFO *info;

	info = (AMX_NATIVE_INFO*)natives.data;
	while (index < natives.count) {
		if (strcmp(info[index].name, name) == 0) {
			return info[index].func;
		}
		index++;
	}

	return NULL;
}

AMX_NATIVE native_lookup_warn(const char *name) {
	AMX_NATIVE fn;

	fn = native_lookup(name);
	if (fn == NULL) {
		sampgdk_logprintf("sampgdk: native function not found: %s", name);
	}

	return fn;
}

static cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
	sampgdk_logprintf("sampgdk: called non-existent native function");
	return 0;
}

AMX_NATIVE native_lookup_stub(const char *name) {
	AMX_NATIVE fn;

	fn = native_lookup(name);
	if (fn == NULL) {
		return native_stub;
	}

	return fn;
}

const AMX_NATIVE_INFO *native_get_all_natives() {
	return (const AMX_NATIVE_INFO*)natives.data;
}

const int native_get_num_natives() {
	return (int)natives.count;
}
