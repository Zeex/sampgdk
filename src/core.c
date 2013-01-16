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

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>

#include <errno.h>
#include <string.h>

#include "call.h"
#include "callback.h"
#include "hooks.h"
#include "log.h"
#include "logprintf.h"
#include "native.h"
#include "plugin.h"
#include "timer.h"

extern int register_callbacks__a_samp();
extern int register_callbacks__a_players();
extern int register_callbacks__a_objects();
extern int register_callbacks__a_vehicles();

extern void *pAMXFunctions;
static void **ppPluginData;

static int register_callbacks() {
	int error_code;

	if ((error_code = register_callbacks__a_samp()) < 0)
		return error_code;
	if ((error_code = register_callbacks__a_players()) < 0)
		return error_code;
	if ((error_code = register_callbacks__a_objects()) < 0)
		return error_code;
	if ((error_code = register_callbacks__a_vehicles()) < 0)
		return error_code;

	return 0;
}

static void init_plugin_data(void **ppData) {
	ppPluginData = ppData;
}

static void init_amx_exports(void **ppData) {
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
}

static void init_logprintf(void **ppData) {
	logprintf = ppData[PLUGIN_DATA_LOGPRINTF];
	sampgdk_logprintf  = logprintf;
	sampgdk_vlogprintf = vlogprintf;
}

static int do_init(void **ppData) {
	int error_code;

	init_plugin_data(ppData);
	init_amx_exports(ppData);
	init_logprintf(ppData);

	if ((error_code = register_callbacks()) < 0)
		goto register_callbacks_failed;
	if ((error_code = callback_init()) < 0)
		goto callback_init_failed;
	if ((error_code = native_init()) < 0)
		goto native_init_failed;
	if ((error_code = timer_init()) < 0)
		goto timer_init_failed;
	if ((error_code = hooks_init()) < 0)
		goto hooks_init_failed;

	goto out;

hooks_init_failed:
	hooks_cleanup();
timer_init_failed:
	timer_cleanup();
native_init_failed:
	native_cleanup();
callback_init_failed:
	callback_cleanup();
register_callbacks_failed:
	error(strerror(-error_code));
	return error_code;

out:
	return 0;
}

static void do_cleanup() {
	hooks_cleanup();
	timer_cleanup();
	native_cleanup();
	callback_cleanup();
}

/* deprecated */
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppData) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_init_plugin(plugin, ppData);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_init(void **ppData) {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_init_plugin(plugin, ppData);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_init_plugin(void *plugin, void **ppData) {
	if (plugin_get_list() == NULL) {
		do_init(ppData);
	}
	plugin_register(plugin);
}

/* deprecated */
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize() {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_cleanup() {
	void *plugin;

	plugin = plugin_address_to_handle(get_ret_addr(NULL, 0));
	sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_cleanup_plugin(void *plugin) {
	if (plugin_get_list() == NULL) {
		do_cleanup();
	}
	plugin_unregister(plugin);
}

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data() {
	return ppPluginData;
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_register_plugin(void *plugin) {
	plugin_register(plugin);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin) {
	plugin_unregister(plugin);
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol) {
	return plugin_address_to_handle(symbol);
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name) {
	return plugin_find_symbol(plugin, name);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers() {
	timer_process_timers(NULL);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin) {
	timer_process_timers(plugin);
}

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives() {
	return native_get_natives();
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_num_natives() {
	return native_get_num_natives();
}

SAMPGDK_EXPORT sampgdk_logprintf_t sampgdk_logprintf = NULL;
SAMPGDK_EXPORT sampgdk_vlogprintf_t sampgdk_vlogprintf = NULL;
