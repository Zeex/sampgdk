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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

static void *get_element_ptr(struct sampgdk_array *a, int index) {
  return (unsigned char*)a->data + (index * a->elem_size);
}

int sampgdk_array_new(struct sampgdk_array *a, int size,
                      int elem_size) {
  assert(a != NULL);
  assert(size > 0);
  assert(elem_size > 0);

  if ((a->data = malloc(elem_size * size)) == NULL) {
    return -ENOMEM;
  }

  a->size = size;
  a->elem_size = elem_size;
  a->count = 0;

  return 0;
}

void sampgdk_array_free(struct sampgdk_array *a) {
  assert(a != NULL);

  free(a->data);
  memset(a, 0, sizeof(*a));
}

bool sampgdk_array_ok(struct sampgdk_array *a) {
  return a->data != NULL && a->elem_size > 0;
}

int sampgdk_array_zero(struct sampgdk_array *a) {
  assert(a != NULL);
  assert(a->data != NULL);

  if (a->data == NULL) {
    return -EINVAL;
  }

  memset(a->data, 0, a->size * a->elem_size);

  return 0;
}

int sampgdk_array_resize(struct sampgdk_array *a, int new_size) {
  void *new_data;

  assert(a != NULL);
  assert(new_size > 0);
  assert(a->elem_size > 0);

  if (new_size == a->size) {
    return 0;
  }

  new_data = realloc(a->data, a->elem_size * new_size);

  if (new_data == NULL) {
    return -errno;
  }

  a->data = new_data;
  a->size = new_size;

  if (a->count > a->size) {
    a->count = a->size;
  }

  return 0;
}

int sampgdk_array_grow(struct sampgdk_array *a) {
  float factor;

  assert(a != NULL);

  if (a->size == 0) {
    return sampgdk_array_resize(a, 1);
  }

  if (a->size < 10) {
    factor = 2.0f;
  } else if (a->size < 100) {
    factor = 1.5f;
  } else {
    factor = 1.1f;
  }

  return sampgdk_array_resize(a, (int)(a->size * factor));
}

int sampgdk_array_shrink(struct sampgdk_array *a) {
  assert(a != NULL);

  return sampgdk_array_resize(a, a->count);
}

int sampgdk_array_pad(struct sampgdk_array *a) {
  int space;

  assert(a != NULL);

  if ((space = a->size - a->count) <= 0) {
    return space;
  }

  return (a->count = a->size);
}

void *sampgdk_array_get(struct sampgdk_array *a, int index) {
  assert(a != NULL);
  assert(index >= 0);
  assert(index < a->count);
  return get_element_ptr(a, index);
}

void sampgdk_array_set(struct sampgdk_array *a, int index, void *elem) {
  assert(a != NULL);
  assert(elem != NULL);
  assert(index >= 0);
  assert(index < a->count);
  memcpy(get_element_ptr(a, index), elem, a->elem_size);
}

int sampgdk_array_insert(struct sampgdk_array *a, int index, int count,
                         void *elems) {
  int need_count;
  int move_count;

  assert(a != NULL);
  assert(elems != NULL);
  assert(index >= 0);
  assert(index < a->count);

  if (count <= 0) {
    return -EINVAL;
  }

  need_count = a->count + count - a->size;
  move_count = a->count - index;

  if (need_count > 0) {
    int error;

    if ((error = sampgdk_array_resize(a, a->size + need_count)) < 0) {
      return error;
    }
  }

  if (move_count > 0) {
    memmove(get_element_ptr(a, index + count),
            get_element_ptr(a, index),
            move_count * a->elem_size);
  }

  a->count += count;
  memcpy(get_element_ptr(a, index), elems, count * a->elem_size);

  return 0;
}

int sampgdk_array_insert_single(struct sampgdk_array *a, int index,
                                void *elem) {
  assert(a != NULL);
  assert(elem != NULL);
  return sampgdk_array_insert(a, index, 1, elem);
}

int sampgdk_array_remove(struct sampgdk_array *a, int index, int count) {
  int move_count;

  assert(a != NULL);
  assert(index >= 0);
  assert(index < count);

  if (count <= 0 || count > a->count - index) {
    return -EINVAL;
  }

  move_count = a->count - index - count;

  if (move_count > 0) {
    memmove(get_element_ptr(a, index),
            get_element_ptr(a, index + count),
            move_count * a->elem_size);
   }

  a->count -= count;

  return 0;
}

int sampgdk_array_remove_single(struct sampgdk_array *a, int index) {
  assert(a != NULL);
  assert(index >= 0);
  assert(index < a->count);
  return sampgdk_array_remove(a, index, 1);
}

int sampgdk_array_append(struct sampgdk_array *a, void *elem) {
  assert(a != NULL);
  assert(elem != NULL);

  if (a->count == a->size) {
    int error;

    if ((error = sampgdk_array_grow(a)) < 0) {
      return error;
    }
  }

  a->count++;
  sampgdk_array_set(a, a->count - 1, elem);

  return 0;
}
