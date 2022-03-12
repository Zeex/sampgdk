/* Copyright (C) 2011-2016 Zeex
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

#include "amx.h"
#include "array.h"
#include "fakeamx.h"
#include "init.h"

/* Space reserved for the stack. */
#define _SAMPGDK_FAKEAMX_STACK_SIZE 64

/* The initial size of the heap. */
#define _SAMPGDK_FAKEAMX_HEAP_SIZE 1024

static struct {
  AMX                  amx;
  AMX_HEADER           amxhdr;
  struct sampgdk_array heap;
} _sampgdk_fakeamx;

SAMPGDK_MODULE_INIT(fakeamx) {
  int error;

  memset(&_sampgdk_fakeamx, 0, sizeof(_sampgdk_fakeamx));

  error = sampgdk_array_new(&_sampgdk_fakeamx.heap,
                            _SAMPGDK_FAKEAMX_HEAP_SIZE +
                            _SAMPGDK_FAKEAMX_STACK_SIZE,
                            sizeof(cell));
  if (error < 0) {
    return error;
  }

  _sampgdk_fakeamx.amxhdr.magic = AMX_MAGIC;
  _sampgdk_fakeamx.amxhdr.file_version = MIN_FILE_VERSION;
  _sampgdk_fakeamx.amxhdr.amx_version = MIN_AMX_VERSION;
  _sampgdk_fakeamx.amxhdr.dat =
    (cell)_sampgdk_fakeamx.heap.data - (cell)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amxhdr.defsize = sizeof(AMX_FUNCSTUBNT);

  _sampgdk_fakeamx.amx.base = (unsigned char *)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amx.data = (unsigned char *)_sampgdk_fakeamx.heap.data;
  _sampgdk_fakeamx.amx.callback = amx_Callback;
  _sampgdk_fakeamx.amx.stp = _sampgdk_fakeamx.heap.size * sizeof(cell);
  _sampgdk_fakeamx.amx.stk = _sampgdk_fakeamx.amx.stp;
  _sampgdk_fakeamx.amx.flags = AMX_FLAG_NTVREG | AMX_FLAG_RELOC;

  sampgdk_array_pad(&_sampgdk_fakeamx.heap);

  return 0;
}

SAMPGDK_MODULE_CLEANUP(fakeamx) {
  sampgdk_array_free(&_sampgdk_fakeamx.heap);
}

AMX *sampgdk_fakeamx_amx(void) {
  return &_sampgdk_fakeamx.amx;
}

int sampgdk_fakeamx_resize_heap(int cells) {
  int error;
  cell old_size;
  cell new_size;
  cell old_stk;
  cell new_stk;
  cell new_stp;

  assert(cells > 0);

  old_size = _sampgdk_fakeamx.heap.size;
  new_size = cells;

  error = sampgdk_array_resize(&_sampgdk_fakeamx.heap, new_size);
  sampgdk_array_pad(&_sampgdk_fakeamx.heap);
  if (error < 0) {
    return error;
  }

  /* Update data pointers to point at the newly allocated heap. */
  _sampgdk_fakeamx.amxhdr.dat = (cell)_sampgdk_fakeamx.heap.data - (cell)&_sampgdk_fakeamx.amxhdr;
  _sampgdk_fakeamx.amx.data = (unsigned char *)_sampgdk_fakeamx.heap.data;

  old_stk = _sampgdk_fakeamx.amx.stk;
  new_stk = _sampgdk_fakeamx.amx.stk + (new_size - old_size) * sizeof(cell);
  new_stp = _sampgdk_fakeamx.amx.stp + (new_size - old_size) * sizeof(cell);

  /* Shift stack contents. */
  memmove((unsigned char *)_sampgdk_fakeamx.heap.data
                           + new_stk - _SAMPGDK_FAKEAMX_STACK_SIZE,
          (unsigned char *)_sampgdk_fakeamx.heap.data
                           + old_stk - _SAMPGDK_FAKEAMX_STACK_SIZE,
          _SAMPGDK_FAKEAMX_STACK_SIZE);

  _sampgdk_fakeamx.amx.stk = new_stk;
  _sampgdk_fakeamx.amx.stp = new_stp;

  return 0;
}

int sampgdk_fakeamx_push(int cells, cell *address) {
  cell old_hea, new_hea;
  cell old_heap_size, new_heap_size;

  assert(cells > 0);

  old_hea = _sampgdk_fakeamx.amx.hea;
  new_hea = _sampgdk_fakeamx.amx.hea + cells * sizeof(cell);

  old_heap_size = _sampgdk_fakeamx.heap.size;
  new_heap_size = (new_hea + _SAMPGDK_FAKEAMX_STACK_SIZE) / sizeof(cell);

  if (new_hea >= (cell)(old_heap_size * sizeof(cell))) {
    int error;

    error = sampgdk_fakeamx_resize_heap(new_heap_size);
    if (error < 0) {
      return error;
    }
  }

  _sampgdk_fakeamx.amx.hea = new_hea;

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

  ((cell *)(_sampgdk_fakeamx.heap.data))[*address / sizeof(cell)] = value;

  return 0;
}

int sampgdk_fakeamx_push_float(float value, cell *address) {
  return sampgdk_fakeamx_push_cell(amx_ftoc(value), address);
}

int sampgdk_fakeamx_push_array(const cell *src, int size, cell *address) {
  int error;
  cell *dest;

  assert(address != NULL);
  assert(src != NULL);
  assert(size > 0);

  if ((error = sampgdk_fakeamx_push(size, address)) < 0) {
    return error;
  }

  dest = (cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap, *address / sizeof(cell));
  memcpy(dest, src, size * sizeof(cell));

  return 0;
}

int sampgdk_fakeamx_push_string(const char *src, int *size, cell *address) {
  int src_size;
  int error;

  assert(address != NULL);
  assert(src != NULL);

  src_size = (int)strlen(src) + 1;
  if ((error = sampgdk_fakeamx_push(src_size, address)) < 0) {
    return error;
  }

  amx_SetString((cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                 *address / sizeof(cell)),
                src, 0, 0, src_size);

  if (size != NULL) {
    *size = src_size;
  }

  return 0;
}

void sampgdk_fakeamx_get_cell(cell address, cell *value) {
  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  *value = *(cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                      address / sizeof(cell));
}

void sampgdk_fakeamx_get_bool(cell address, bool *value) {
  cell tmp;

  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = !!tmp;
}

void sampgdk_fakeamx_get_float(cell address, float *value) {
  cell tmp;

  assert(address % sizeof(cell) == 0);
  assert(value != NULL);

  sampgdk_fakeamx_get_cell(address, &tmp);
  *value = amx_ctof(tmp);
}

void sampgdk_fakeamx_get_array(cell address, cell *dest, int size) {
  cell *src;

  assert(address % sizeof(cell) == 0);
  assert(dest != NULL);
  assert(size > 0);

  src = (cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap, address / sizeof(cell));
  memcpy(dest, src, size * sizeof(cell));
}

void sampgdk_fakeamx_get_string(cell address, char *dest, int size) {
  assert(address % sizeof(cell) == 0);
  assert(dest != NULL);

  amx_GetString(dest, (cell *)sampgdk_array_get(&_sampgdk_fakeamx.heap,
                                                address / sizeof(cell)),
                                                0, size);
}

void sampgdk_fakeamx_pop(cell address) {
  assert(address % sizeof(cell) == 0);

  if (_sampgdk_fakeamx.amx.hea > address) {
    _sampgdk_fakeamx.amx.hea = address;
  }
}
