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
#include "callback.h"
#include "init.h"
#include "plugin.h"

static struct sampgdk_array callbacks;

DEFINE_INIT_FUNC(callback) {
  int error;

  if (callbacks.data != NULL) {
    return 0; /* alrady initialized */
  }

  error = sampgdk_array_new(&callbacks, 1, sizeof(struct sampgdk_callback));
  if (error < 0) {
    return error;
  }

  return 0;
}

DEFINE_CLEANUP_FUNC(callback) {
  int index;

  for (index = 0; index < callbacks.count; index++) {
    struct sampgdk_callback *info =
      (struct sampgdk_callback *)sampgdk_array_get(&callbacks, index);
    free(info->name);
  }

  sampgdk_array_free(&callbacks);
}

static int compare(const void *key, const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct sampgdk_callback *)elem)->name);
}

struct sampgdk_callback *sampgdk_callback_lookup(const char *name) {
  assert(name != NULL);
  return bsearch(name, callbacks.data, callbacks.count,
                 callbacks.elem_size, compare);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback_handler handler) {
  int error;
  struct sampgdk_callback info;
  struct sampgdk_callback *ptr;
  int index;
  
  assert(name != NULL);
  assert(handler != NULL);

  /* This is rather an exception than a rule. */
  sampgdk_callback_init();

  ptr = sampgdk_callback_lookup(name);
  if (ptr != NULL) {
    ptr->handler = handler;
    return 0;
  }

  info.name = malloc(strlen(name) + 1);
  if (info.name == NULL) {
    return -ENOMEM;
  }

  strcpy(info.name, name);
  info.handler = handler;

  /* Maintain element order (by name). */
  for (index = 0; index < callbacks.count; index++) {
    ptr = (struct sampgdk_callback *)sampgdk_array_get(&callbacks, index);
    if (strcmp(ptr->name, name) >= 0) {
      error = sampgdk_array_insert_single(&callbacks, index, &info);
      break;
    }
  }

  /* Append to the end. */
  if (index == callbacks.count) {
    error = sampgdk_array_append(&callbacks, &info);
  }

  if (error < 0) {
    free(info.name);
    return error;
  }

  return 0;
}

int sampgdk_callback_register_table(const struct sampgdk_callback *table) {
  const struct sampgdk_callback *ptr;
  int error;

  for (ptr = table; ptr->name != NULL; ptr++) {
    error = sampgdk_callback_register(ptr->name, ptr->handler);
    if (error < 0) {
      return error;
    }
  }

  return 0;
}

void sampgdk_callback_unregister(const char *name) {
  const struct sampgdk_callback *ptr;
  int index;

  for (index = 0; index < callbacks.count; index++) {
    ptr = (const struct sampgdk_callback *)sampgdk_array_get(&callbacks, index);
    if (strcmp(ptr->name, name) == 0) {
      sampgdk_array_remove_single(&callbacks, index);
      break;
    }
  }
}

void sampgdk_callback_unregister_table(const struct sampgdk_callback *table) {
  const struct sampgdk_callback *ptr;

  for (ptr = table; ptr->name != NULL; ptr++) {
    sampgdk_callback_unregister(ptr->name);
  }
}

bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval) {
  struct sampgdk_plugin_list *plugin;

  assert(name != NULL);

  for (plugin = sampgdk_plugin_get_list(); plugin != NULL;
       plugin = plugin->next) {
    void *func;
    struct sampgdk_callback *info;
    sampgdk_callback_handler handler;

    func = sampgdk_plugin_find_symbol(plugin->plugin, name);
    if (func == NULL) {
      continue;
    }

    info = sampgdk_callback_lookup(name);
    if (info == NULL) {
      continue;
    }

    handler = info->handler;
    if (handler == NULL) {
      continue;
    }

    /* If the callback handler returns false, the call chain
     * should be interrupted.
     */
    if (!handler(amx, func, retval)) {
      return false;
    }
  }

  return true;
}

cell sampgdk_callback_arg_cell(AMX *amx, int index) {
  AMX_HEADER *hdr = (AMX_HEADER*)amx->base;
  unsigned char *data = (amx->data != 0) ? amx->data : amx->base + hdr->dat;
  unsigned char *stack = data + amx->stk * sizeof(cell);
  return ((cell*)stack)[index];
}

bool sampgdk_callback_arg_bool(AMX *amx, int index) {
  return (bool)sampgdk_callback_arg_cell(amx, index);
}

float sampgdk_callback_arg_float(AMX *amx, int index) {
  cell value = sampgdk_callback_arg_cell(amx, index);
  return amx_ctof(value);
}

char *sampgdk_callback_arg_string(AMX *amx, int index) {
  cell amx_addr;
  cell *phys_addr;
  int length;
  char *string;
  
  amx_addr = sampgdk_callback_arg_cell(amx, index);
  if (amx_GetAddr(amx, amx_addr, &phys_addr) != AMX_ERR_NONE) {
    return NULL;
  }
  
  amx_StrLen(phys_addr, &length);
  string = malloc((length + 1) * sizeof(char));
  
  if (amx_GetString(string, phys_addr, 0, length + 1) != AMX_ERR_NONE) {
    free(string);
    return NULL;
  }

  return string;
}
