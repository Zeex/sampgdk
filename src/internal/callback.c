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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "callback.h"
#include "init.h"
#include "param.h"
#include "plugin.h"

static struct sampgdk_array _sampgdk_callbacks;

SAMPGDK_MODULE_INIT(callback) {
  int error;

  if (_sampgdk_callbacks.data != NULL) {
    return 0; /* already initialized */
  }

  error = sampgdk_array_new(&_sampgdk_callbacks,
                            1,
                            sizeof(struct sampgdk_callback));
  if (error < 0) {
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int index;

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    struct sampgdk_callback *info =
      (struct sampgdk_callback *)sampgdk_array_get(&_sampgdk_callbacks,
                                                   index);
    free(info->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

static int _sampgdk_callback_compare(const void *c1, const void *c2) {
  return strcmp(((const struct sampgdk_callback*)c1)->name,
                ((const struct sampgdk_callback*)c2)->name);
}

static int _sampgdk_callback_compare_bsearch(const void *key,
                                             const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct sampgdk_callback *)elem)->name);
}

struct sampgdk_callback *sampgdk_callback_find(const char *name) {
  assert(name != NULL);
  return bsearch(name, _sampgdk_callbacks.data,
                       _sampgdk_callbacks.count,
                       _sampgdk_callbacks.elem_size,
                       _sampgdk_callback_compare_bsearch);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback_handler handler) {
  int error;
  struct sampgdk_callback info;
  struct sampgdk_callback *ptr;
 
  assert(name != NULL);
  assert(handler != NULL);

  ptr = sampgdk_callback_find(name);
  if (ptr != NULL) {
    ptr->handler = handler;
    return 0;
  }

  info.name = malloc(strlen(name) + 1);
  if (info.name == NULL) {
    return -ENOMEM;
  }

  info.handler = handler;
  strcpy(info.name, name);

  error = sampgdk_array_insert_ordered(&_sampgdk_callbacks,
                                       &info,
                                       _sampgdk_callback_compare);

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

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    ptr = (const struct sampgdk_callback *)
      sampgdk_array_get(&_sampgdk_callbacks, index);
    if (strcmp(ptr->name, name) == 0) {
      sampgdk_array_remove_single(&_sampgdk_callbacks, index);
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

static bool call_public_filter(void *plugin, AMX *amx, const char *name,
                               cell *retval) {
  void *func;
  cell *params;

  func = sampgdk_plugin_get_symbol(plugin, "OnPublicCall");
  if (func != NULL) {
    typedef bool (PLUGIN_CALL *public_filter)(AMX *amx, const char *name,
                                              cell *params, cell *retval);
    sampgdk_param_get_all(amx, true, &params);
    return ((public_filter)func)(amx, name, params, retval);
  }

  return true;
}

static bool call_public_handler(void *plugin, AMX *amx, const char *name,
                                cell *retval) {
  void *func;
  struct sampgdk_callback *callback;

  func = sampgdk_plugin_get_symbol(plugin, name);
  if (func != NULL) {
    callback = sampgdk_callback_find(name);
    if (callback != NULL) {
      return callback->handler(amx, func, retval);
    }
  }

  return true;
}

bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval) {
  struct sampgdk_plugin_list *plugin_list;
  
  assert(amx != NULL);
  assert(name != NULL);

  plugin_list = sampgdk_plugin_get_list();
  while (plugin_list != NULL) {
    if (call_public_filter(plugin_list->plugin, amx, name, retval) &&
        !call_public_handler(plugin_list->plugin, amx, name, retval)) {
      return false;
    }
    plugin_list = plugin_list->next;
  }

  return true;
}
