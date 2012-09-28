/* Copyright (C) 2012 Zeex
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

#ifndef SAMPGDK_ARRAY_H_
#define SAMPGDK_ARRAY_H_

#include <sampgdk/bool.h>

struct array {
	void *data;      /* pointer to array contents */
	int   count;     /* number of elements in array */
	int   size;      /* maximum number of elements for this array */
	int   elem_size; /* size of a signle element in bytes */
};

int array_new(struct array *a, int size, int elem_size);
void array_free(struct array *a);
bool array_ok(struct array *a);
int array_zero(struct array *a);
int array_resize(struct array *a, int new_size);
int array_grow(struct array *a);
int array_shrink(struct array *a);
int array_pad(struct array *a);
void *array_get(struct array *a, int index);
void array_set(struct array *a, int index, void *elem);
int array_insert(struct array *a, int index, int count, void *elems);
int array_insert_single(struct array *a, int index, void *elem);
int array_remove(struct array *a, int index, int count);
int array_remove_single(struct array *a, int index);
int array_append(struct array *a, void *elem);

#endif /* !SAMPGDK_ARRAY_H */
