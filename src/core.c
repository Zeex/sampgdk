/* Copyright (C) 2011-2013 Zeex
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
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>

#include "sdk/amx/amx.h"
#include "private/call.h"
#include "private/log.h"
#include "private/logprintf.h"
#include "private/native.h"
#include "private/plugin.h"
#include "private/timer.h"

extern int module_init(void);
extern void module_cleanup(void);

static void **ppPluginData;

static void init_plugin_data(void **ppData) {
	ppPluginData = ppData;
}

static void init_amx_exports(void **ppData) {
	amx_exports = ppData[PLUGIN_DATA_AMX_EXPORTS];
}

static void init_logprintf(void **ppData) {
	logprintf = ppData[PLUGIN_DATA_LOGPRINTF];
	sampgdk_logprintf  = logprintf;
	sampgdk_vlogprintf = vlogprintf;
}

static int do_init(void **ppData) {
	int error;

	init_plugin_data(ppData);
	init_amx_exports(ppData);
	init_logprintf(ppData);

	error = module_init();
	if (error < 0)
		return error;

	return 0;
}

static void do_cleanup(void) {
	module_cleanup();
}

/* deprecated */
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppData) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_init_plugin(plugin, ppData);
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init(void **ppData) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	return sampgdk_init_plugin(plugin, ppData);
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init_plugin(void *plugin, void **ppData) {
	if (plugin_get_list() == NULL) {
		int error;

		if ((error = do_init(ppData)) < 0) {
			log_error_code(error);
			return error;
		}
	}

	return plugin_register(plugin);
}

/* deprecated */
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize(void) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup(void) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	return sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup_plugin(void *plugin) {
	int error;

	error = plugin_unregister(plugin);
	
	if (plugin_get_list() == NULL) {
		do_cleanup();
	}

	return error;
}

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data(void) {
	return ppPluginData;
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_register_plugin(void *plugin) {
	return plugin_register(plugin);
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin) {
	return plugin_unregister(plugin);
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol) {
	return plugin_address_to_handle(symbol);
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name) {
	return plugin_find_symbol(plugin, name);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers(void) {
	timer_process_timers(NULL);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin) {
	timer_process_timers(plugin);
}

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives(void) {
	return native_get_natives();
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_num_natives(void) {
	return native_get_num_natives();
}

SAMPGDK_EXPORT sampgdk_logprintf_t sampgdk_logprintf = NULL;
SAMPGDK_EXPORT sampgdk_vlogprintf_t sampgdk_vlogprintf = NULL;
