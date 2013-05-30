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
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "init.h"
#include "native.h"
#include "log.h"

static struct sampgdk_array natives;

DEFINE_INIT_FUNC(native) {
  int error;
  
  error = sampgdk_array_new(&natives, 100, sizeof(AMX_NATIVE_INFO));
  if (error < 0) {
    return error;
  }

  return 0;
}

DEFINE_CLEANUP_FUNC(native) {
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
  return strcmp((const char *)key,
                ((const AMX_NATIVE_INFO *)elem)->name);
}

AMX_NATIVE sampgdk_native_lookup(const char *name) {
  AMX_NATIVE_INFO *info;

  assert(name != NULL);

  info = bsearch(name, natives.data, natives.count,
                 natives.elem_size, compare);
  if (info == NULL) {
    return NULL;
  }

  return info->func;
}

AMX_NATIVE sampgdk_native_lookup_warn(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  func = sampgdk_native_lookup(name);
  if (func == NULL) {
    sampgdk_log_warn("Native function not found: %s", name);
  }

  return func;
}

cell AMX_NATIVE_CALL sampgdk_native_stub(AMX *amx, cell *params) {
  sampgdk_log_warn("Native stub");
  return 0;
}

AMX_NATIVE sampgdk_native_lookup_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_lookup(name)) == NULL) {
    return sampgdk_native_stub;
  }

  return func;
}

AMX_NATIVE sampgdk_native_lookup_warn_stub(const char *name) {
  AMX_NATIVE func;

  assert(name != NULL);

  if ((func = sampgdk_native_lookup_warn(name)) == NULL) {
    return sampgdk_native_stub;
  }

  return func;
}

const AMX_NATIVE_INFO *sampgdk_native_get_natives(void) {
  return (const AMX_NATIVE_INFO*)natives.data;
}

int sampgdk_native_get_num_natives(void) {
  return natives.count;
}
