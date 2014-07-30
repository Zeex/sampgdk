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
  int index;
  struct sampgdk_callback *callback;

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, index);
    sampgdk_array_free(&callback->cache->items);
    free(callback->cache);
    free(callback->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

static int _sampgdk_callback_compare_name(const void *key,
                                          const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct sampgdk_callback *)elem)->name);
}

static int _sampgdk_callback_compare_cache_plugin(const void *key,
                                                  const void *elem) {
  const struct _sampgdk_callback_cache_item *item = elem;

  assert(key != NULL);
  assert(elem != NULL);

  if (key < item->plugin) return -1;
  if (key > item->plugin) return +1;

  return 0;
}

struct sampgdk_callback *sampgdk_callback_find(const char *name) {
  assert(name != NULL);
  return bsearch(name, _sampgdk_callbacks.data,
                       _sampgdk_callbacks.count - 1,
                       _sampgdk_callbacks.elem_size,
                       _sampgdk_callback_compare_name);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback_handler handler) {
  int error;
  int index;
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

  /* Keep callbacks ordered by name.
   * This allows us to use binary search in sampgdk_callback_find().
   */
  for (index = 0; index < _sampgdk_callbacks.count - 1; index++) {
    ptr = sampgdk_array_get(&_sampgdk_callbacks, index);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  error = sampgdk_array_insert_single(&_sampgdk_callbacks,
                                      index,
                                      &callback);
  if (error < 0) {
    sampgdk_array_free(&callback.cache->items);
    free(callback.cache);
    free(callback.name);
    return error;
  }

  return error; /* index */
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
  sampgdk_array_find_remove(&_sampgdk_callbacks,
                            name,
                            _sampgdk_callback_compare_name);
}

void sampgdk_callback_unregister_table(const struct sampgdk_callback *table) {
  const struct sampgdk_callback *ptr;

  for (ptr = table; ptr->name != NULL; ptr++) {
    sampgdk_callback_unregister(ptr->name);
  }
}

void sampgdk_callback_scan_plugin(void *plugin) {
  int index;
  struct sampgdk_callback *callback;
  struct _sampgdk_callback_cache_item item = {plugin, NULL};

  assert(plugin != NULL);

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, index);
    item.func = sampgdk_plugin_get_symbol(plugin, callback->name);
    sampgdk_array_append(&callback->cache->items, &item);
  }
}

void sampgdk_callback_forget_plugin(void *plugin) {
  int index;
  struct sampgdk_callback *callback;

  assert(plugin != NULL);

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, index);
    sampgdk_array_find_remove(&callback->cache->items,
                              plugin,
                              _sampgdk_callback_compare_cache_plugin);
  }
}

bool sampgdk_callback_invoke(AMX *amx, const char *name, cell *retval) {
  struct sampgdk_callback *callback;
  struct sampgdk_callback *filter_callback;
  int index;
  struct _sampgdk_callback_cache_item *ci;
  cell *params;

  assert(amx != NULL);
  assert(name != NULL);

  callback = sampgdk_callback_find(name);
  if (callback == NULL || callback->handler == NULL) {
    return true;
  }

  filter_callback = sampgdk_array_get(&_sampgdk_callbacks,
                                      _sampgdk_callbacks.count - 1);
  assert(filter_callback != NULL);
  assert(strcmp(filter_callback->name, _SAMPGDK_PUBLIC_FILTER_NAME) == 0);

  typedef bool (PLUGIN_CALL *filter_func)(
      AMX *amx, const char *name, cell *params, cell *retval);

  sampgdk_param_get_all(amx, true, &params);

  for (index = 0; index < callback->cache->items.count; index++) {
    ci = sampgdk_array_get(&filter_callback->cache->items, index);
    if (ci->func != NULL
        && !((filter_func)ci->func)(amx, name, params, retval)) {
      continue;
    }
    ci = sampgdk_array_get(&callback->cache->items, index);
    if (ci->func != NULL
        && callback->handler != NULL
        && !callback->handler(amx, ci->func, retval)) {
      return false;
    }
  }

  return true;
}
