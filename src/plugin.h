/* Copyright (C) 2011-2012 Zeex
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

struct plugin_list {
	void               *plugin;
	struct plugin_list *next;
};

void plugin_register(void *plugin);
bool plugin_unregister(void *plugin);
struct plugin_list *plugin_get_list();

void *plugin_find_symbol(void *plugin, const char *name);
void *plugin_address_to_handle(void *address);

#endif /* !SAMPGDK_PLUGIN_H_ */
