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
#include <sampgdk/plugin.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <subhook.h>

#include "sdk/amx/amx.h"
#include "callback.h"
#include "fakeamx.h"
#include "init.h"
#include "log.h"
#include "native.h"

/* AMX corresponding to the game mode. */
static AMX *g_main_amx = NULL;

/* The name of the most recently Exec'ed public function. */
static char *g_public_name = NULL;

static struct subhook *amx_FindPublic_hook;
static struct subhook *amx_Exec_hook;
static struct subhook *amx_Register_hook;
static struct subhook *amx_Callback_hook;
static struct subhook *amx_Allot_hook;

/* The "funcidx" native uses amx_FindPublic() to get public function index
 * but our FindPublic always succeeds regardless of public existence, so
 * here's a fixed version.
 *
 * Thanks to Incognito for finding this bug!
 */
static cell AMX_NATIVE_CALL fixed_funcidx(AMX *amx, cell *params) {
	char *funcname;
	int index;
	int error;

	amx_StrParam(amx, params[1], funcname);
	if (funcname == NULL)
		return -1;

	error = amx_FindPublic(amx, funcname, &index);
	if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK))
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
	int error;
	int index;

	subhook_remove(amx_Register_hook);

	for (index = 0; nativelist[index].name != 0 && (index < number || number == -1); ++index)
		native_register(nativelist[index].name, nativelist[index].func);

	/* fix for the funcidx() problem */
	hook_native(amx, "funcidx", fixed_funcidx);

	error = amx_Register(amx, nativelist, number);
	subhook_install(amx_Register_hook);

	return error;
}

/* The SA-MP server always makes a call to amx_FindPublic() and depending on
 * the value returned it may invoke amx_Exec() to call the public function.
 *
 * In order to make it always execute publics regardless of their existence
 * we have to make amx_FindPublic() always return OK.
 */
static int AMXAPI amx_FindPublic_(AMX *amx, const char *name, int *index) {
	int error;
	bool proceed = false;

	subhook_remove(amx_FindPublic_hook);

	/* We are interested in calling publics against two AMX instances:
	 * - the main AMX (the gamemode)
	 * - the fake AMX
	 */
	proceed = (amx == g_main_amx || amx == &fakeamx_global()->amx);

	error = amx_FindPublic(amx, name, index);
	if (error != AMX_ERR_NONE && proceed) {
		/* Trick the server to make it call this public with amx_Exec()
			* even though the public doesn't actually exist.
			*/
		error = AMX_ERR_NONE;
		*index = AMX_EXEC_GDK;
	}

	if (proceed) {
		/* Store the function name in a global string to later access
		 * it in amx_Exec_().
		 */
		if (g_public_name != NULL)
			free(g_public_name);

		if ((g_public_name = malloc(strlen(name) + 1)) == NULL) {
			log_error(strerror(ENOMEM));
			return error;
		}

		strcpy(g_public_name, name);
	}

	subhook_install(amx_FindPublic_hook);

	return error;
}

static int AMXAPI amx_Exec_(AMX *amx, cell *retval, int index) {
	int error;
	bool proceed;

	subhook_remove(amx_Exec_hook);
	subhook_install(amx_Callback_hook);

	proceed = true;

	if (index == AMX_EXEC_MAIN) {
		g_main_amx = amx;
		callback_invoke(g_main_amx, "OnGameModeInit", retval);
	} else {
		if (index != AMX_EXEC_CONT && g_public_name != NULL
				&& (amx == g_main_amx || amx == &fakeamx_global()->amx))
			proceed = callback_invoke(amx, g_public_name, retval);
	}

	error = AMX_ERR_NONE;

	if (proceed && index != AMX_EXEC_GDK)
		error = amx_Exec(amx, retval, index);
	else
		amx->stk += amx->paramcount * sizeof(cell);

	amx->paramcount = 0;

	subhook_remove(amx_Callback_hook);
	subhook_install(amx_Exec_hook);

	return error;
}

