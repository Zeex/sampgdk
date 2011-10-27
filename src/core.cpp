// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

#ifdef _WIN32
	#include <windows.h>
#else
	#define _GNU_SOURCE
	#include <dlfcn.h>
#endif

#include <sampgdk/core.h>
#include <sampgdk/export.h>

#include "callbacks.h"
#include "funcidx.h"
#include "gamemode.h"
#include "hooknative.h"
#include "jump.h"
#include "natives.h"

namespace hooks {

	static std::string currentPublic;

	int amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number) {
		int error = ::amx_Register(amx, nativelist, number);

		for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
			NativeManager::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
		}

		// Fix funcidx
		HookNative(amx, "funcidx", funcidx);

		return error;
	}

	int AMXAPI amx_FindPublic(AMX *amx, const char *name, int *index) {
		int error = ::amx_FindPublic(amx, name, index);	

		if (amx == GetGameMode()) {
			if (error != AMX_ERR_NONE) {
				*index = AMX_EXEC_GDK;
				error = AMX_ERR_NONE;
			}
			//printf("amx_FindPublic(%s) returns %d\n", name, error);
			currentPublic = name;
		}

		return error;
	}

	int AMXAPI amx_Exec(AMX *amx, cell *retval, int index) {
		if (amx == GetGameMode()) {
			//printf("BEGIN amx_Exec(%s[%d]) [paramcount = %d]\n", 
			//	currentPublic.c_str(), index, amx->paramcount);
		}

		bool canDoExec = true;	
		if (index == AMX_EXEC_MAIN) {
			//printf("main()\n");
			SetGameMode(amx);
			CallbackManager::GetInstance()->HandleCallback("OnGameModeInit");
		} else {
			if (amx == GetGameMode() && index != AMX_EXEC_CONT) {
				canDoExec = CallbackManager::GetInstance()->HandleCallback(currentPublic.c_str());
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

	int amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int wchar) {
		int error = ::amx_PushString(amx, amx_addr, phys_addr, string, pack, wchar);
		if (amx == GetGameMode()) {
			CallbackManager::GetInstance()->PushArg(*phys_addr);
		}
		return error;
	}

	int amx_Push(AMX *amx, cell value) {
		int error = ::amx_Push(amx, value);
		if (amx == GetGameMode()) {
			CallbackManager::GetInstance()->PushArg(value);
		}
		return error;
	}

} // namespace hooks

SAMPGDK_EXPORT void SAMPGDK_CALL SampGdkInit(void **pluginData) {
	static bool initialized = false;

	if (!initialized) {
		void **amxApiExports = (void**)pluginData[PLUGIN_DATA_AMX_EXPORTS];

		SetJump(amxApiExports[PLUGIN_AMX_EXPORT_Register], (void*)hooks::amx_Register);
		SetJump(amxApiExports[PLUGIN_AMX_EXPORT_FindPublic], (void*)hooks::amx_FindPublic);
		SetJump(amxApiExports[PLUGIN_AMX_EXPORT_Exec], (void*)hooks::amx_Exec);
		SetJump(amxApiExports[PLUGIN_AMX_EXPORT_Push], (void*)hooks::amx_Push);
		SetJump(amxApiExports[PLUGIN_AMX_EXPORT_PushString], (void*)hooks::amx_PushString);

		initialized = true;
	}
}

SAMPGDK_EXPORT void SAMPGDK_CALL SampGdkRegisterPlugin(void *plugin) {
	CallbackManager::GetInstance()->RegisterCallbackHandler(plugin);	
}

SAMPGDK_EXPORT void *SAMPGDK_CALL SampGdkGetPluginHandle(void *symbol) {
#ifdef _WIN32
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(symbol, &mbi, sizeof(mbi));
	return (void*)mbi.AllocationBase;
#else
	Dl_info info;
	dladdr(symbol, &info);
	return (void*)info.dli_fbase;
#endif
}

SAMPGDK_EXPORT void *SAMPGDK_CALL SampGdkFindSymbol(void *plugin, const char *name)  {
#ifdef _WIN32
	return (void*)GetProcAddress((HMODULE)plugin, name);
#else
	return dlsym(plugin, name);
#endif
}
