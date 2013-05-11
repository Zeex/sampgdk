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

#ifndef SAMPGDK_PRIVATE_FAKEAMX_H_
#define SAMPGDK_PRIVATE_FAKEAMX_H_

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>

#include "array.h"

struct fakeamx {
  AMX          amx;
  AMX_HEADER   amxhdr;
  struct array heap;
};

int fakeamx_new(struct fakeamx *fa);
void fakeamx_free(struct fakeamx *fa);
struct fakeamx *fakeamx_global(void);
int fakeamx_heap_resize(struct fakeamx *fa, int cells);
int fakeamx_heap_push(struct fakeamx *fa, int cells, cell *address);
int fakeamx_heap_push_cell(struct fakeamx *fa, cell value, cell *address);
int fakeamx_heap_push_float(struct fakeamx *fa, float value, cell *address);
int fakeamx_heap_push_string(struct fakeamx *fa, const char *src, int *size, cell *address);
void fakeamx_heap_get_cell(struct fakeamx *fa, cell address, cell *value);
void fakeamx_heap_get_bool(struct fakeamx *fa, cell address, bool *value);
void fakeamx_heap_get_float(struct fakeamx *fa, cell address, float *value);
void fakeamx_heap_get_string(struct fakeamx *fa, cell address, char *dest, int size);
void fakeamx_heap_pop(struct fakeamx *fa, cell address);

#endif /* !SAMPGDK_PRIVATE_FAKEAMX_H_ */
