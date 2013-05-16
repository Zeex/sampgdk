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

static struct sampgdk_fakeamx global;

DEFINE_INIT_FUNC(fakeamx) {
  int error;

  error = sampgdk_fakeamx_new(&global);
  if (error < 0) {
    return error;
  }

  return 0;
}

DEFINE_CLEANUP_FUNC(fakeamx) {
  sampgdk_fakeamx_free(&global);
}

static bool is_cell_aligned(cell address) {
  return address % sizeof(cell) == 0;
}

int sampgdk_fakeamx_new(struct sampgdk_fakeamx *fa) {
  int error;

  assert(fa != NULL);

  memset(fa, 0, sizeof(*fa));

  error = sampgdk_array_new(&fa->heap, INITIAL_HEAP_SIZE + STACK_SIZE,
                   sizeof(cell));
  if (error < 0) {
    return error;
  }

  fa->amxhdr.magic = AMX_MAGIC;
  fa->amxhdr.file_version = MIN_FILE_VERSION;
  fa->amxhdr.amx_version = MIN_AMX_VERSION;
  fa->amxhdr.dat = (cell)fa->heap.data - (cell)&fa->amxhdr;
  fa->amxhdr.defsize = sizeof(AMX_FUNCSTUBNT);

  fa->amx.base = (unsigned char *)&fa->amxhdr;
  fa->amx.data = (unsigned char *)fa->heap.data;
  fa->amx.callback = amx_Callback;

  fa->amx.stp = fa->heap.size * sizeof(cell);
  fa->amx.stk = fa->amx.stp;

  sampgdk_array_pad(&fa->heap);

  return 0;
}

void sampgdk_fakeamx_free(struct sampgdk_fakeamx *fa) {
  assert(fa != NULL);
  sampgdk_array_free(&fa->heap);
}

struct sampgdk_fakeamx *sampgdk_fakeamx_global(void) {
  return &global;
}

int sampgdk_fakeamx_heap_resize(struct sampgdk_fakeamx *fa, int cells) {
  int error;
  cell old_size, new_size;
  cell old_stk, new_stk;
  cell old_stp, new_stp;

  assert(cells > 0);

  old_size = fa->heap.size;
  new_size = cells;

  error = sampgdk_array_resize(&fa->heap, new_size);
  if (error < 0) {
    return error;
  }

  /* Update data pointers to point at the newly allocated heap. */
  fa->amxhdr.dat = (cell)fa->heap.data - (cell)&fa->amxhdr;
  fa->amx.data = (unsigned char *)fa->heap.data;

  old_stk = fa->amx.stk;
  new_stk = fa->amx.stk + (new_size - old_size) * sizeof(cell);

  old_stp = fa->amx.stp;
  new_stp = fa->amx.stp + (new_size - old_size) * sizeof(cell);

  /* Shift stack contents. */
  memmove((unsigned char *)fa->heap.data + new_stk - STACK_SIZE,
          (unsigned char *)fa->heap.data + old_stk - STACK_SIZE,
          STACK_SIZE);

  fa->amx.stk = new_stk;
  fa->amx.stp = new_stp;

  return 0;
}

int sampgdk_fakeamx_heap_push(struct sampgdk_fakeamx *fa, int cells,
                              cell *address) {
  cell old_hea, new_hea;
  cell old_heap_size, new_heap_size;

  assert(fa != NULL);
  assert(cells > 0);
  
  old_hea = fa->amx.hea;
  new_hea = fa->amx.hea + cells * sizeof(cell);

  old_heap_size = fa->heap.size;
  new_heap_size = (new_hea + STACK_SIZE) / sizeof(cell);

  if (new_hea >= (cell)(old_heap_size * sizeof(cell))) {
    int error;

    error = sampgdk_fakeamx_heap_resize(fa, new_heap_size);
    if (error < 0) {
      return error;
    }
  }

  fa->amx.hea = new_hea;

  if (address != NULL) {
    *address = old_hea;
  }

  return 0;
}

int sampgdk_fakeamx_heap_push_cell(struct sampgdk_fakeamx *fa, cell value,
                                   cell *address) {
  int error;

  assert(address != NULL);

  if ((error = sampgdk_fakeamx_heap_push(fa, 1, address)) < 0) {
    return error;
  }

  ((cell *)(fa->heap.data))[*address / sizeof(cell)] = value;

  return 0;
}

int sampgdk_fakeamx_heap_push_float(struct sampgdk_fakeamx *fa, float value,
                                    cell *address) {
  assert(fa != NULL);
  return sampgdk_fakeamx_heap_push_cell(fa, amx_ftoc(value), address);
}

int sampgdk_fakeamx_heap_push_string(struct sampgdk_fakeamx *fa,
                                     const char *src, int *size,
                                     cell *address) {
  int src_size;
  int error;

  assert(address != NULL);
  assert(src != NULL);
  assert(address != NULL);

  src_size = (int)strlen(src) + 1;
  if ((error = sampgdk_fakeamx_heap_push(fa, src_size, address)) < 0) {
    return error;
  }

  amx_SetString((cell *)sampgdk_array_get(&fa->heap, *address / sizeof(cell)),
                src, 0, 0, src_size);

  if (size != NULL) {
    *size = src_size;
  }

  return 0;
}

void sampgdk_fakeamx_heap_get_cell(struct sampgdk_fakeamx *fa, cell address,
                                   cell *value) {
  assert(fa != NULL);
  assert(is_cell_aligned(address));
  assert(value != NULL);

  *value = *(cell *)sampgdk_array_get(&fa->heap, address / sizeof(cell));
}

void sampgdk_fakeamx_heap_get_bool(struct sampgdk_fakeamx *fa, cell address,
                                   bool *value) {
  cell tmp;

  assert(fa != NULL);
  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_heap_get_cell(fa, address, &tmp);
  *value = (bool)tmp;
}

void sampgdk_fakeamx_heap_get_float(struct sampgdk_fakeamx *fa, cell address,
                                    float *value) {
  cell tmp;

  assert(fa != NULL);
  assert(is_cell_aligned(address));
  assert(value != NULL);

  sampgdk_fakeamx_heap_get_cell(fa, address, &tmp);
  *value = amx_ctof(tmp);
}

void sampgdk_fakeamx_heap_get_string(struct sampgdk_fakeamx *fa, cell address,
                                     char *dest, int size) {
  assert(fa != NULL);
  assert(is_cell_aligned(address));
  assert(dest != NULL);

  amx_GetString(dest, (cell *)sampgdk_array_get(&fa->heap,
                                                address / sizeof(cell)),
                                                0, size);
}

void sampgdk_fakeamx_heap_pop(struct sampgdk_fakeamx *fa, cell address) {
  assert(fa != NULL);
  assert(is_cell_aligned(address));

  if (fa->amx.hea > address) {
    fa->amx.hea = address;
  }
}
