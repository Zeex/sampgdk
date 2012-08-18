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

#include <sampgdk/config.h>
#include <sampgdk/amx.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include <stdlib.h>
#include <string.h>

#include "callback.h"
#include "plugin.h"
#include "util.h"

#include "generated/callback-handlers.c"

struct handler_list {
	callback_handler     handler;
	struct handler_list *next;
	char                 name[1];
};

static struct handler_list *handlers;

void callback_init() {
	register_callback_handlers();
}

void callback_cleanup() {
	struct handler_list *cur;
	struct handler_list *tmp;

	cur = handlers;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void callback_add_handler(const char *name, callback_handler handler) {
	struct handler_list *ptr;

	ptr = malloc(sizeof(*ptr) + strlen(name));
	ptr->handler = handler;
	ptr->next = handlers;
	strcpy(ptr->name, name);

	handlers = ptr;
}

bool callback_invoke(AMX *amx, const char *name, cell *retval) {
	struct plugin_list *plugin;

	for (plugin = plugin_get_list(); plugin != NULL; plugin = plugin->next) {
		void *func;
		struct handler_list *handler;

		func = plugin_find_symbol(plugin->plugin, name);
		if (func == NULL)
			continue;

		for (handler = handlers; handler != NULL; handler = handler->next) {
			if (strcmp(handler->name, name) == 0) {
				if (!handler->handler(amx, func, retval))
					return false;
				continue;
			}
		}
	}

	return true;
}
