/* Copyright (C) 2012-2019 Zeex
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
#include "likely.h"
#include "native.h"
#include "log.h"

#define _SAMPGDK_NATIVE_MAX_ARGS     32
#define _SAMPGDK_NATIVE_MAX_ARGS_SIZE 8  /* in bytes */

static struct sampgdk_array _sampgdk_natives;

SAMPGDK_MODULE_INIT(native) {
  int error;
  AMX_NATIVE_INFO null = {NULL, NULL};

  error = sampgdk_array_new(&_sampgdk_natives,
                            128,
                            sizeof(AMX_NATIVE_INFO));
  if (error < 0) {
    return error;
  }

  return sampgdk_array_append(&_sampgdk_natives, &null);
}

SAMPGDK_MODULE_CLEANUP(native) {
  sampgdk_array_free(&_sampgdk_natives);
}

int sampgdk_native_register(const char *name, AMX_NATIVE func) {
  AMX_NATIVE old_func;
  AMX_NATIVE_INFO info;
  AMX_NATIVE_INFO *ptr;
  int i;

  info.name = name;
  info.func = func;

  assert(name != 0);

  old_func = sampgdk_native_find(name);
  if (old_func != NULL) {
    return -1;
  }

  /* Keep natives ordered by name.
   * This allows us to use binary search in sampgdk_native_find().
   */
  for (i = 0; i < _sampgdk_natives.count - 1; i++) {
    ptr = (AMX_NATIVE_INFO *)sampgdk_array_get(&_sampgdk_natives, i);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  return sampgdk_array_insert(&_sampgdk_natives, i, 1, &info);
}

static int _sampgdk_native_compare_bsearch(const void *key,
                                           const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key, ((const AMX_NATIVE_INFO *)elem)->name);
}

AMX_NATIVE sampgdk_native_find(const char *name) {
  AMX_NATIVE_INFO *info;

  assert(name != NULL);

  if (_sampgdk_natives.data == NULL) {
    /* Perhaps they forgot to initialize? */
    return NULL;
  }

  info = (AMX_NATIVE_INFO *)bsearch(name,
                                    _sampgdk_natives.data,
                                    _sampgdk_natives.count - 1,
                                    _sampgdk_natives.elem_size,
                                    _sampgdk_native_compare_bsearch);
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
    sampgdk_log_warning("Native function not found: %s", name);
  }

  return func;
}

