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

#include <sampgdk/bool.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "plugin.h"

static struct plugin_list *plugins;

void plugin_register(void *plugin) {
	struct plugin_list *ptr;

	assert(plugin != NULL);

	if (plugin_is_registered(plugin))
		return;

	ptr = malloc(sizeof(*ptr));
	ptr->plugin = plugin;
	ptr->next = plugins;

	plugins = ptr;
}

bool plugin_unregister(void *plugin) {
	struct plugin_list *prev;
	struct plugin_list *cur;

	assert(plugin != NULL);

	cur = plugins;
	prev = NULL;

	while (cur != NULL) {
		if (cur->plugin == plugin) {
			if (prev != NULL)
				prev->next = cur->next;
			free(cur);
			return true;
		}
	}

	return false;
}

bool plugin_is_registered(void *plugin) {
	struct plugin_list *cur;

	assert(plugin != NULL);

	cur = plugins;

	while (cur != NULL) {
		if (cur->plugin == plugin)
			return true;
		cur = cur->next;
	}

	return false;
}

struct plugin_list *plugin_get_list() {
	return plugins;
}
