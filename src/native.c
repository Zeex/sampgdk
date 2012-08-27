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

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>
#include <sampgdk/core.h>

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "likely.h"
#include "log.h"

static struct array natives;
static bool init_ok = false;

int native_init() {
	return array_new(&natives, 100, sizeof(AMX_NATIVE_INFO));
}

void native_cleanup() {
	array_free(&natives);
}

int native_register(const char *name, AMX_NATIVE func) {
	AMX_NATIVE_INFO native;

	if (unlikely(!init_ok)) {
		int error;

		if ((error = native_init()) < 0)
			return error;

		init_ok = true;
	}

	native.name = name;
	native.func = func;

	return array_append(&natives, &native);
}

AMX_NATIVE native_lookup(const char *name) {
	int index = 0;
	AMX_NATIVE_INFO *info;

	info = (AMX_NATIVE_INFO*)natives.data;
	while (index < natives.count) {
		if (strcmp(info[index].name, name) == 0)
			return info[index].func;
		index++;
	}

	return NULL;
}

AMX_NATIVE native_lookup_warn(const char *name) {
	AMX_NATIVE fn;

	fn = native_lookup(name);
	if (fn == NULL)
		warning("Native function not found: %s", name);

	return fn;
}

cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
	error("Native stub");
	return 0;
}

AMX_NATIVE native_lookup_stub(const char *name) {
	AMX_NATIVE fn;

	if ((fn = native_lookup(name)) == NULL)
		return native_stub;

	return fn;
}

AMX_NATIVE native_lookup_warn_stub(const char *name) {
	AMX_NATIVE fn;

	if ((fn = native_lookup_warn(name)) == NULL)
		return native_stub;

	return fn;
}

const AMX_NATIVE_INFO *native_get_natives() {
	return (const AMX_NATIVE_INFO*)natives.data;
}

const int native_get_num_natives() {
	return (int)natives.count;
}
