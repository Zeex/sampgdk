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

static cell read_amx_stack_cell(AMX *amx, int index);
static bool read_amx_stack_bool(AMX *amx, int index);
static float read_amx_stack_float(AMX *amx, int index);
static char *read_amx_stack_string(AMX *amx, int index);

#include "generated/callback-handlers.c"

struct handler_list {
	callback_handler     handler;
	struct handler_list *next;
	char                 name[1];
};

static struct handler_list *handlers;

static unsigned char *get_data_ptr(AMX *amx) {
	return amx->data != 0 
		? amx->data 
		: amx->base + ((AMX_HEADER*)amx->base)->dat;
}

static cell *get_stack_ptr(AMX *amx) {
	return (cell*)(get_data_ptr(amx) + amx->stk);
}

static cell read_amx_stack_cell(AMX *amx, int index) {
	return get_stack_ptr(amx)[index];
}

static bool read_amx_stack_bool(AMX *amx, int index) {
	return (bool)read_amx_stack_cell(amx, index);
}

static float read_amx_stack_float(AMX *amx, int index) {
	cell value;

	value = read_amx_stack_cell(amx, index);
	return amx_ctof(value);
}

static char *read_amx_stack_string(AMX *amx, int index) {
	cell amx_addr;
	cell *phys_addr;
	int length;
	char *string;
	
	amx_addr = read_amx_stack_cell(amx, index);
	if (amx_GetAddr(amx, amx_addr, &phys_addr) != AMX_ERR_NONE) {
		return NULL;
	}
	
	amx_StrLen(phys_addr, &length);
	string = malloc((length + 1) * sizeof(char));
	
	if (amx_GetString(string, phys_addr, 0, length + 1) != AMX_ERR_NONE) {
		free(string);
		return NULL;
	}

	return string;
}

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
