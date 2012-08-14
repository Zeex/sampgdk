// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <vector>

#include <sampgdk/config.h>
#include <sampgdk/core.h>
#include <sampgdk/export.h>
#include <sampgdk/plugin.h>

#include "callbacks.h"
#include "hook.h"
#include "natives.h"
#include "timers.h"

extern void *pAMXFunctions;

namespace {

	void **ppPluginData;

	AMX *gamemode_amx = 0;

	std::string current_public;

	sampgdk::Hook amx_FindPublic_hook;
	sampgdk::Hook amx_Exec_hook;
	sampgdk::Hook amx_Register_hook;
	sampgdk::Hook amx_Callback_hook;

	std::vector<AMX_NATIVE_INFO> native_info;

	// The "funcidx" native uses amx_FindPublic() to get public function index
	// but our FindPublic always succeeds regardless of public existence, so
	// here's a fixed version.
	// Thanks to Incognito for finding this bug!
	cell AMX_NATIVE_CALL fixed_funcidx(AMX *amx, cell *params) {
		char *funcname;
		amx_StrParam(amx, params[1], funcname);

		int index;
		int error = amx_FindPublic(amx, funcname, &index);
		if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK)) {
			return -1;
		}

		return index;
	}

	int AMXAPI amx_Register_(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
		sampgdk::Hook::ScopedRemove remove(&amx_Register_hook);

		for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
			sampgdk::Natives::SetNative(nativelist[i].name, nativelist[i].func);
			native_info.push_back(nativelist[i]);

			if (strcmp(nativelist[i].name, "funcidx") == 0) {
				new sampgdk::Hook((void*)nativelist[i].func, (void*)fixed_funcidx);
			}
		}

		return amx_Register(amx, nativelist, number);
	}

	// The SA-MP server always makes a call to amx_FindPublic() and depending on
	// its return value invokes amx_Exec() to call the public function.
	// In order to make it always execute publics regardless of their existence
	// we have to make amx_FindPublic() always return OK.
	int AMXAPI amx_FindPublic_(AMX *amx, const char *name, int *index) {
		sampgdk::Hook::ScopedRemove remove(&amx_FindPublic_hook);

		int error = ::amx_FindPublic(amx, name, index);
		if (amx == gamemode_amx) {
			if (error != AMX_ERR_NONE) {
				error = AMX_ERR_NONE;
				*index = AMX_EXEC_GDK;
			}
			current_public = name;
		}

		return error;
	}

	// Whenever the server runs amx_Exec() we trigger callback handlers in all registered
	// plugins, if they exist. See Callbacks::HandleCallback().
	int AMXAPI amx_Exec_(AMX *amx, cell *retval, int index) {
		sampgdk::Hook::ScopedRemove remove(&amx_Exec_hook);
		sampgdk::Hook::ScopedInstall install(&amx_Callback_hook);

		bool canDoExec = true;
		if (index == AMX_EXEC_MAIN) {
			gamemode_amx = amx;
			sampgdk::Callbacks::HandleCallback(gamemode_amx, "OnGameModeInit", retval);
		} else {
			if (amx == gamemode_amx && index != AMX_EXEC_CONT) {
				canDoExec = sampgdk::Callbacks::HandleCallback(gamemode_amx, current_public, retval);
			}
		}

		int error = AMX_ERR_NONE;
		if (canDoExec && index != AMX_EXEC_GDK) {
			error = ::amx_Exec(amx, retval, index);
		} else {
			amx->stk += amx->paramcount * sizeof(cell);
		}

		amx->paramcount = 0;
		return error;
	}

	int AMXAPI amx_Callback_(AMX *amx, cell index, cell *result, cell *params) {
		sampgdk::Hook::ScopedRemove remove(&amx_Callback_hook);
		sampgdk::Hook::ScopedInstall install(&amx_Exec_hook);

		// Prevent the default AMX callback from replacing SYSREQ.C
		// instructions with SYSREQ.D.
		amx->sysreq_d = 0;

		return ::amx_Callback(amx, index, result, params);
	}

} // namespace

sampgdk_logprintf_t sampgdk_logprintf;

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppPluginData) {
	static bool initialized = false;

	if (!initialized) {
		pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];
		ppPluginData = ppPluginData;

		sampgdk_logprintf = (sampgdk_logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];

		void **exports = static_cast<void**>(pAMXFunctions);
		::amx_Register_hook.Install(
			exports[PLUGIN_AMX_EXPORT_Register],
			(void*)amx_Register_);
		::amx_FindPublic_hook.Install(
			exports[PLUGIN_AMX_EXPORT_FindPublic],
			(void*)amx_FindPublic_);
		::amx_Exec_hook.Install(
			exports[PLUGIN_AMX_EXPORT_Exec],
			(void*)amx_Exec_);
		::amx_Callback_hook.Install(
			exports[PLUGIN_AMX_EXPORT_Callback],
			(void*)amx_Callback_);

		sampgdk::Callbacks::Initialize();

		initialized = true;
	}
}

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data() {
	return ppPluginData;
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize() {
	amx_Register_hook.Remove();
	amx_FindPublic_hook.Remove();
	amx_Exec_hook.Remove();
	amx_Callback_hook.Remove();
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_register_plugin(void *plugin) {
	sampgdk::Callbacks::RegisterPlugin(plugin);
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin) {
	sampgdk::Callbacks::UnregisterPlugin(plugin);
}

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives() {
	return &::native_info[0];
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers() {
	sampgdk::Timer::ProcessTimers();
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin) {
	sampgdk::Timer::ProcessTimers(plugin);
}
