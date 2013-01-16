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
#include <sampgdk/plugin.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <subhook.h>

#include "callback.h"
#include "log.h"
#include "native.h"

/* Defined in "amxplugin.c". */
extern void *pAMXFunctions;

/* AMX corresponding to the game mode. */
static AMX *g_main_amx = NULL;

/* The name of the most recently Exec'ed public function. */
static char *g_public_name = NULL;

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

	if (amx == g_main_amx) {
		if (error_code != AMX_ERR_NONE) {
			error_code = AMX_ERR_NONE;
			*index = AMX_EXEC_GDK;
		}

		/* Store the function name in a global string to be able
		 * to access it from amx_Exec_.
		 */
		if (g_public_name != NULL)
			free(g_public_name);

		if ((g_public_name = malloc(strlen(name) + 1)) == NULL) {
			error(strerror(ENOMEM));
			return error_code;
		}

		strcpy(g_public_name, name);
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
		g_main_amx = amx;
		callback_invoke(g_main_amx, "OnGameModeInit", retval);
	} else {
		if (amx == g_main_amx && index != AMX_EXEC_CONT && g_public_name != NULL)
			can_exec = callback_invoke(g_main_amx, g_public_name, retval);
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

int hooks_init() {
	int error_code;

	if ((error_code = install_hooks()) < 0)
		remove_hooks();

	return error_code;
}

void hooks_cleanup() {
	remove_hooks();
}
