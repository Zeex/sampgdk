/* Copyright (C) 2011-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_FAKEAMX_H
#define SAMPGDK_INTERNAL_FAKEAMX_H

#include <sampgdk/bool.h>
#include <sampgdk/sdk.h>

/* Returns the global fake AMX instance. */
AMX *sampgdk_fakeamx_amx(void);

/* Changes the size of the fake AMX heap. Used in the amx_Allot() hook. */
int sampgdk_fakeamx_resize_heap(int cells);

/* Push a value onto the fake AMX heap. */
int sampgdk_fakeamx_push(int cells, cell *address);
int sampgdk_fakeamx_push_cell(cell value, cell *address);
int sampgdk_fakeamx_push_float(float value, cell *address);
int sampgdk_fakeamx_push_array(const cell *src, int size, cell *address);
int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address);
void sampgdk_fakeamx_pop(cell address);

/* Get stuff back from the heap. Usually used for output parameters. */
void sampgdk_fakeamx_get_cell(cell address, cell *value);
void sampgdk_fakeamx_get_bool(cell address, bool *value);
void sampgdk_fakeamx_get_float(cell address, float *value);
void sampgdk_fakeamx_get_array(cell address, cell *dest, int size);
void sampgdk_fakeamx_get_string(cell address, char *dest, int size);

#endif /* !SAMPGDK_INTERNAL_FAKEAMX_H */
