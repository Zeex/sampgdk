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

#ifndef SAMPGDK_FAKEAMX_H_
#define SAMPGDK_FAKEAMX_H_

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>

#include "array.h"

struct sampgdk_fakeamx {
  AMX                  amx;
  AMX_HEADER           amxhdr;
  struct sampgdk_array heap;
};

int sampgdk_fakeamx_new(struct sampgdk_fakeamx *fa);
void sampgdk_fakeamx_free(struct sampgdk_fakeamx *fa);
struct sampgdk_fakeamx *sampgdk_fakeamx_global(void);
int sampgdk_fakeamx_heap_resize(struct sampgdk_fakeamx *fa, int cells);
int sampgdk_fakeamx_heap_push(struct sampgdk_fakeamx *fa, int cells,
                              cell *address);
int sampgdk_fakeamx_heap_push_cell(struct sampgdk_fakeamx *fa, cell value,
                                   cell *address);
int sampgdk_fakeamx_heap_push_float(struct sampgdk_fakeamx *fa, float value,
                                    cell *address);
int sampgdk_fakeamx_heap_push_string(struct sampgdk_fakeamx *fa,
                                     const char *src, int *size, cell *address);
void sampgdk_fakeamx_heap_pop(struct sampgdk_fakeamx *fa, cell address);
void sampgdk_fakeamx_heap_get_cell(struct sampgdk_fakeamx *fa, cell address,
                                   cell *value);
void sampgdk_fakeamx_heap_get_bool(struct sampgdk_fakeamx *fa, cell address,
                                   bool *value);
void sampgdk_fakeamx_heap_get_float(struct sampgdk_fakeamx *fa, cell address,
                                    float *value);
void sampgdk_fakeamx_heap_get_string(struct sampgdk_fakeamx *fa, cell address,
                                     char *dest, int size);

#endif /* !SAMPGDK_FAKEAMX_H_ */
