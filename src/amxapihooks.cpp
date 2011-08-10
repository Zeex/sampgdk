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
#include "natives.h"

static std::string lastPublicName;

namespace sampgdk {

int AmxApiHooks::Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number) {
    AmxApiHooks::GetInstance()->amxRegisterHook.Remove();

    int error = amx_Register(amx, nativelist, number);

    for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        sampgdk::NativeManager::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
    }

    // Fix funcidx
    HookNative(amx, "funcidx", funcidx);

    AmxApiHooks::GetInstance()->amxRegisterHook.Reinstall();

    return error;
}

int AmxApiHooks::FindPublic(AMX *amx, const char *name, int *index) {
    AmxApiHooks::GetInstance()->amxFindPublicHook.Remove();

    int error = amx_FindPublic(amx, name, index);

    if (amx == GetGameMode() && GetGameMode() != 0) {
        if (error != AMX_ERR_NONE) {
            // Make it think that any public it wants does exist.
            *index = AMX_EXEC_GDK;
            error = AMX_ERR_NONE;
        }
        ::lastPublicName = name;
    }

    AmxApiHooks::GetInstance()->amxFindPublicHook.Reinstall();

    return error;
}

int AmxApiHooks::Exec(AMX *amx, cell *retval, int index) {
    AmxApiHooks::GetInstance()->amxExecHook.Remove();

    int error = AMX_ERR_NONE;
    if (index == AMX_EXEC_MAIN) {
        // main() is being called -> this is the game mode.
        SetGameMode(amx);
        // OnGameModeInit is called before main so we must exec it manually somehow.
        sampgdk::Wrapper::GetInstance()->ExecutePublicHook(amx, retval, "OnGameModeInit");
        // Allow calls to main()
        error = amx_Exec(amx, retval, index);
    } else {
        // Check whether we deal with a game mode
        if (amx == GetGameMode() && GetGameMode() != 0) {
            bool canDoExec = true;
            if (index != AMX_EXEC_MAIN && index != AMX_EXEC_CONT) {
                // Handle this public call.
                canDoExec = sampgdk::Wrapper::GetInstance()->ExecutePublicHook(
                    GetGameMode(), retval, ::lastPublicName.c_str());
            }
            // The handler could return a value indicating that the call should
            // not be propagated to the gamemode or other handlers, if any (there can
            // be multiple handlers since recently).
            if (canDoExec) {
                error = amx_Exec(amx, retval, index);
                if (error == AMX_ERR_INDEX && index == AMX_EXEC_GDK) {
                    // Return no error if it's our fault that it executes a non-existing public.
                    error = AMX_ERR_NONE;
                }
            }
        } else {
            // Not a game mode - just call the original amx_Exec.
            error = amx_Exec(amx, retval, index);
        }
    }

    AmxApiHooks::GetInstance()->amxExecHook.Reinstall();

    return error;
}


AmxApiHooks::AmxApiHooks() {}

void AmxApiHooks::Initialize(void **amxExportsTable) {
    amxRegisterHook.Install(amxExportsTable[PLUGIN_AMX_EXPORT_Register], (void*)Register);
    amxFindPublicHook.Install(amxExportsTable[PLUGIN_AMX_EXPORT_FindPublic], (void*)FindPublic);
    amxExecHook.Install(amxExportsTable[PLUGIN_AMX_EXPORT_Exec], (void*)Exec);
}

} // namespace sampgdk
