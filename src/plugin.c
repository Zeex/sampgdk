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

#include "plugin.h"

static struct sampgdk_plugin_list *plugins;

int sampgdk_plugin_register(void *plugin) {
  struct sampgdk_plugin_list *ptr;

  assert(plugin != NULL);

  if (sampgdk_plugin_is_registered(plugin)) {
    return -EINVAL;
  }

  ptr = malloc(sizeof(*ptr));
  if (ptr == NULL) {
    return -ENOMEM;
  }

  ptr->plugin = plugin;
  ptr->next = plugins;
  plugins = ptr;

  return 0;
}

int sampgdk_plugin_unregister(void *plugin) {
  struct sampgdk_plugin_list *prev;
  struct sampgdk_plugin_list *cur;

  assert(plugin != NULL);

  cur = plugins;
  prev = NULL;

  while (cur != NULL) {
    if (cur->plugin != plugin) {
      continue;
    }

    if (prev != NULL) {
      prev->next = cur->next;
    } else {
      assert(plugins == cur);
      plugins = cur->next;
    }

    free(cur);
    return 0;
  }

  return -EINVAL;
}

bool sampgdk_plugin_is_registered(void *plugin) {
  struct sampgdk_plugin_list *cur;

  assert(plugin != NULL);

  cur = plugins;

  while (cur != NULL) {
    if (cur->plugin == plugin) {
      return true;
    }
    cur = cur->next;
  }

  return false;
}

struct sampgdk_plugin_list *sampgdk_plugin_get_list(void) {
  return plugins;
}
