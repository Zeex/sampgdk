/* Copyright (C) 2012-2013 Zeex
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

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "log.h"

static struct array natives;

int native_init() {
	return array_new(&natives, 100, sizeof(AMX_NATIVE_INFO));
}

void native_cleanup() {
	array_free(&natives);
}

int native_register(const char *name, AMX_NATIVE func) {
	AMX_NATIVE_INFO info;
	AMX_NATIVE_INFO *ptr;
	int index;

	info.name = name;
	info.func = func;

	assert(name != 0);

	/* Maintain element order (by name). */
	for (index = 0; index < natives.count; index++) {
		ptr = (AMX_NATIVE_INFO *)array_get(&natives, index);
		if (strcmp(ptr->name, name) >= 0) {
			return array_insert_single(&natives, index, &info);
		}
	}

	return array_append(&natives, &info);
}

static int compare(const void *key, const void *elem) {
	assert(key != NULL);
	assert(elem != NULL);
	return strcmp((const char *)key,
	              ((const AMX_NATIVE_INFO *)elem)->name);
}

AMX_NATIVE native_lookup(const char *name) {
	AMX_NATIVE_INFO *info;

	assert(name != NULL);

	info = bsearch(name, natives.data, natives.count,
	               natives.elem_size, compare);

	if (info == NULL)
		return NULL;

	return info->func;
}

AMX_NATIVE native_lookup_warn(const char *name) {
	AMX_NATIVE func;

	assert(name != NULL);

	func = native_lookup(name);
	if (func == NULL)
		log_warning("Native function not found: %s", name);

	return func;
}

cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
	log_error("Native stub");
	return 0;
}

AMX_NATIVE native_lookup_stub(const char *name) {
	AMX_NATIVE func;

	assert(name != NULL);

	if ((func = native_lookup(name)) == NULL)
		return native_stub;

	return func;
}

AMX_NATIVE native_lookup_warn_stub(const char *name) {
	AMX_NATIVE func;

	assert(name != NULL);

	if ((func = native_lookup_warn(name)) == NULL)
		return native_stub;

	return func;
}

const AMX_NATIVE_INFO *native_get_natives() {
	return (const AMX_NATIVE_INFO*)natives.data;
}

int native_get_num_natives() {
	return natives.count;
}
