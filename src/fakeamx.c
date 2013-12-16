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

#include <assert.h>
#include <limits.h>
#include <string.h>

#include "array.h"
#include "fakeamx.h"
#include "init.h"

/* Space reserved for the stack. */
#define STACK_SIZE 64

/* The initial size of the heap. */
#define INITIAL_HEAP_SIZE 1024

struct sampgdk_fakeamx {
  AMX                  amx;
  AMX_HEADER           amxhdr;
  struct sampgdk_array heap;
};

static struct sampgdk_fakeamx global;

DEFINE_INIT_FUNC(fakeamx) {
  int error;

  memset(&global, 0, sizeof(global));

  error = sampgdk_array_new(&global.heap, INITIAL_HEAP_SIZE + STACK_SIZE,
                            sizeof(cell));
  if (error < 0) {
    return error;
  }

  global.amxhdr.magic = AMX_MAGIC;
  global.amxhdr.file_version = MIN_FILE_VERSION;
  global.amxhdr.amx_version = MIN_AMX_VERSION;
  global.amxhdr.dat = (cell)global.heap.data - (cell)&global.amxhdr;
  global.amxhdr.defsize = sizeof(AMX_FUNCSTUBNT);

  global.amx.base = (unsigned char *)&global.amxhdr;
  global.amx.data = (unsigned char *)global.heap.data;
  global.amx.callback = amx_Callback;

  global.amx.stp = global.heap.size * sizeof(cell);
  global.amx.stk = global.amx.stp;

  sampgdk_array_pad(&global.heap);

  return 0;
}

DEFINE_CLEANUP_FUNC(fakeamx) {
  sampgdk_array_free(&global.heap);
}

AMX *sampgdk_fakeamx_amx() {
  return &global.amx;
}

int sampgdk_fakeamx_resize_heap(int cells) {
  int error;
  cell old_size;
  cell new_size;
  cell old_stk;
  cell new_stk;
  cell new_stp;

  assert(cells > 0);

  old_size = global.heap.size;
  new_size = cells;

  error = sampgdk_array_resize(&global.heap, new_size);
  if (error < 0) {
    return error;
  }

  /* Update data pointers to point at the newly allocated heap. */
  global.amxhdr.dat = (cell)global.heap.data - (cell)&global.amxhdr;
  global.amx.data = (unsigned char *)global.heap.data;

  old_stk = global.amx.stk;
  new_stk = global.amx.stk + (new_size - old_size) * sizeof(cell);
  new_stp = global.amx.stp + (new_size - old_size) * sizeof(cell);

  /* Shift stack contents. */
  memmove((unsigned char *)global.heap.data + new_stk - STACK_SIZE,
          (unsigned char *)global.heap.data + old_stk - STACK_SIZE,
          STACK_SIZE);

  global.amx.stk = new_stk;
  global.amx.stp = new_stp;

  return 0;
}

int sampgdk_fakeamx_push(int cells, cell *address) {
  cell old_hea, new_hea;
  cell old_heap_size, new_heap_size;

  assert(cells > 0);
  
  old_hea = global.amx.hea;
  new_hea = global.amx.hea + cells * sizeof(cell);

  old_heap_size = global.heap.size;
  new_heap_size = (new_hea + STACK_SIZE) / sizeof(cell);

  if (new_hea >= (cell)(old_heap_size * sizeof(cell))) {
    int error;

    error = sampgdk_fakeamx_resize_heap(new_heap_size);
    if (error < 0) {
      return error;
    }
  }

  global.amx.hea = new_hea;

  if (address != NULL) {
    *address = old_hea;
  }

  return 0;
}

int sampgdk_fakeamx_push_cell(cell value, cell *address) {
  int error;

  assert(address != NULL);

  if ((error = sampgdk_fakeamx_push(1, address)) < 0) {
    return error;
  }

  ((cell *)(global.heap.data))[*address / sizeof(cell)] = value;

  return 0;
}

int sampgdk_fakeamx_push_float(float value, cell *address) {
  return sampgdk_fakeamx_push_cell(amx_ftoc(value), address);
}

int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address) {
  int src_size;
  int error;

  assert(address != NULL);
  assert(src != NULL);
  assert(address != NULL);

  src_size = (int)strlen(src) + 1;
  if ((error = sampgdk_fakeamx_push(src_size, address)) < 0) {
    return error;
  }

  amx_SetString((cell *)sampgdk_array_get(&global.heap,
                *address / sizeof(cell)), src, 0, 0, src_size);

  if (size != NULL) {
    *size = src_size;
  }

  return 0;
}

static bool is_cell_aligned(cell address) {
  return address % sizeof(cell) == 0;
}

void sampgdk_fakeamx_get_cell(cell address, cell *value) {
  assert(is_cell_aligned(address));
  assert(value != NULL);

  *value = *(cell *)sampgdk_array_get(&global.heap, address / sizeof(cell));
}

void sampgdk_fakeamx_get_bool(cell address, bool *value) {
  cell tmp;

  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = (bool)tmp;
}

void sampgdk_fakeamx_get_float(cell address, float *value) {
  cell tmp;

  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = amx_ctof(tmp);
}

void sampgdk_fakeamx_get_string(cell address, char *dest, int size) {
  assert(is_cell_aligned(address));
  assert(dest != NULL);

  amx_GetString(dest, (cell *)sampgdk_array_get(&global.heap,
                                                address / sizeof(cell)),
                                                0, size);
}

void sampgdk_fakeamx_pop(cell address) {
  assert(is_cell_aligned(address));

  if (global.amx.hea > address) {
    global.amx.hea = address;
  }
}
