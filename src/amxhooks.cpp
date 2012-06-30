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

#include <sampgdk/config.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include "amxhooks.h"
#include "callbacks.h"
#include "hook.h"
#include "natives.h"

#include <cstring>

extern void *pAMXFunctions;

namespace sampgdk {

AMX *AmxHooks::gamemode_ = 0;

std::string AmxHooks::currentPublic_;

Hook AmxHooks::amx_FindPublicHook_;
Hook AmxHooks::amx_ExecHook_;
Hook AmxHooks::amx_RegisterHook_;
Hook AmxHooks::amx_CallbackHook_;

std::vector<AMX_NATIVE_INFO> AmxHooks::native_info_;

// The "funcidx" native uses amx_FindPublic() to get public function index
// but our FindPublic always succeeds regardless of public existence, so
// here's a fixed version.
// Thanks to Incognito for finding this bug!
static cell AMX_NATIVE_CALL fixed_funcidx(AMX *amx, cell *params) {
	char *funcname;
	amx_StrParam(amx, params[1], funcname);
	int index;
	int error = amx_FindPublic(amx, funcname, &index);
	if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK)) {
		return -1;
	}
	return index;
}

void AmxHooks::Initialize(void **ppPluginData) {
	pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

	void **amxExports = static_cast<void**>(pAMXFunctions);
	amx_RegisterHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_Register],
		(void*)amx_Register);
	amx_FindPublicHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_FindPublic],
		(void*)amx_FindPublic);
	amx_ExecHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_Exec],
		(void*)amx_Exec);
	amx_CallbackHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_Callback],
		(void*)amx_Callback);

	Callbacks::Initialize();
}

void AmxHooks::Finalize() {
	amx_RegisterHook_.Remove();
	amx_FindPublicHook_.Remove();
	amx_ExecHook_.Remove();
	amx_CallbackHook_.Remove();
}

int AMXAPI AmxHooks::amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	Hook::ScopedRemove r(&amx_RegisterHook_);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		Natives::SetNative(nativelist[i].name, nativelist[i].func);
		// Fix for funcidx() issue
		if (strcmp(nativelist[i].name, "funcidx") == 0) {
			new Hook((void*)nativelist[i].func, (void*)fixed_funcidx);
		}
		native_info_.push_back(nativelist[i]);
	}
	return ::amx_Register(amx, nativelist, number);
}

// The SA-MP server always makes a call to amx_FindPublic() and depending on
// its return value invokes amx_Exec() (i.e. calls a public function).
// To make the server always execute publics regardless of their existence
// we have to make amx_FindPublic() always succeed i.e. return AMX_ERR_NONE.
int AMXAPI AmxHooks::amx_FindPublic(AMX *amx, const char *name, int *index) {
	Hook::ScopedRemove r(&amx_FindPublicHook_);

	int error = ::amx_FindPublic(amx, name, index);
	if (amx == gamemode_) {
		if (error != AMX_ERR_NONE) {
			*index = AMX_EXEC_GDK;
			error = AMX_ERR_NONE;
		}
		currentPublic_ = name;
	}
	return error;
}

// Whenever the server runs amx_Exec() we trigger callback handlers in all registered
// plugins, if they exist. See Callbacks::HandleCallback().
int AMXAPI AmxHooks::amx_Exec(AMX *amx, cell *retval, int index) {
	Hook::ScopedRemove r(&amx_ExecHook_);
	Hook::ScopedInstall i(&amx_CallbackHook_);

	bool canDoExec = true;
	if (index == AMX_EXEC_MAIN) {
		// main() is called only for gamemodes - so this is it.
		gamemode_ = amx;
		Callbacks::HandleCallback(gamemode_, "OnGameModeInit", retval);
	} else {
		if (amx == gamemode_ && index != AMX_EXEC_CONT) {
			canDoExec = Callbacks::HandleCallback(gamemode_, currentPublic_, retval);
		}
	}

	int error = AMX_ERR_NONE;
	if (canDoExec && index != AMX_EXEC_GDK) {
		error = ::amx_Exec(amx, retval, index);
	} else {
		// Pop parameters from stack.
		amx->stk += amx->paramcount * sizeof(cell);
	}

	// Reset parameter count.
	amx->paramcount = 0;

	return error;
}

int AMXAPI AmxHooks::amx_Callback(AMX *amx, cell index, cell *result, cell *params) {
	Hook::ScopedRemove r(&amx_CallbackHook_);
	Hook::ScopedInstall i(&amx_ExecHook_);

	// Forbid SYSREQ.D.
	amx->sysreq_d = 0;

	return ::amx_Callback(amx, index, result, params);
}

} // namespace sampgdk
