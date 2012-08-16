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

#include <stdlib.h>
#include <string.h>

#define MAX_NATIVES 512

/* TODO: make this dynamic */
static AMX_NATIVE_INFO natives[MAX_NATIVES];
static unsigned int num_natives = 0;

void native_register(const char *name, AMX_NATIVE native) {
	if (num_natives < MAX_NATIVES) {
		natives[num_natives].name = name;
		natives[num_natives].func = native;
		num_natives++;
	}
}

AMX_NATIVE native_lookup(const char *name) {
	unsigned int index = 0;

	while (index < num_natives) {
		if (strcmp(natives[index].name, name) == 0) {
			return natives[index].func;
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
	return natives;
}
