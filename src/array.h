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

#ifndef SAMPGDK_ARRAY_H_
#define SAMPGDK_ARRAY_H_

#include <sampgdk/config.h>

#include <stddef.h>

struct array {
	void  *data;      /* pointer to array contents */
	size_t count;     /* number of elements in array */
	size_t size;      /* maximum number of elements for this array */
	size_t elem_size; /* size of a signle element in bytes */
};

bool array_init(struct array *a, size_t size, size_t elem_size);
void array_free(struct array *a);
bool array_resize(struct array *a, size_t new_size);
bool array_grow(struct array *a);
bool array_shrink(struct array *a);
void *array_get(const struct array *a, size_t index);
void array_set(struct array *a, size_t index, void *elem);
bool array_insert(struct array *a, size_t index, size_t count, void *elems);
bool array_insert_single(struct array *a, size_t index, void *elem);
void array_remove(struct array *a, size_t index, size_t count);
void array_remove_single(struct array *a, size_t index);
bool array_append(struct array *a, void *elem);

#endif /* !SAMPGDK_ARRAY_H_ */
