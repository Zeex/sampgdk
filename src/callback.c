/* Copyright (C) 2012 Zeex
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

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "callback.h"
#include "likely.h"
#include "plugin.h"

static struct array handlers;

int callback_init() {
	return array_new(&handlers, 1, sizeof(struct callback_info));
}

void callback_cleanup() {
	int i;

	for (i = 0; i < handlers.count; i++) {
		struct callback_info *info =
			(struct callback_info *)array_get(&handlers, i);
		free(info->name);
	}

	array_free(&handlers);
}

int callback_set_handler(const char *name, callback_handler handler) {
	int error;
	struct callback_info info;
	struct callback_info *ptr;
	
	ptr = callback_find(name);
	if (ptr != NULL) {
		ptr->handler = handler;
		return 0;
	}

	info.name = malloc(strlen(name) + 1);
	if (info.name == NULL)
		return -ENOMEM;

	strcpy(info.name, name);
	info.handler = handler;

	error = array_append(&handlers, &info);
	if (error < 0) {
		free(info.name);
		return error;
	}

	return 0;
}

static int compare_info(const void *key, const void *elem) {
	return strcmp((const char *)key,
	              ((const struct callback_info *)elem)->name);
}

struct callback_info *callback_find(const char *name) {
	return bsearch(name, handlers.data, handlers.count,
	               handlers.elem_size, compare_info);
}

bool callback_invoke(AMX *amx, const char *name, cell *retval) {
	struct plugin_list *plugin;

	for (plugin = plugin_get_list(); plugin != NULL; plugin = plugin->next) {
		void *func;
		struct callback_info *info;
		callback_handler handler;

		func = plugin_find_symbol(plugin->plugin, name);
		if (func == NULL)
			continue;

		info = callback_find(name);
		if (info == NULL)
			continue;

		handler = info->handler;
		if (handler == NULL)
			continue;

		/* If the callback handler returns false, the call chain
		 * should be interrupted.
		 */
		if (!handler(amx, func, retval))
			return false;
	}

	return true;
}
