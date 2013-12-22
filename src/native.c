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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "fakeamx.h"
#include "init.h"
#include "native.h"
#include "log.h"

/* MAX_NATIVE_PARAMS is the maximum number of parameters that
 * sampgdk_native_invoke() can pass to native functions.
 */
#define MAX_NATIVE_PARAMS 32

static struct sampgdk_array natives;

SAMPGDK_MODULE_INIT(native) {
  int error;

  error = sampgdk_array_new(&natives, 100, sizeof(AMX_NATIVE_INFO));
  if (error < 0) {
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(native) {
  sampgdk_array_free(&natives);
}

int sampgdk_native_register(const char *name, AMX_NATIVE func) {
  AMX_NATIVE_INFO info;
  AMX_NATIVE_INFO *ptr;
  int index;

  info.name = name;
  info.func = func;

  assert(name != 0);

  /* Maintain element order (by name). */
  for (index = 0; index < natives.count; index++) {
    ptr = (AMX_NATIVE_INFO *)sampgdk_array_get(&natives, index);
    if (strcmp(ptr->name, name) >= 0) {
      return sampgdk_array_insert_single(&natives, index, &info);
    }
  }

  return sampgdk_array_append(&natives, &info);
}

static int compare(const void *key, const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key, ((const AMX_NATIVE_INFO *)elem)->name);
}

AMX_NATIVE sampgdk_native_find(const char *name) {
  AMX_NATIVE_INFO *info;

  assert(name != NULL);

  if (natives.data == NULL) {
    /* Perhaps they forgot to initialize? */
    return NULL;
  }

  info = bsearch(name, natives.data, natives.count,
                 natives.elem_size, compare);
  if (info == NULL) {
    return NULL;
  }

  return info->func;
}

AMX_NATIVE sampgdk_native_find_warn(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  func = sampgdk_native_find(name);
  if (func == NULL) {
    sampgdk_log_warn("Native function not found: %s", name);
  }

  return func;
}

static cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
  sampgdk_log_warn("Native stub");
  return 0;
}

AMX_NATIVE sampgdk_native_find_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_find(name)) == NULL) {
    return native_stub;
  }

  return func;
}

AMX_NATIVE sampgdk_native_find_warn_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_find_warn(name)) == NULL) {
    return native_stub;
  }

  return func;
}

const AMX_NATIVE_INFO *sampgdk_native_get_natives(void) {
  return (const AMX_NATIVE_INFO*)natives.data;
}

int sampgdk_native_get_num_natives(void) {
  return natives.count;
}

cell sampgdk_native_call(AMX_NATIVE native, cell *params) {
  AMX *amx = sampgdk_fakeamx_amx();
  return native(amx, params);
}

cell sampgdk_native_invoke(AMX_NATIVE native, const char *format, va_list args) {
  AMX *amx = sampgdk_fakeamx_amx();
  cell i;
  cell num_params = 0;
  cell params[MAX_NATIVE_PARAMS] = {0};
  struct ref_param {
    void  *ptr;
    size_t size;
  } ref_params[MAX_NATIVE_PARAMS] = {{NULL, 0}};
  cell retval;

  assert(native != NULL);

  if (format != NULL) {
    for (i = 1; format[i - 1] != '\0'; i++) {
      char type = format[i - 1];
      switch (type) {
        case 'i': /* integer */
        case 'd': /* integer */
        case 'b': /* boolean */
          params[i] = (cell)va_arg(args, int);
          break;
        case 'f': /* floating-point */ {
          float value = (float)va_arg(args, double);
          params[i] = amx_ftoc(value);
          break;
        }
        case 'r': /* const reference */
        case 'R': /* non-const reference (writeable) */ {
          cell *ptr = va_arg(args, cell *);
          sampgdk_fakeamx_push_cell(*ptr, &params[i]);
          ref_params[i].ptr = ptr;
          if (type == 'R') {
            ref_params[i].size = sizeof(cell);
          }
          break;
        }
        case 's': /* const string */
        case 'S': /* non-const string (writeable) */ {
          char *str = va_arg(args, char *);
          sampgdk_fakeamx_push_string(str, NULL, &params[i]);
          ref_params[i].ptr = str;
          if (type == 'S') {
            size_t size = va_arg(args, size_t);
            ref_params[i].size = size;
            /* Next parameter must be an integer argument containing the size
             * of the string. All SA-MP natives follow this convention.
             */
            params[++i] = size;
          }
          break;
        }
        default:
          assert(0 && "Invalid type specifier");
      }
    }
    num_params = i - 1;
  }

  params[0] = num_params * sizeof(cell);
  retval = native(amx, params);
  
  for (i = num_params; i >= 1; i--) {
    if (ref_params[i].size != 0) {
      /* If this is an output parameter, write back its new value. */
      char type = format[i - 1];
      switch (type) {
        case 'R':
          sampgdk_fakeamx_get_cell(params[i], ref_params[i].ptr);
          break;
        case 'S':
          sampgdk_fakeamx_get_string(params[i], ref_params[i].ptr,
                                     ref_params[i].size);
          break;
      }
    }
    if (ref_params[i].ptr != NULL) {
      sampgdk_fakeamx_pop(params[i]);
    }
  }

  return retval;
}
