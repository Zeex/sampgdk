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

#ifndef SAMPGDK_FAKEAMX_H_
#define SAMPGDK_FAKEAMX_H_

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

struct fakeamx {
	AMX         amx;
	AMX_HEADER  amxhdr;
	cell       *heap;
	size_t      heap_size;
};

void fakeamx_new(struct fakeamx *fa);
void fakeamx_free(struct fakeamx *fa);
struct fakeamx *fakeamx_global();
cell fakeamx_push(struct fakeamx *fa, size_t cells);
cell fakeamx_push_cell(struct fakeamx *fa, cell value);
cell fakeamx_push_float(struct fakeamx *fa, float value);
cell fakeamx_push_string(struct fakeamx *fa, const char *src, size_t *size /* = NULL */);
void fakeamx_get_cell(struct fakeamx *fa, cell address, cell *value);
void fakeamx_get_bool(struct fakeamx *fa, cell address, bool *value);
void fakeamx_get_float(struct fakeamx *fa, cell address, float *value);
void fakeamx_get_string(struct fakeamx *fa, cell address, char *dest, size_t size);
void fakeamx_pop(struct fakeamx *fa, cell address);
void fakeamx_resize_heap(struct fakeamx *fa, size_t new_size);

#endif /* !SAMPGDK_FAKEAMX_H_ */
