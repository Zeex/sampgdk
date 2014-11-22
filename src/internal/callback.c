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

#define _SAMPGDK_CALLBACK_MAX_ARGS 32

typedef bool (PLUGIN_CALL *_sampgdk_callback_filter)(AMX *amx,
                                                     const char *name,
                                                     cell *params,
                                                     cell *retval);

struct _sampgdk_callback_info {
  char *name;
  void *handler;
  struct sampgdk_array cache;
};

struct _sampgdk_callback_cache_entry {
  void *plugin;
  void *func;
};

static struct sampgdk_array _sampgdk_callbacks;

SAMPGDK_MODULE_INIT(callback) {
  int error;

  if (_sampgdk_callbacks.data != NULL) {
    return 0; /* already initialized */
  }

  error = sampgdk_array_new(&_sampgdk_callbacks,
                            1,
                            sizeof(struct _sampgdk_callback_info));
  if (error < 0) {
    return error;
  }

  return sampgdk_callback_register("OnPublicCall", NULL);
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int index;
  struct _sampgdk_callback_info *callback;

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, index);
    sampgdk_array_free(&callback->cache);
    free(callback->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

static int _sampgdk_callback_compare_name(const void *key,
                                          const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct _sampgdk_callback_info *)elem)->name);
}

static int _sampgdk_callback_compare_cache_plugin(const void *key,
                                                  const void *elem) {
  const struct _sampgdk_callback_cache_entry *ce = elem;

  assert(key != NULL);
  assert(elem != NULL);

  if (key < ce->plugin) return -1;
  if (key > ce->plugin) return +1;

  return 0;
}

struct _sampgdk_callback_info *_sampgdk_callback_find(const char *name) {
  assert(name != NULL);
  return bsearch(name, _sampgdk_callbacks.data,
                       _sampgdk_callbacks.count - 1,
                       _sampgdk_callbacks.elem_size,
                       _sampgdk_callback_compare_name);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback handler) {
  int error;
  int index;
  struct _sampgdk_callback_info callback;
  struct _sampgdk_callback_info *ptr;

  assert(name != NULL);

  callback.name = malloc(strlen(name) + 1);
  if (callback.name == NULL) {
    return -ENOMEM;
  }

  callback.handler = handler;
  strcpy(callback.name, name);

  error = sampgdk_array_new(&callback.cache,
                            1,
                            sizeof(struct _sampgdk_callback_cache_entry));
  if (error < 0) {
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
    sampgdk_array_free(&callback.cache);
    free(callback.name);
    return error;
  }

  return error; /* index */
}

void sampgdk_callback_unregister(const char *name) {
  struct _sampgdk_callback_info *callback;

  if ((callback = _sampgdk_callback_find(name)) != NULL) {
    callback->handler = NULL;
  }
}

void sampgdk_callback_cache_plugin(void *plugin) {
  int index;

  assert(plugin != NULL);

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    struct _sampgdk_callback_info *callback =
        sampgdk_array_get(&_sampgdk_callbacks, index);
    struct _sampgdk_callback_cache_entry ce = {
      plugin,
      sampgdk_plugin_get_symbol(plugin, callback->name)
    };
    sampgdk_array_append(&callback->cache, &ce);
  }
}

void sampgdk_callback_uncache_plugin(void *plugin) {
  int index;
  struct _sampgdk_callback_info *callback;

  assert(plugin != NULL);

  for (index = 0; index < _sampgdk_callbacks.count; index++) {
    callback = sampgdk_array_get(&_sampgdk_callbacks, index);
    sampgdk_array_find_remove(&callback->cache,
                              plugin,
                              _sampgdk_callback_compare_cache_plugin);
  }
}

bool sampgdk_callback_invoke(AMX *amx,
                             const char *name,
                             int paramcount,
                             cell *retval) {
  struct _sampgdk_callback_info *callback;
  struct _sampgdk_callback_info *callback_filter;
  int index;
  struct _sampgdk_callback_cache_entry *ce;
  cell params[_SAMPGDK_CALLBACK_MAX_ARGS + 1];

  assert(amx != NULL);
  assert(name != NULL);

  callback = _sampgdk_callback_find(name);
  callback_filter = sampgdk_array_get(&_sampgdk_callbacks,
                                      _sampgdk_callbacks.count - 1);
  assert(callback_filter != NULL);
  assert(callback == NULL
         || callback_filter->cache.count == callback->cache.count);

  if (paramcount > _SAMPGDK_CALLBACK_MAX_ARGS) {
    sampgdk_log_error("Too many callback arguments (at most %d allowed)",
                      _SAMPGDK_CALLBACK_MAX_ARGS);
    return true;
  }

  params[0] = paramcount * sizeof(cell);
  memcpy(&params[1], sampgdk_param_get_start(amx), params[0]);

  for (index = 0; index < callback_filter->cache.count; index++) {
    ce = sampgdk_array_get(&callback_filter->cache, index);
    if (ce->func != NULL
        && !((_sampgdk_callback_filter)ce->func)(amx, name, params, retval)) {
      continue;
    }
    if (callback == NULL || callback->handler == NULL) {
      continue;
    }
    ce = sampgdk_array_get(&callback->cache, index);
    if (ce->func != NULL
        && !((sampgdk_callback)callback->handler)(amx, ce->func, retval)) {
      return false;
    }
  }

  return true;
}
