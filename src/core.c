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

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <subhook.h>

#include "call.h"
#include "callback.h"
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

static AMX  *gamemode_amx = 0;
static char *current_public;

static struct subhook *amx_FindPublic_hook;
static struct subhook *amx_Exec_hook;
static struct subhook *amx_Register_hook;
static struct subhook *amx_Callback_hook;

/* The "funcidx" native uses amx_FindPublic() to get public function index
 * but our FindPublic always succeeds regardless of public existence, so
 * here's a fixed version.
 *
 * Thanks to Incognito for finding this bug!
 */
static cell AMX_NATIVE_CALL fixed_funcidx(AMX *amx, cell *params) {
	char *funcname;
	int index;
	int error_code;

	amx_StrParam(amx, params[1], funcname);
	if (funcname == NULL)
		return -1;

	error_code = amx_FindPublic(amx, funcname, &index);
	if (error_code != AMX_ERR_NONE || (error_code == AMX_ERR_NONE && index == AMX_EXEC_GDK))
		return -1;

	return index;
}

static void hook_native(AMX *amx, const char *name, AMX_NATIVE address) {
	AMX_HEADER *hdr;
	AMX_FUNCSTUBNT *cur;
	AMX_FUNCSTUBNT *end;

	hdr = (AMX_HEADER*)(amx->base);
	cur = (AMX_FUNCSTUBNT*)(amx->base + hdr->natives);
	end = (AMX_FUNCSTUBNT*)(amx->base + hdr->libraries);

	while (cur < end) {
		if (strcmp((char*)(cur->nameofs + amx->base), name) == 0) {
			cur->address = (cell)address;
			break;
		}
		cur++;
	}
}

static int AMXAPI amx_Register_(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	int error_code;
	int index;

	subhook_remove(amx_Register_hook);

	for (index = 0; nativelist[index].name != 0 && (index < number || number == -1); ++index)
		native_register(nativelist[index].name, nativelist[index].func);

	/* fix for the funcidx() problem */
	hook_native(amx, "funcidx", fixed_funcidx);

	error_code = amx_Register(amx, nativelist, number);
	subhook_install(amx_Register_hook);

	return error_code;
}

/* The SA-MP server always makes a call to amx_FindPublic() and depending on
 * the value returned it may invoke amx_Exec() to call the public function.
 *
 * In order to make it always execute publics regardless of their existence
 * we have to make amx_FindPublic() always return OK.
 */
static int AMXAPI amx_FindPublic_(AMX *amx, const char *name, int *index) {
	int error_code;

	subhook_remove(amx_FindPublic_hook);

	error_code = amx_FindPublic(amx, name, index);

	if (amx == gamemode_amx) {
		if (error_code != AMX_ERR_NONE) {
			error_code = AMX_ERR_NONE;
			*index = AMX_EXEC_GDK;
		}

		/* Store the function name in a global string to be able
		 * to access it from amx_Exec_.
		 */
		if (current_public != NULL)
			free(current_public);

		if ((current_public = malloc(strlen(name) + 1)) == NULL) {
			error(strerror(ENOMEM));
			return error_code;
		}

		strcpy(current_public, name);
	}

	subhook_install(amx_FindPublic_hook);

	return error_code;
}

static int AMXAPI amx_Exec_(AMX *amx, cell *retval, int index) {
	int error_code;
	bool can_exec;

	subhook_remove(amx_Exec_hook);
	subhook_install(amx_Callback_hook);

	can_exec = true;

	if (index == AMX_EXEC_MAIN) {
		gamemode_amx = amx;
		callback_invoke(gamemode_amx, "OnGameModeInit", retval);
	} else {
		if (amx == gamemode_amx && index != AMX_EXEC_CONT && current_public != NULL)
			can_exec = callback_invoke(gamemode_amx, current_public, retval);
	}

	error_code = AMX_ERR_NONE;

	if (can_exec && index != AMX_EXEC_GDK)
		error_code = amx_Exec(amx, retval, index);
	else
		amx->stk += amx->paramcount * sizeof(cell);

	amx->paramcount = 0;

	subhook_remove(amx_Callback_hook);
	subhook_install(amx_Exec_hook);

	return error_code;
}

static int AMXAPI amx_Callback_(AMX *amx, cell index, cell *result, cell *params) {
	int error_code;

	subhook_remove(amx_Callback_hook);
	subhook_install(amx_Exec_hook);

	/* Prevent the default AMX callback from replacing SYSREQ.C
	 * instructions with SYSREQ.D.
	 */
	amx->sysreq_d = 0;

	error_code = amx_Callback(amx, index, result, params);

	subhook_remove(amx_Exec_hook);
	subhook_install(amx_Callback_hook);

	return error_code;
}

static void remove_hooks() {
	if (amx_Register_hook != NULL) {
		subhook_remove(amx_Register_hook);
		subhook_free(amx_Register_hook);
	}
	if (amx_FindPublic_hook != NULL) {
		subhook_remove(amx_FindPublic_hook);
		subhook_free(amx_FindPublic_hook);
	}
	if (amx_Exec_hook != NULL) {
		subhook_remove(amx_Exec_hook);
		subhook_free(amx_Exec_hook);
	}
	if (amx_Callback_hook != NULL) {
		subhook_remove(amx_Callback_hook);
		subhook_free(amx_Callback_hook);
	}
}

static int install_hooks() {
	if ((amx_Register_hook = subhook_new()) == NULL)
		goto no_memory;
	if ((amx_FindPublic_hook = subhook_new()) == NULL)
		goto no_memory;
	if ((amx_Exec_hook = subhook_new()) == NULL)
		goto no_memory;
	if ((amx_Callback_hook = subhook_new()) == NULL)
		goto no_memory;

	SUBHOOK_INSTALL_HOOK(
		amx_Register_hook,
		((void**)(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register],
		(void*)amx_Register_
	);
	SUBHOOK_INSTALL_HOOK(
		amx_FindPublic_hook,
		((void**)(pAMXFunctions))[PLUGIN_AMX_EXPORT_FindPublic],
		(void*)amx_FindPublic_
	);
	SUBHOOK_INSTALL_HOOK(
		amx_Exec_hook,
		((void**)(pAMXFunctions))[PLUGIN_AMX_EXPORT_Exec],
		(void*)amx_Exec_
	);
	SUBHOOK_INSTALL_HOOK(
		amx_Callback_hook,
		((void**)(pAMXFunctions))[PLUGIN_AMX_EXPORT_Callback],
		(void*)amx_Callback_
	);

	return 0;

no_memory:
	remove_hooks();
	return -ENOMEM;
}

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
	if ((error_code = install_hooks()) < 0)
		goto install_hooks_failed;
	if ((error_code = callback_init()) < 0)
		goto callback_init_failed;
	if ((error_code = native_init()) < 0)
		goto native_init_failed;
	if ((error_code = timer_init()) < 0)
		goto timer_init_failed;

	goto out;

timer_init_failed:
	timer_cleanup();
native_init_failed:
	native_cleanup();
callback_init_failed:
	callback_cleanup();
install_hooks_failed:
	remove_hooks();
register_callbacks_failed:
	error(strerror(-error_code));
	return error_code;

out:
	return 0;
}

static void do_cleanup() {
	timer_cleanup();
	native_cleanup();
	callback_cleanup();
	remove_hooks();
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
