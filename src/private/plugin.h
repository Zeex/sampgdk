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

#ifndef SAMPGDK_PLUGIN_H_
#define SAMPGDK_PLUGIN_H_

#include <sampgdk/bool.h>

#include <stddef.h>

struct plugin_list {
	void               *plugin;
	struct plugin_list *next;
};

/* Registers a plugin (for notifying it about SA-MP events, etc). If the
 * plugin happens to be already registered nothing no action taken.
 *
 * This functions walks through the list of registered plugins and compares
 * their handles with the given one so it's O(n).
 */
int plugin_register(void *plugin);

/* Opposite of plugin_register(). 
 */
int plugin_unregister(void *plugin);

/* Checks if a plugin was registered with plugin_register().
 */
bool plugin_is_registered(void *plugin);

/* Returns address of a symbol (variable or function) or NULL if not found.
 */
void *plugin_find_symbol(void *plugin, const char *name);

/* Returns a handle of the module (plugin) to which the specified address
 * belongs to.
 */
void *plugin_address_to_handle(void *address);

/* Returns a full path of the module (plugin) to which the specified address
 * belongs to.
 */ 
void plugin_address_to_filename(void *address, char *filename, size_t size);

/* Returns the list of currently registered plugins. 
 */
struct plugin_list *plugin_get_list();

#endif /* !SAMPGDK_PLUGIN_H_ */
