/* Copyright (C) 2012-2015 Zeex
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

#include <sampgdk/bool.h>

int sampgdk_plugin_register(void *plugin);
int sampgdk_plugin_unregister(void *plugin);

void *sampgdk_plugin_get_symbol(void *plugin, const char *name);
void *sampgdk_plugin_get_handle(void *address);

/* Returns all currently registered plugins. */
void **sampgdk_plugin_get_plugins(int *number);

#endif /* !SAMPGDK_INTERNAL_PLUGIN_H */
