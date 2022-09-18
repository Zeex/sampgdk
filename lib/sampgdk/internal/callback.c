/* Copyright (C) 2012-2017 Zeex
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

typedef bool (PLUGIN_CALL *_sampgdk_callback_filter)(
    AMX *amx,
    const char *name,
    cell *params,
    cell *retval);
typedef bool (PLUGIN_CALL *_sampgdk_callback_filter2)(
    AMX *amx,
    const char *name,
    cell *params,
    cell *retval,
    bool *stop);

struct _sampgdk_callback_info {
  char *name;
  char *func_name;
  void *handler;
};

static struct sampgdk_array _sampgdk_callbacks;

static int _sampgdk_callback_compare_name(const void *key,
                                          const void *elem) {
  assert(key != NULL);
  assert(elem != NULL);
  return strcmp((const char *)key,
                ((const struct _sampgdk_callback_info *)elem)->name);
}

static struct _sampgdk_callback_info *_sampgdk_callback_find(const char *name) {
  assert(name != NULL);

  if (_sampgdk_callbacks.count <= 0) {
    return NULL;
  }

  return (struct _sampgdk_callback_info *)bsearch(name,
                 _sampgdk_callbacks.data,
                 _sampgdk_callbacks.count,
                 _sampgdk_callbacks.elem_size,
                 _sampgdk_callback_compare_name);
}

SAMPGDK_MODULE_INIT(callback) {
  int error;

  error = sampgdk_array_new(&_sampgdk_callbacks,
                            32,
                            sizeof(struct _sampgdk_callback_info));
  if (error < 0) {
    return error;
  }

  error = sampgdk_callback_register(":OnPublicCall", NULL);
  if (error < 0) {
    return error;
  }

  error = sampgdk_callback_register(":OnPublicCall2", NULL);
  if (error < 0) {
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(callback) {
  int i;
  struct _sampgdk_callback_info *callback;

  for (i = 0; i < _sampgdk_callbacks.count; i++) {
    callback = (struct _sampgdk_callback_info *)sampgdk_array_get(&_sampgdk_callbacks, i);
    free(callback->name);
  }

  sampgdk_array_free(&_sampgdk_callbacks);
}

int sampgdk_callback_register(const char *name,
                              sampgdk_callback handler) {
  int error;
  int count;
  int i;
  struct _sampgdk_callback_info callback;
  struct _sampgdk_callback_info *ptr;

  assert(name != NULL);

  ptr = _sampgdk_callback_find(name);
  if (ptr != NULL) {
    return sampgdk_array_get_index(&_sampgdk_callbacks, ptr);
  }

  callback.handler = (void *)handler;

  callback.name = (char *)malloc(strlen(name) + 1);
  if (callback.name == NULL) {
    return -ENOMEM;
  }

  strcpy(callback.name, name);

  if (callback.name[0] == ':') {
    /* Special callbacks have a name that begins with ':'. This is to ensure
     * that their name is not used by SA-MP or user scripts.
     */
    callback.func_name = callback.name + 1;
  } else {
    callback.func_name = callback.name;
  }

  /* Keep callbacks ordered by name.
   * This allows us to use binary search when searching through callbacks.
   */
  count = _sampgdk_callbacks.count;
  for (i = 0; i < count; i++) {
    ptr = (struct _sampgdk_callback_info *)sampgdk_array_get(
        &_sampgdk_callbacks, i);
    if (strcmp(name, ptr->name) <= 0) {
      break;
    }
  }

  error = sampgdk_array_insert(&_sampgdk_callbacks, i, 1, &callback);
  if (error < 0) {
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

bool sampgdk_callback_get(int index, char **name) {
  struct _sampgdk_callback_info *callback;

  assert(name != NULL);

  if (index < 0 || index >= _sampgdk_callbacks.count) {
    return false;
  }

  callback = (struct _sampgdk_callback_info *)sampgdk_array_get(
      &_sampgdk_callbacks, index);
  *name = callback->name;

  return true;
}

bool sampgdk_callback_invoke(AMX *amx,
                             const char *name,
                             int paramcount,
                             cell *retval)
{
  cell params[_SAMPGDK_CALLBACK_MAX_ARGS + 1];
  void **plugins;
  int num_plugins;
  int i;

  assert(amx != NULL);

  if (paramcount > _SAMPGDK_CALLBACK_MAX_ARGS) {
    sampgdk_log_error("Too many callback arguments (at most %d allowed)",
                      _SAMPGDK_CALLBACK_MAX_ARGS);
    return true;
  }

  params[0] = paramcount * sizeof(cell);
  memcpy(&params[1], sampgdk_param_get_start(amx), params[0]);

  plugins = sampgdk_plugin_get_plugins(&num_plugins);

  for (i = 0; i < num_plugins; i++) {
    void *plugin = plugins[i];
    struct _sampgdk_callback_info *callback;
    struct _sampgdk_callback_info *callback_filter;
    struct _sampgdk_callback_info *callback_filter2;
    void *func;
    bool do_call = true;
    bool stop = false;

    callback_filter = _sampgdk_callback_find(":OnPublicCall");
    assert(callback_filter != NULL);
    
    func = sampgdk_plugin_get_symbol(plugin, callback_filter->func_name);
    if (func != NULL) {
      do_call = ((_sampgdk_callback_filter)func)(amx, name, params, retval);
    }

    /* callback_filter2 is similar to callback_filter except it can stop
     * propagation of public call to other plugins. It was added for backwards
     * compatibility.
     *
     * callback_filter2's return value overrides that of callback_filter.
     */
    callback_filter2 = _sampgdk_callback_find(":OnPublicCall2");
    assert(callback_filter2 != NULL);
    
    func = sampgdk_plugin_get_symbol(plugin, callback_filter2->func_name);
    if (func != NULL) {
      do_call = !((_sampgdk_callback_filter2)func)(amx,
                                                   name,
                                                   params,
                                                   retval,
                                                   &stop);
    }

    if (stop) {
      return false;
    }

    if (!do_call) {
      continue;
    }

    callback = _sampgdk_callback_find(name);
    if (callback == NULL || callback->handler == NULL) {
      continue;
    }
    
    func = sampgdk_plugin_get_symbol(plugin, callback->func_name);
    if (func != NULL
        && !((sampgdk_callback)callback->handler)(amx, func, retval)) {
      return false;
    }
  }

  return true;
}