static int AMXAPI amx_Callback_(AMX *amx, cell index, cell *result, cell *params) {
	int error;

	subhook_remove(amx_Callback_hook);
	subhook_install(amx_Exec_hook);

	/* Prevent the default AMX callback from replacing SYSREQ.C
	 * instructions with SYSREQ.D.
	 */
	amx->sysreq_d = 0;

	error = amx_Callback(amx, index, result, params);

	subhook_remove(amx_Exec_hook);
	subhook_install(amx_Callback_hook);

	return error;
}

static int AMXAPI amx_Allot_(AMX *amx, int cells, cell *amx_addr, cell **phys_addr) {
	int error;

	subhook_remove(amx_Allot_hook);

	/* There is a bug in amx_Allot() where it returns success even though
	 * there's not enough space on the heap:
	 *
	 * if (amx->stk - amx->hea - cells*sizeof(cell) < STKMARGIN)
     *   return AMX_ERR_MEMORY;
	 *
	 * The expression on the right side of the comparison is converted
	 * to an unsigned type (because result of sizeof is of type size_t).
	 * and in fact never results in a negative value. 
	 */
	#define STKMARGIN (cell)(16 * sizeof(cell))
	if ((size_t)amx->stk < (size_t)(amx->hea + cells*sizeof(cell) + STKMARGIN))
		error =  AMX_ERR_MEMORY;
	else
		error = amx_Allot(amx, cells, amx_addr, phys_addr);

	/* If failing to allocate on the fake AMX heap, resize the heap
	 * automatically.
	 */
	if (error == AMX_ERR_MEMORY && amx == &fakeamx_global()->amx) {
		cell new_size;

		/* STKMARGIN + 2 is here to stop amx_Push() from thinking that there's
		 * no space left on the stack.
		 */
		new_size = ((amx->hea + STKMARGIN) / sizeof(cell)) + cells + 2;

		if (fakeamx_resize_heap(fakeamx_global(), new_size) >= 0)
			error = amx_Allot(amx, cells, amx_addr, phys_addr);
	}

	subhook_install(amx_Allot_hook);

	return error;
}

#define CREATE_HOOK(name, failure_label) \
	if ((amx_##name##_hook = subhook_new()) == NULL) \
		goto failure_label;

#define DESTROY_HOOK(name) \
	subhook_free(amx_##name##_hook); \

#define INSTALL_HOOK(name) \
	subhook_set_src(amx_##name##_hook, ((void**)(amx_exports))[PLUGIN_AMX_EXPORT_##name]); \
	subhook_set_dst(amx_##name##_hook, (void*)amx_##name##_); \
	subhook_install(amx_##name##_hook);

#define REMOVE_HOOK(name)\
	subhook_remove(amx_##name##_hook); \

static int create_hooks(void) {
	CREATE_HOOK(Register, no_memory);
	CREATE_HOOK(FindPublic, no_memory);
	CREATE_HOOK(Exec, no_memory);
	CREATE_HOOK(Callback, no_memory);
	CREATE_HOOK(Allot, no_memory);
	return 0;
no_memory:
	return -ENOMEM;
}

static void destroy_hooks(void) {
	DESTROY_HOOK(Register);
	DESTROY_HOOK(FindPublic);
	DESTROY_HOOK(Exec);
	DESTROY_HOOK(Callback);
	DESTROY_HOOK(Allot);
}

static void install_hooks(void) {
	INSTALL_HOOK(Register);
	INSTALL_HOOK(FindPublic);
	INSTALL_HOOK(Exec);
	INSTALL_HOOK(Callback);
	INSTALL_HOOK(Allot);
}

static void remove_hooks(void) {
	REMOVE_HOOK(Register);
	REMOVE_HOOK(FindPublic);
	REMOVE_HOOK(Exec);
	REMOVE_HOOK(Callback);
	REMOVE_HOOK(Allot);
}

DEFINE_INIT_FUNC(hooks_init) {
	int error;

	error = create_hooks();
	if (error < 0) {
		destroy_hooks();
		return error;
	}

	install_hooks();

	return 0;
}

DEFINE_CLEANUP_FUNC(hooks_cleanup) {
	remove_hooks();
}
