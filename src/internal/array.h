/* Copyright (C) 2012-2014 Zeex
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

#ifndef SAMPGDK_INTERNAL_ARRAY_H
#define SAMPGDK_INTERNAL_ARRAY_H

#include <sampgdk/bool.h>

struct sampgdk_array {
  void *data;      /* pointer to array contents */
  int   count;     /* number of elements in array */
  int   size;      /* maximum number of elements */
  int   elem_size; /* size of an element in bytes */
};

typedef int (*sampgdk_array_cmp)(const void *x, const void *y);

int sampgdk_array_new(struct sampgdk_array *a, int size, int elem_size);
void sampgdk_array_free(struct sampgdk_array *a);
bool sampgdk_array_ok(struct sampgdk_array *a);
int sampgdk_array_zero(struct sampgdk_array *a);
int sampgdk_array_resize(struct sampgdk_array *a, int new_size);
int sampgdk_array_grow(struct sampgdk_array *a);
int sampgdk_array_shrink(struct sampgdk_array *a);
int sampgdk_array_pad(struct sampgdk_array *a);
void *sampgdk_array_get(struct sampgdk_array *a, int index);
void sampgdk_array_set(struct sampgdk_array *a,int index, void *elem);
int sampgdk_array_insert(struct sampgdk_array *a, int index, int count, void *elems);
int sampgdk_array_insert_single(struct sampgdk_array *a, int index, void *elem);
int sampgdk_array_insert_ordered(struct sampgdk_array *a, void *elem, sampgdk_array_cmp cmp);
int sampgdk_array_remove(struct sampgdk_array *a, int index, int count);
int sampgdk_array_remove_single(struct sampgdk_array *a, int index);
int sampgdk_array_append(struct sampgdk_array *a, void *elem);
int sampgdk_array_find(struct sampgdk_array *a, const void *key, sampgdk_array_cmp cmp);
int sampgdk_array_find_remove(struct sampgdk_array *a, const void *key, sampgdk_array_cmp cmp);

#endif /* !SAMPGDK_INTERNAL_ARRAY_H */
