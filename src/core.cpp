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
#include "plugin.h"

extern void *pAMXFunctions;

static std::string lastPublicName;

namespace hooks {

	Jump amx_Register_hook;	

	int amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number) {
		amx_Register_hook.Remove();

		int error = ::amx_Register(amx, nativelist, number);

		for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
			NativeManager::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
		}

		// Fix funcidx
		HookNative(amx, "funcidx", funcidx);

		amx_Register_hook.Reinstall();

		return error;
	}

	Jump amx_FindPublic_hook;

	int amx_FindPublic(AMX *amx, const char *name, int *index) {
		amx_FindPublic_hook.Remove();

		int error = ::amx_FindPublic(amx, name, index);

		if (amx == GetGameMode() && GetGameMode() != 0) {
			if (error != AMX_ERR_NONE) {
				// Make it think that any public it wants does exist.
				*index = AMX_EXEC_GDK;
				error = AMX_ERR_NONE;
			}
			::lastPublicName = name;
		}

		amx_FindPublic_hook.Reinstall();

		return error;
	}

	Jump amx_Exec_hook;

	int amx_Exec(AMX *amx, cell *retval, int index) {
		amx_Exec_hook.Remove();

		int error = AMX_ERR_NONE;
		if (index == AMX_EXEC_MAIN) {
			// main() is being called -> this is the game mode.
			SetGameMode(amx);
			// OnGameModeInit is called before main so we must exec it manually somehow.
			CallbackManager::GetInstance()->HandleCallback("OnGameModeInit");
			error = ::amx_Exec(amx, retval, index);
		} else {
			// Check whether we deal with a game mode
			if (amx == GetGameMode() && GetGameMode() != 0) {
				bool canDoExec = true;
				if (index != AMX_EXEC_MAIN && index != AMX_EXEC_CONT) {
					canDoExec = CallbackManager::GetInstance()->HandleCallback(::lastPublicName.c_str());
					*retval = cell(canDoExec);
				}
				// The handler could return a value indicating that the call should
				// not be propagated to the gamemode or other handlers, if any (there can
				// be multiple handlers since recently).
				if (canDoExec) {
					error = ::amx_Exec(amx, retval, index);
					if (error == AMX_ERR_INDEX && index == AMX_EXEC_GDK) {
						// Return no error if it's our fault that it executes a non-existing public.
						error = AMX_ERR_NONE;
					}
				}
			} else {
				// Not a game mode - just call the original amx_Exec.
				error = ::amx_Exec(amx, retval, index);
			}
		}

		amx_Exec_hook.Reinstall();

		return error;
	}

	Jump amx_PushString_hook;

	int amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int wchar) {
		amx_PushString_hook.Remove();

		int error = ::amx_PushString(amx, amx_addr, phys_addr, string, pack, wchar);
		if (amx == GetGameMode()) {
			CallbackManager::GetInstance()->PushArg(*phys_addr);
		}

		amx_PushString_hook.Reinstall();
		return error;
	}

	Jump amx_Push_hook;

	int amx_Push(AMX *amx, cell value) {
		amx_Push_hook.Remove();

		int error = ::amx_Push(amx, value);
		if (amx == GetGameMode() && amx_PushString_hook.IsInstalled()) {
			CallbackManager::GetInstance()->PushArg(value);
		}

		amx_Push_hook.Reinstall();
		return error;
	}

} // namespace hooks

SAMPGDK_EXPORT void SAMPGDK_CALL SampGdkInit(void **data) {
	static bool initialized = false;

	if (!initialized) {
		pAMXFunctions = data[PLUGIN_DATA_AMX_EXPORTS];

		hooks::amx_Register_hook.Install(
			((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Register], 
			(void*)hooks::amx_Register
		);

		hooks::amx_FindPublic_hook.Install(
			((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPublic], 
			(void*)hooks::amx_FindPublic
		);

		hooks::amx_Exec_hook.Install(
			((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Exec], 
			(void*)hooks::amx_Exec
		);

		hooks::amx_Push_hook.Install(
			((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Push], 
			(void*)hooks::amx_Push
		);

		hooks::amx_PushString_hook.Install(
			((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_PushString], 
			(void*)hooks::amx_PushString
		);

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