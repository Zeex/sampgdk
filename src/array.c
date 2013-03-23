/* Copyright (C) 2012-2013 Zeex
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

#include <sampgdk/bool.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

int array_new(struct array *a, int size, int elem_size) {
	assert(a != NULL);
	assert(size > 0);
	assert(elem_size > 0);

	if ((a->data = malloc(elem_size * size)) == NULL)
		return -ENOMEM;

	a->size = size;
	a->elem_size = elem_size;
	a->count = 0;

	return 0;
}

void array_free(struct array *a) {
	assert(a != NULL);

	free(a->data);
	memset(a, 0, sizeof(*a));
}

bool array_ok(struct array *a) {
	return a->data != NULL && a->elem_size > 0;
}

int array_zero(struct array *a) {
	assert(a != NULL);
	assert(a->data != NULL);

	if (a->data == NULL)
		return -EINVAL;

	memset(a->data, 0, a->size * a->elem_size);

	return 0;
}

int array_resize(struct array *a, int new_size) {
	void *new_data;

	assert(a != NULL);
	assert(new_size > 0);
	assert(a->elem_size > 0);

	if (new_size == a->size)
		return 0;

	new_data = realloc(a->data, a->elem_size * new_size);

	if (new_data == NULL)
		return -ENOMEM;

	a->data = new_data;
	a->size = new_size;

	if (a->count > a->size)
		a->count = a->size;

	return 0;
}

int array_grow(struct array *a) {
	float factor;

	assert(a != NULL);

	if (a->size == 0)
		return array_resize(a, 1);

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

	return array_resize(a, (int)(a->size * factor));
}

int array_shrink(struct array *a) {
	assert(a != NULL);

	return array_resize(a, a->count);
}

int array_pad(struct array *a) {
	int space;

	assert(a != NULL);

	if ((space = a->size - a->count) <= 0)
		return space;

	return (a->count = a->size);
}

static void *array_get_ptr(struct array *a, int index) {
	return (unsigned char*)a->data + (index * a->elem_size);
}

void *array_get(struct array *a, int index) {
	assert(a != NULL);
	assert(index >= 0);
	assert(index < a->count);

	return array_get_ptr(a, index);
}

void array_set(struct array *a, int index, void *elem) {
	assert(a != NULL);
	assert(elem != NULL);
	assert(index >= 0);
	assert(index < a->count);

	memcpy(array_get_ptr(a, index), elem, a->elem_size);
}

int array_insert(struct array *a, int index, int count, void *elems) {
	int need_count;
	int move_count;

	assert(a != NULL);
	assert(elems != NULL);
	assert(index >= 0);
	assert(index < a->count);

	if (count <= 0)
		return -EINVAL;

	need_count = a->count + count - a->size;
	move_count = a->count - index;

	if (need_count > 0) {
		int error;

		if ((error = array_resize(a, a->size + need_count)) < 0)
			return error;
	}

	if (move_count > 0) {
		memmove(array_get_ptr(a, index + count),
		        array_get_ptr(a, index),
		        move_count * a->elem_size);
	}

	a->count += count;
	memcpy(array_get_ptr(a, index), elems, count * a->elem_size);

	return 0;
}

int array_insert_single(struct array *a, int index, void *elem) {
	return array_insert(a, index, 1, elem);
}

int array_remove(struct array *a, int index, int count) {
	int move_count;

	assert(a != NULL);
	assert(index >= 0);
	assert(index < count);

	if (count <= 0 || count > a->count - index)
		return -EINVAL;

	move_count = a->count - index - count;

	if (move_count > 0) {
		memmove(array_get_ptr(a, index),
		        array_get_ptr(a, index + count),
		        move_count * a->elem_size);
 	}

	a->count -= count;

	return 0;
}

int array_remove_single(struct array *a, int index) {
	return array_remove(a, index, 1);
}

int array_append(struct array *a, void *elem) {
	assert(a != NULL);
	assert(elem != NULL);

	if (a->count == a->size) {
		int error;

		if ((error = array_grow(a)) < 0)
			return error;
	}

	a->count++;
	array_set(a, a->count - 1, elem);

	return 0;
}
