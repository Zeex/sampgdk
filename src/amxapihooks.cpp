// Copyright (c) 2011 Zeex
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

#include <sampgdk/amxplugin.h>
#include <sampgdk/wrapper.h>

#include "amxapihooks.h"
#include "funcidx.h"
#include "gamemode.h"
#include "hooknative.h"

namespace sampgdk {

int AMXAPI AmxApiHooks::amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number) {
	AmxApiHooks::GetInstance()->registerHook_.Remove();

	int error = ::amx_Register(amx, nativelist, number);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		sampgdk::Wrapper::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
	}

	// Fix funcidx
	HookNative(amx, "funcidx", funcidx);

	AmxApiHooks::GetInstance()->registerHook_.Reinstall();

	return error;
}

int AMXAPI AmxApiHooks::amx_FindPublic(AMX *amx, const char *name, int *index) {
	AmxApiHooks::GetInstance()->findPublicHook_.Remove();

	int error = ::amx_FindPublic(amx, name, index);

	if (amx == GetGameMode() && GetGameMode() != 0) {
		if (error != AMX_ERR_NONE) {
			// Make it think that any public it wants does exist.
			*index = AMX_EXEC_GDK;
			error = AMX_ERR_NONE;
		}
		AmxApiHooks::GetInstance()->currentPublic_ = name;
	}

	AmxApiHooks::GetInstance()->findPublicHook_.Reinstall();

	return error;
}

int AMXAPI AmxApiHooks::amx_Exec(AMX *amx, cell *retval, int index) {
	AmxApiHooks::GetInstance()->execHook_.Remove();

	int error = AMX_ERR_NONE;
	if (index == AMX_EXEC_MAIN) {
		// main() is being called -> this is the game mode.
		SetGameMode(amx);
		// OnGameModeInit is called before main so we must exec it manually somehow...
		sampgdk::Wrapper::GetInstance()->ExecutePublicHook(amx, retval, "OnGameModeInit");
		error = ::amx_Exec(amx, retval, index);
	} else {
		// Check whether we deal with a game mode
		if (amx == GetGameMode() && GetGameMode() != 0) {
			bool canDoExec = true;
			if (index != AMX_EXEC_MAIN && index != AMX_EXEC_CONT) {
				canDoExec = sampgdk::Wrapper::GetInstance()->ExecutePublicHook(
					GetGameMode(), retval, AmxApiHooks::GetInstance()->currentPublic_.c_str());
			}
			// The handler could return a value indicating that this call shouldn't
			// propagate to the gamemode or the rest of handlers (if any)
			if (canDoExec) {
				if (index != AMX_EXEC_GDK) {
					error = ::amx_Exec(amx, retval, index);
				} else {
					error = AMX_ERR_NONE;
				}
			}
		} else {
			// Not a game mode - just call the original amx_Exec.
			error = ::amx_Exec(amx, retval, index);
		}
	}

	AmxApiHooks::GetInstance()->execHook_.Reinstall();

	return error;
}

AmxApiHooks::AmxApiHooks() {}

void AmxApiHooks::Initialize(void **amxExportsTable) {
	registerHook_.Install(amxExportsTable[PLUGIN_AMX_EXPORT_Register], 
		(void*)AmxApiHooks::amx_Register);
	findPublicHook_.Install(amxExportsTable[PLUGIN_AMX_EXPORT_FindPublic], 
		(void*)AmxApiHooks::amx_FindPublic);
	execHook_.Install(amxExportsTable[PLUGIN_AMX_EXPORT_Exec], 
		(void*)AmxApiHooks::amx_Exec);
}

AmxApiHooks *AmxApiHooks::GetInstance() {
	static AmxApiHooks inst;
	return &inst;
}

} // namespace sampgdk

