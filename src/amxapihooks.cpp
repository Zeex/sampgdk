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
	int error = ::amx_Register(amx, nativelist, number);

	for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
		sampgdk::Wrapper::GetInstance().SetNative(nativelist[i].name, nativelist[i].func);
	}

	// Fix for funcidx()
	HookNative(amx, "funcidx", funcidx);

	return error;
}

int AMXAPI AmxApiHooks::amx_FindPublic(AMX *amx, const char *name, int *index) {
	int error = ::amx_FindPublic(amx, name, index);	

	if (amx == GetGameMode()) {
		if (error != AMX_ERR_NONE) {
			*index = AMX_EXEC_GDK;
			error = AMX_ERR_NONE;
		}
		//printf("amx_FindPublic(%s) returns %d\n", name, error);
		AmxApiHooks::GetInstance().currentPublic_ = name;
	}

	return error;
}

int AMXAPI AmxApiHooks::amx_Exec(AMX *amx, cell *retval, int index) {
	if (amx == GetGameMode()) {
		//printf("BEGIN amx_Exec(%s[%d]) [paramcount = %d]\n", 
		//	AmxApiHooks::GetInstance().currentPublic_.c_str(), index, amx->paramcount);
	}

	bool canDoExec = true;	
	if (index == AMX_EXEC_MAIN) {
		//printf("main()\n");
		SetGameMode(amx);
		sampgdk::Wrapper::GetInstance().ExecutePublicHook(amx, retval, "OnGameModeInit");
	} else {
		if (amx == GetGameMode() && index != AMX_EXEC_CONT) {
			canDoExec = sampgdk::Wrapper::GetInstance().ExecutePublicHook(amx, 
					retval, AmxApiHooks::GetInstance().currentPublic_.c_str());
		}
		if (index == AMX_EXEC_GDK) {
			canDoExec = false;
			//printf("stk: %d --> ", amx->stk);
			amx->stk += amx->paramcount * sizeof(cell);
			amx->paramcount = 0;
			//printf("%d (stp = %d)\n", amx->stk, amx->stp);
		}
	}

	int error = AMX_ERR_NONE;
	if (canDoExec) {
		error = ::amx_Exec(amx, retval, index);
		//if (error != AMX_ERR_NONE) printf("AMX ERROR: %d\n", error);
	} 

	//if (amx == GetGameMode()) printf("END   amx_Exec(%d) [paramcount = %d]\n", index, amx->paramcount);

	return error;
}

AmxApiHooks::AmxApiHooks() {}

void AmxApiHooks::Initialize(void **amxExportsTable) {
	SetJump(amxExportsTable[PLUGIN_AMX_EXPORT_Register], (void*)AmxApiHooks::amx_Register);
	SetJump(amxExportsTable[PLUGIN_AMX_EXPORT_FindPublic], (void*)AmxApiHooks::amx_FindPublic);
	SetJump(amxExportsTable[PLUGIN_AMX_EXPORT_Exec], (void*)AmxApiHooks::amx_Exec);
}

AmxApiHooks &AmxApiHooks::GetInstance() {
	static AmxApiHooks inst;
	return inst;
}

} // namespace sampgdk

