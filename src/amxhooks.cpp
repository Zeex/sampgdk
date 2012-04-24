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
#include "jump-x86.h"
#include "natives.h"

#include <cstring>

extern void *pAMXFunctions;

namespace sampgdk {

// Gamemode's AMX
AMX *AmxHooks::gamemode_ = 0;

// Curently Exec()'ing public
std::string AmxHooks::currentPublic_;

// AMX API hooks
JumpX86 AmxHooks::amx_FindPublicHook_;
JumpX86 AmxHooks::amx_ExecHook_;
JumpX86 AmxHooks::amx_RegisterHook_;
JumpX86 AmxHooks::amx_CallbackHook_;
JumpX86 AmxHooks::amx_PushHook_;
JumpX86 AmxHooks::amx_PushStringHook_;

// Maps callback name to its 'bad' return value
std::map<std::string, int> AmxHooks::cbBadRetVals_;

// Global list of registered native functions (server + all plugins)
std::vector<AMX_NATIVE_INFO> AmxHooks::native_info_;

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

#define NICE_CALLBACK(name) \
	do { cbBadRetVals_[#name] = 0; } while(false)
#define UGLY_CALLBACK(name) \
	do { cbBadRetVals_[#name] = 1; } while(false)

void AmxHooks::RegisterCallbacks() {
	UGLY_CALLBACK(OnDialogResponse);
	UGLY_CALLBACK(OnPlayerCommandText);
	NICE_CALLBACK(OnPlayerConnect);
	NICE_CALLBACK(OnPlayerDisonnect);
	NICE_CALLBACK(OnPlayerEnterCheckpoint);
	NICE_CALLBACK(OnPlayerEnterRaceCheckpoint);
	NICE_CALLBACK(OnPlayerKeyStateChange);
	NICE_CALLBACK(OnPlayerSpawn);
	NICE_CALLBACK(OnPlayerRequestClass);
	NICE_CALLBACK(OnPlayerRequestSpawn);
	NICE_CALLBACK(OnPlayerText);
	NICE_CALLBACK(OnPlayerUpdate);
	UGLY_CALLBACK(OnRconCommand);
	NICE_CALLBACK(OnVehicleMod);
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
	amx_PushHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_Push],
		(void*)amx_Push);
	amx_PushStringHook_.Install(
		amxExports[PLUGIN_AMX_EXPORT_PushString],
		(void*)amx_PushString);

	RegisterCallbacks();
}

void AmxHooks::Finalize() {
	amx_RegisterHook_.Remove();
	amx_FindPublicHook_.Remove();
	amx_ExecHook_.Remove();
	amx_CallbackHook_.Remove();
	amx_PushHook_.Remove();
	amx_PushStringHook_.Remove();
}

int AMXAPI AmxHooks::amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	JumpX86::ScopedRemove r(&amx_RegisterHook_);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		Natives::GetInstance().SetNative(nativelist[i].name, nativelist[i].func);
		// Fix for funcidx() issue
		if (strcmp(nativelist[i].name, "funcidx") == 0) {
			new JumpX86((void*)nativelist[i].func, (void*)fixed_funcidx);
		}
		native_info_.push_back(nativelist[i]);
	}
	return ::amx_Register(amx, nativelist, number);
}

int AMXAPI AmxHooks::amx_FindPublic(AMX *amx, const char *name, int *index) {
	JumpX86::ScopedRemove r(&amx_FindPublicHook_);

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

int AMXAPI AmxHooks::amx_Exec(AMX *amx, cell *retval, int index) {
	JumpX86::ScopedRemove r(&amx_ExecHook_);
	JumpX86::ScopedInstall i(&amx_CallbackHook_);

	bool canDoExec = true;
	if (index == AMX_EXEC_MAIN) {
		gamemode_ = amx;
		Callbacks::GetInstance().GetInstance().HandleCallback("OnGameModeInit", 0);
	} else {
		if (amx == gamemode_ && index != AMX_EXEC_CONT) {
			std::map<std::string, int>::const_iterator iterator = cbBadRetVals_.find(currentPublic_.c_str());
			CallbackRetVal badRetVal;
			if (iterator != cbBadRetVals_.end()) {
				badRetVal = iterator->second;
			}
			cell retval_ = Callbacks::GetInstance().GetInstance().HandleCallback(currentPublic_.c_str(), badRetVal);
			if (badRetVal.IsSet()) {
				*retval = retval_;
			}
			if (badRetVal.IsSet() && *retval == badRetVal) {
				canDoExec = false;
			}
		}
	}

	int error = AMX_ERR_NONE;
	if (canDoExec && index != AMX_EXEC_GDK) {
		error = ::amx_Exec(amx, retval, index);
	} else {
		// Pop parameters from stack
		amx->stk += amx->paramcount * sizeof(cell);
	}

	// Reset parameter count
	amx->paramcount = 0;

	return error;
}

int AMXAPI AmxHooks::amx_Callback(AMX *amx, cell index, cell *result, cell *params) {
	JumpX86::ScopedRemove r(&amx_CallbackHook_);
	JumpX86::ScopedInstall i(&amx_ExecHook_);

	// Forbid SYSREQ.D
	amx->sysreq_d = 0;

	return ::amx_Callback(amx, index, result, params);
}

int AMXAPI AmxHooks::amx_Push(AMX *amx, cell value) {
	JumpX86::ScopedRemove r1(&amx_PushHook_);

	if (amx == gamemode_) {
		Callbacks::GetInstance().GetInstance().PushArgFront(value);
	}
	return ::amx_Push(amx, value);
}

int AMXAPI AmxHooks::amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int wchar) {
	JumpX86::ScopedRemove r1(&amx_PushHook_);
	JumpX86::ScopedRemove r2(&amx_PushStringHook_);

	if (amx == gamemode_) {
		Callbacks::GetInstance().GetInstance().PushArgFront(string);
	}
	return ::amx_PushString(amx, amx_addr, phys_addr, string, pack, wchar);
}

} // namespace sampgdk
