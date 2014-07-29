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
#include "log.h"
#include "param.h"
#include "plugin.h"

#define _SAMPGDK_PUBLIC_FILTER_NAME "OnPublicCall"

static struct sampgdk_array _sampgdk_callbacks;

struct _sampgdk_callback_cache_item {
  void *plugin;
  void *func;
};

struct _sampgdk_callback_cache {
  struct sampgdk_array items;
};

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

  return sampgdk_callback_register(_SAMPGDK_PUBLIC_FILTER_NAME, NULL);
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int i;
  struct sampgdk_callback *callback;

  for (i = 0; i < _sampgdk_callbacks.count; i++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, i);
    sampgdk_array_free(&callback->cache->items);
    free(callback->cache);
    free(callback->name);
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
  struct sampgdk_callback callback;
  struct sampgdk_callback *ptr;

  assert(name != NULL);

  ptr = sampgdk_callback_find(name);
  if (ptr != NULL) {
    ptr->handler = handler;
    return 0;
  }

  callback.name = malloc(strlen(name) + 1);
  if (callback.name == NULL) {
    return -ENOMEM;
  }

  callback.handler = handler;
  strcpy(callback.name, name);

  callback.cache = calloc(1, sizeof(struct sampgdk_array));
  if (callback.cache == NULL) {
    free(callback.name);
    return -ENOMEM;
  }

  error = sampgdk_array_new(&callback.cache->items,
                            1,
                            sizeof(struct _sampgdk_callback_cache_item));
  if (error < 0) {
    free(callback.cache);
    free(callback.name);
    return error;
  }

  error = sampgdk_array_insert_ordered(&_sampgdk_callbacks,
                                       &callback,
                                       _sampgdk_callback_compare);

  if (error < 0) {
    sampgdk_array_free(&callback.cache->items);
    free(callback.cache);
    free(callback.name);
    return error;
  }

  return error; /* i */
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
  int i;
  const struct sampgdk_callback *callback;

  for (i = 0; i < _sampgdk_callbacks.count; i++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, i);
    if (strcmp(callback->name, name) == 0) {
      sampgdk_array_remove_single(&_sampgdk_callbacks, i);
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

void sampgdk_callback_scan_plugin(void *plugin) {
  int i;
  struct sampgdk_callback *callback;
  struct _sampgdk_callback_cache_item item = {plugin, NULL};

  assert(plugin != NULL);

  for (i = 0; i < _sampgdk_callbacks.count; i++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, i);
    item.func = sampgdk_plugin_get_symbol(plugin, callback->name);
    sampgdk_array_append(&callback->cache->items, &item);
  }
}

bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval) {
  struct sampgdk_callback *callback;
  struct sampgdk_callback *filter_callback;
  int i;
  struct _sampgdk_callback_cache_item *ci;
  cell *params;

  assert(amx != NULL);
  assert(name != NULL);

  callback = sampgdk_callback_find(name);
  if (callback == NULL || callback->handler == NULL) {
    return true;
  }

  filter_callback = sampgdk_callback_find(_SAMPGDK_PUBLIC_FILTER_NAME);
  assert(filter_callback != NULL);

  typedef bool (PLUGIN_CALL *filter_func)(
      AMX *amx, const char *name, cell *params, cell *retval);

  sampgdk_param_get_all(amx, true, &params);

  for (i = 0; i < callback->cache->items.count; i++) {
    ci = sampgdk_array_get(&filter_callback->cache->items, i);
    if (ci->func != NULL
        && !((filter_func)ci->func)(amx, name, params, retval)) {
      continue;
    }
    ci = sampgdk_array_get(&callback->cache->items, i);
    if (ci->func != NULL
        && callback->handler != NULL
        && !callback->handler(amx, ci->func, retval)) {
      return false;
    }
  }

  return true;
}
