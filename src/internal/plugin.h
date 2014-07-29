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

#ifndef SAMPGDK_INTERNAL_PLUGIN_H
#define SAMPGDK_INTERNAL_PLUGIN_H

#include <stddef.h>

#include <sampgdk/bool.h>

struct sampgdk_plugin {
  void *handle;
};

int sampgdk_plugin_register(void *handle);
int sampgdk_plugin_unregister(void *handle);
void *sampgdk_plugin_get_symbol(void *handle, const char *name);
void *sampgdk_plugin_get_handle(void *address);
void sampgdk_plugin_get_filename(void *address, char *filename, size_t size);
struct sampgdk_plugin *sampgdk_plugin_table(int *number);
int sampgdk_plugin_count(void);

#endif /* !SAMPGDK_INTERNAL_PLUGIN_H */
