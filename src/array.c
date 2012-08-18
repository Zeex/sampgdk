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

#include <sampgdk/config.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

bool array_new(struct array *a, size_t size, size_t elem_size) {
	assert(a != NULL);
	assert(size > 0);
	assert(elem_size > 0);

	if ((a->data = malloc(elem_size * size)) == NULL)
		return false;

	a->size = size;
	a->elem_size = elem_size;
	a->count = 0;

	return true;
}

void array_free(struct array *a) {
	assert(a != NULL);

	free(a->data);
	memset(a, 0, sizeof(*a));
}

bool array_resize(struct array *a, size_t new_size) {
	void *new_data;

	assert(a != NULL);
	assert(new_size > 0);

	if (new_size == a->size)
		return true;

	new_data = realloc(a->data, a->elem_size * new_size);

	if (new_data == NULL)
		return false;

	a->data = new_data;
	a->size = new_size;

	if (a->count > a->size)
		a->count = a->size;

	return true;
}

bool array_grow(struct array *a) {
	float factor;

	assert(a != NULL);

	/* Magic numbers below are just a guess... 
	 * You better use array_resize() if this code doesn't fit your needs.
	 */
	if (a->size < 10)
		/* very small arrays: [0, 10) */
		factor = 2.0f;
	else if (a->size < 100)
		/* medium size arrays: [10, 100) */
		factor = 1.5f;
	else
		/* large array: [100, infinity) */
		factor = 1.1f;

	return array_resize(a, (size_t)(a->size * factor));
}

bool array_shrink(struct array *a) {
	assert(a != NULL);

	return array_resize(a, a->count);
}

void *array_get(const struct array *a, size_t index) {
	assert(a != NULL);
	assert(index < a->size);

	return (unsigned char*)a->data + (index * a->elem_size);
}

void array_set(struct array *a, size_t index, void *elem) {
	assert(a != NULL);
	assert(elem != NULL);

	memcpy(array_get(a, index), elem, a->elem_size);
}

bool array_insert(struct array *a, size_t index, size_t count, void *elems) {
	assert(a != NULL);
	assert(elems != NULL);

	if (a->count == a->size && !array_grow(a))
		return false;

	memmove(
		array_get(a, index + count),
		array_get(a, index),
		a->elem_size * (a->count - index + 1)
	);
	a->count += count;

	return true;
}

bool array_insert_single(struct array *a, size_t index, void *elem) {
	return array_insert(a, index, 1, elem);
}

void array_remove(struct array *a, size_t index, size_t count) {
	assert(a != NULL);

	if (count == 0)
		return;

	memmove(
		array_get(a, index),
		array_get(a, index + count),
		a->elem_size * (a->count - index - count + 1)
	);
	a->count -= count;
}

void array_remove_single(struct array *a, size_t index) {
	array_remove(a, index, 1);
}

bool array_append(struct array *a, void *elem) {
	assert(a != NULL);
	assert(elem != NULL);

	if (a->data == NULL)
		return false;

	if (a->count == a->size && !array_grow(a))
		return false;

	array_set(a, a->count, elem);
	a->count++;

	return true;
}