static cell AMX_NATIVE_CALL native_stub(AMX *amx, cell *params) {
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

AMX_NATIVE sampgdk_native_find_flexible(const char *name, AMX_NATIVE current) {
  char *always_search;

  if (SAMPGDK_LIKELY(current != NULL && current != native_stub)) {
    return current;
  }

  if (current == NULL) {
    /* This is the first time this native is searched for, do it as usual.
     */
    return sampgdk_native_find_warn_stub(name);
  }

  /* current == native_stub */
  if ((always_search = getenv("SAMGDK_NATIVE_SEARCH_ALWAYS")) != NULL
      && atoi(always_search) != 0) {
    /* Previous attempt to find the native failed, but the always search
     * option is set so search again.
     */
    return sampgdk_native_find_warn_stub(name);
  }

  return current;
}

const AMX_NATIVE_INFO *sampgdk_native_get_natives(int *number) {
  if (number != NULL) {
    *number = _sampgdk_natives.count - 1;
  }
  return (AMX_NATIVE_INFO *)_sampgdk_natives.data;
}

cell sampgdk_native_call(AMX_NATIVE native, cell *params) {
  AMX *amx = sampgdk_fakeamx_amx();
  assert(native != NULL);
  return native(amx, params);
}

cell sampgdk_native_invoke(AMX_NATIVE native,
                           const char *format,
                           va_list args) {
  cell i = 0;
  const char *format_ptr = format;
  unsigned char args_copy[_SAMPGDK_NATIVE_MAX_ARGS *
                          _SAMPGDK_NATIVE_MAX_ARGS_SIZE];
  unsigned char *args_ptr = args_copy;
  void *args_array[_SAMPGDK_NATIVE_MAX_ARGS];

  assert(format_ptr != NULL);

  while (*format_ptr != '\0' && i < _SAMPGDK_NATIVE_MAX_ARGS) {
    switch (*format_ptr) {
      case 'i': /* integer */
      case 'd': /* integer */
        *(int *)args_ptr = va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'b': /* boolean */
        *(bool *)args_ptr = !!va_arg(args, int);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'f': /* floating-point */
        *(float *)args_ptr = (float)va_arg(args, double);
        args_array[i++] = args_ptr;
        args_ptr += _SAMPGDK_NATIVE_MAX_ARGS_SIZE;
        break;
      case 'r': /* const reference */
      case 'R': /* non-const reference */
      case 's': /* const string */
      case 'S': /* non-const string */
      case 'a': /* const array */
      case 'A': /* non-const array */
        args_array[i++] = va_arg(args, void *);
        break;
    }
    format_ptr++;
  }

  return sampgdk_native_invoke_array(native, format, args_array);
}

cell sampgdk_native_invoke_array(AMX_NATIVE native, const char *format,
                                 void **args) {
  AMX *amx = sampgdk_fakeamx_amx();
  const char *format_ptr = format;
  cell i = 0;
  cell params[_SAMPGDK_NATIVE_MAX_ARGS + 1];
  cell size[_SAMPGDK_NATIVE_MAX_ARGS] = {0};
  char type[_SAMPGDK_NATIVE_MAX_ARGS];
  int needs_size = -1;
  enum {
    ST_READ_SPEC,
    ST_NEED_SIZE,
    ST_READING_SIZE,
    ST_READING_SIZE_ARG,
    ST_READ_SIZE
  } state = ST_READ_SPEC;
  cell retval;

  assert(format_ptr != NULL);
  assert(args != NULL);

  while (*format_ptr != '\0' && i < _SAMPGDK_NATIVE_MAX_ARGS) {
    switch (state) {
      case ST_READ_SPEC:
        switch (*format_ptr) {
          case 'i': /* integer */
          case 'd': /* integer */
            params[i + 1] = *(int *)args[i];
            break;
          case 'b': /* boolean */
            params[i + 1] = *(bool *)args[i];
            break;
          case 'f': /* floating-point */ {
            float value = *(float *)args[i];
            params[i + 1] = amx_ftoc(value);
            break;
          }
          case 'r': /* const reference */
          case 'R': /* non-const reference */ {
            cell *ptr = (cell *)args[i];
            sampgdk_fakeamx_push_cell(*ptr, &params[i + 1]);
            size[i] = sizeof(cell);
            break;
          }
          case 's': /* const string */ {
            char *str = (char *)args[i];
            int str_size;
            sampgdk_fakeamx_push_string(str, &str_size, &params[i + 1]);
            size[i] = str_size;
            break;
          }
          case 'S': /* non-const string */
          case 'a': /* const array */
          case 'A': /* non-const array */
            needs_size = i;
            state = ST_NEED_SIZE;
            break;
          default:
            sampgdk_log_warning("Unrecognized type specifier '%c'",
                                *format_ptr);
        }
        type[i++] = *format_ptr++;
        break;
      case ST_NEED_SIZE:
        if (*format_ptr == '[') {
          state = ST_READING_SIZE;
        } else {
          sampgdk_log_warning("Bad format string: expected '[' but got '%c'",
                              *format_ptr);
        }
        format_ptr++;
        break;
      case ST_READING_SIZE:
        if (*format_ptr == '*') {
          format_ptr++;
          state = ST_READING_SIZE_ARG;
        } else {
          size[needs_size] = (int)strtol(format_ptr, (char **)&format_ptr, 10);
          state = ST_READ_SIZE;
        }
        break;
      case ST_READING_SIZE_ARG: {
        int index = (int)strtol(format_ptr, (char **)&format_ptr, 10);
        size[needs_size] = *(int *)args[index];
        state = ST_READ_SIZE;
        break;
      }
      case ST_READ_SIZE: {
        if (*format_ptr == ']') {
          switch (type[needs_size]) {
            case 'a':
            case 'A':
            case 'S':
              if (size[needs_size] > 0) {
                sampgdk_fakeamx_push_array((const cell *)args[needs_size],
                                           size[needs_size],
                                           &params[needs_size + 1]);
              } else {
                sampgdk_log_warning("Invalid buffer size");
              }
              break;
          }
          needs_size = -1;
          state = ST_READ_SPEC;
        } else {
          sampgdk_log_warning("Bad format string (expected ']' but got '%c')",
                              *format_ptr);
        }
        format_ptr++;
        break;
      }
    }
  }

  if (*format_ptr != '\0') {
    sampgdk_log_warning("Too many native arguments (at most %d allowed)",
                        _SAMPGDK_NATIVE_MAX_ARGS);
  }

  params[0] = i * sizeof(cell);
  assert(native != NULL);
  retval = native(amx, params);

  while (--i >= 0) {
    if (size[i] > 0) {
      /* If this is an output parameter we have to write the updated value
       * back to the argument.
       */
      switch (type[i]) {
        case 'R':
          sampgdk_fakeamx_get_cell(params[i + 1], (cell *)args[i]);
          break;
        case 'S':
          sampgdk_fakeamx_get_string(params[i + 1], (char *)args[i], size[i]);
          break;
        case 'A':
          sampgdk_fakeamx_get_array(params[i + 1], (cell *)args[i], size[i]);
          break;
      }
      sampgdk_fakeamx_pop(params[i + 1]);
    }
  }

  return retval;
}
