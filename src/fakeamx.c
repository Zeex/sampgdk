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
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#include "array.h"
#include "fakeamx.h"
#include "likely.h"
#include "log.h"

#define INITIAL_HEAP_SIZE 1024

static bool is_cell_aligned(cell address) {
	return address % sizeof(cell) == 0;
}

int fakeamx_new(struct fakeamx *fa) {
	int error;

	assert(fa != NULL);

	/* clear the struct */
	memset(fa, 0, sizeof(*fa));
	
	if ((error = array_new(&fa->heap, INITIAL_HEAP_SIZE, sizeof(cell))) < 0)
		return error;

	array_pad(&fa->heap);

	fa->amxhdr.magic = AMX_MAGIC;
	fa->amxhdr.file_version = MIN_FILE_VERSION;
	fa->amxhdr.amx_version = MIN_AMX_VERSION;
	fa->amxhdr.dat = (int)fa->heap.data - (int)&fa->amxhdr;

	fa->amx.base = (unsigned char*)&fa->amxhdr;
	fa->amx.data = (unsigned char*)fa->heap.data;
	fa->amx.callback = amx_Callback;
	fa->amx.stp = INT_MAX;

	return 0;
}

void fakeamx_free(struct fakeamx *fa) {
	assert(fa != NULL);

	array_free(&fa->heap);
}

struct fakeamx *fakeamx_global() {
	static struct fakeamx static_fa;
	static struct fakeamx *fa = NULL;

	if (unlikely(fa == NULL)) {
		int error_code;

		if ((error_code = fakeamx_new(&static_fa)) < 0) {
			error(strerror(-error_code));
			return NULL;
		}
		
		fa = &static_fa;
	}

	return fa;
}

cell fakeamx_push(struct fakeamx *fa, size_t cells) {
	cell address;

	assert(fa != NULL);

	address = fa->amx.hea;
	fa->amx.hea += cells * sizeof(cell);

	if (fa->amx.hea >= fa->heap.size * (int)sizeof(cell)) {
		int error_code;

		if ((error_code = array_resize(&fa->heap, fa->amx.hea / sizeof(cell))) < 0)
			error(strerror(-error_code));
		else
			array_pad(&fa->heap);
	}

	return address;
}

cell fakeamx_push_cell(struct fakeamx *fa, cell value) {
	cell address;

	assert(fa != NULL);

	address = fakeamx_push(fa, 1);
	((cell *)(fa->heap.data))[address / sizeof(cell)] = value;

	return address;
}

cell fakeamx_push_float(struct fakeamx *fa, float value) {
	assert(fa != NULL);

	return fakeamx_push_cell(fa, amx_ftoc(value));
}

cell fakeamx_push_string(struct fakeamx *fa, const char *src, int *size) {
	int src_size;
	cell address;
	
	assert(fa != NULL);

	src_size = (int)strlen(src) + 1;
	address = fakeamx_push(fa, src_size);
	amx_SetString((cell *)array_get(&fa->heap, address / sizeof(cell)), src, 0, 0, src_size);

	if (size != NULL)
		*size = src_size;

	return address;
}

void fakeamx_get_cell(struct fakeamx *fa, cell address, cell *value) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));

	*value = *(cell *)array_get(&fa->heap, address / sizeof(cell));
}

void fakeamx_get_bool(struct fakeamx *fa, cell address, bool *value) {
	cell tmp;

	assert(fa != NULL);
	assert(is_cell_aligned(address));

	fakeamx_get_cell(fa, address, &tmp);
	*value = (bool)tmp;
}

void fakeamx_get_float(struct fakeamx *fa, cell address, float *value) {
	cell tmp;

	assert(fa != NULL);
	assert(is_cell_aligned(address));

	fakeamx_get_cell(fa, address, &tmp);
	*value = amx_ctof(tmp);
}

void fakeamx_get_string(struct fakeamx *fa, cell address, char *dest, int size) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));

	amx_GetString(dest, (cell *)array_get(&fa->heap, address / sizeof(cell)), 0, size);
}

void fakeamx_pop(struct fakeamx *fa, cell address) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));

	if (fa->amx.hea > address)
		fa->amx.hea = address;
}
