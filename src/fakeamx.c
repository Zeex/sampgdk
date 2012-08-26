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

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#include "fakeamx.h"
#include "likely.h"

#define INITIAL_HEAP_SIZE 1024

void fakeamx_new(struct fakeamx *fa) {
	assert(fa != NULL);

	memset(fa, 0, sizeof(*fa));
	fa->heap = malloc(sizeof(cell) * INITIAL_HEAP_SIZE);
	fa->heap_size = INITIAL_HEAP_SIZE;

	fa->amxhdr.magic = AMX_MAGIC;
	fa->amxhdr.file_version = MIN_FILE_VERSION;
	fa->amxhdr.amx_version = MIN_AMX_VERSION;
	fa->amxhdr.dat = (int)fa->heap - (int)&fa->amxhdr;

	fa->amx.base = (unsigned char*)&fa->amxhdr;
	fa->amx.data = (unsigned char*)fa->heap;
	fa->amx.callback = amx_Callback;
	fa->amx.stp = INT_MAX;
}

void fakeamx_free(struct fakeamx *fa) {
	assert(fa != NULL);

	free(fa->heap);
}

struct fakeamx *fakeamx_global() {
	static struct fakeamx static_fa;
	static struct fakeamx *fa_ptr = NULL;

	if (unlikely(fa_ptr == NULL)) {
		fa_ptr = &static_fa;
		fakeamx_new(fa_ptr);
	}

	return fa_ptr;
}

cell fakeamx_push(struct fakeamx *fa, size_t cells) {
	cell address;
	
	assert(fa != NULL);

	address = fa->amx.hea;
	fa->amx.hea += cells * sizeof(cell);

	if (fa->amx.hea / sizeof(cell) >= fa->heap_size) {
		fakeamx_resize_heap(fa, fa->amx.hea / sizeof(cell));
	}

	return address;
}

cell fakeamx_push_cell(struct fakeamx *fa, cell value) {
	cell address;

	assert(fa != NULL);

	address = fakeamx_push(fa, 1);
	fa->heap[address / sizeof(cell)] = value;

	return address;
}

cell fakeamx_push_float(struct fakeamx *fa, float value) {
	assert(fa != NULL);

	return fakeamx_push_cell(fa, amx_ftoc(value));
}

cell fakeamx_push_string(struct fakeamx *fa, const char *src, size_t *size) {
	size_t src_size;
	cell address;
	
	assert(fa != NULL);

	src_size = strlen(src) + 1;
	address = fakeamx_push(fa, src_size);
	amx_SetString(fa->heap + (address / sizeof(cell)), src, 0, 0, src_size);

	if (size != NULL) {
		*size = src_size;
	}

	return address;
}

void fakeamx_get_cell(struct fakeamx *fa, cell address, cell *value) {
	assert(fa != NULL);

	*value = fa->heap[address / sizeof(cell)];
}

void fakeamx_get_bool(struct fakeamx *fa, cell address, bool *value) {
	assert(fa != NULL);

	*value = (bool)fa->heap[address / sizeof(cell)];
}

void fakeamx_get_float(struct fakeamx *fa, cell address, float *value) {
	cell tmp;

	assert(fa != NULL);

	fakeamx_get_cell(fa, address, &tmp);
	*value = amx_ctof(tmp);
}

void fakeamx_get_string(struct fakeamx *fa, cell address, char *dest, size_t size) {
	assert(fa != NULL);

	amx_GetString(dest, fa->heap + (address / sizeof(cell)), 0, size);
}

void fakeamx_pop(struct fakeamx *fa, cell address) {
	assert(fa != NULL);

	if (fa->amx.hea > address) {
		fa->amx.hea = address;
	}
}

void fakeamx_resize_heap(struct fakeamx *fa, size_t new_size) {
	void *new_heap;

	assert(fa != NULL);

	new_heap = realloc(fa->heap, new_size);
	if (new_heap != NULL) {
		fa->heap = new_heap;
		fa->heap_size = new_size;
		fa->amx.data = (unsigned char*)fa->heap;
		fa->amxhdr.dat = (int)fa->heap - (int)&fa->amxhdr;
	}
}
