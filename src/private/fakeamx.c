/* Copyright (C) 2011-2013 Zeex
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

#include "array.h"
#include "fakeamx.h"
#include "init.h"
#include "likely.h"
#include "log.h"

#define INITIAL_HEAP_SIZE 1024

static struct fakeamx global;

DEFINE_CLEANUP_FUNC(fakeamx_cleanup) {
	fakeamx_free(&global);
}

DEFINE_INIT_FUNC(fakeamx_init) {
	int error;

	error = fakeamx_new(&global);
	if (error < 0)
		return error;

	atexit(fakeamx_cleanup);
	return 0;
}

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

void fakeamx_global(struct fakeamx **fa) {
	*fa = &global;
}

int fakeamx_push(struct fakeamx *fa, size_t cells, cell *address) {
	cell old_hea;
	cell new_hea;

	assert(fa != NULL);
	
	old_hea = fa->amx.hea;
	new_hea = fa->amx.hea + cells * sizeof(cell);

	if (new_hea >= fa->heap.size * (int)sizeof(cell)) {
		int error;

		if ((error = array_resize(&fa->heap, new_hea / sizeof(cell))) < 0)
			return error;

		array_pad(&fa->heap);
	}

	fa->amx.hea = new_hea;

	if (address != NULL)
		*address = old_hea;

	return 0;
}

int fakeamx_push_cell(struct fakeamx *fa, cell value, cell *address) {
	int error;

	assert(address != NULL);

	if ((error = fakeamx_push(fa, 1, address)) < 0)
		return error;

	((cell *)(fa->heap.data))[*address / sizeof(cell)] = value;

	return 0;
}

int fakeamx_push_float(struct fakeamx *fa, float value, cell *address) {
	assert(fa != NULL);
	return fakeamx_push_cell(fa, amx_ftoc(value), address);
}

int fakeamx_push_string(struct fakeamx *fa, const char *src, int *size, cell *address) {
	int src_size;
	int error;

	assert(address != NULL);
	assert(src != NULL);
	assert(address != NULL);

	src_size = (int)strlen(src) + 1;
	if ((error = fakeamx_push(fa, src_size, address)) < 0)
		return error;

	amx_SetString((cell *)array_get(&fa->heap, *address / sizeof(cell)), src, 0, 0, src_size);

	if (size != NULL)
		*size = src_size;

	return 0;
}

void fakeamx_get_cell(struct fakeamx *fa, cell address, cell *value) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));
	assert(value != NULL);

	*value = *(cell *)array_get(&fa->heap, address / sizeof(cell));
}

void fakeamx_get_bool(struct fakeamx *fa, cell address, bool *value) {
	cell tmp;

	assert(fa != NULL);
	assert(is_cell_aligned(address));
	assert(value != NULL);

	fakeamx_get_cell(fa, address, &tmp);
	*value = (bool)tmp;
}

void fakeamx_get_float(struct fakeamx *fa, cell address, float *value) {
	cell tmp;

	assert(fa != NULL);
	assert(is_cell_aligned(address));
	assert(value != NULL);

	fakeamx_get_cell(fa, address, &tmp);
	*value = amx_ctof(tmp);
}

void fakeamx_get_string(struct fakeamx *fa, cell address, char *dest, int size) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));
	assert(dest != NULL);

	amx_GetString(dest, (cell *)array_get(&fa->heap, address / sizeof(cell)), 0, size);
}

void fakeamx_pop(struct fakeamx *fa, cell address) {
	assert(fa != NULL);
	assert(is_cell_aligned(address));

	if (fa->amx.hea > address)
		fa->amx.hea = address;
}
