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

#include <cstring> // for memcpy()
#include <string>

#include <sampgdk/logprintf.h>
#include <sampgdk/plugin/plugin.h>
#include <sampgdk/wrapper/callbacks.h>
#include <sampgdk/wrapper/wrapper.h>

#include "jump.h"

#define AMX_EXEC_CHEAT (-10)

extern void *pAMXFunctions;

static uint32_t amx_Register_addr;
static unsigned char amx_Register_code[5];

static int my_amx_Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number) {
    // Restore the original code so we can call the function
    memcpy(reinterpret_cast<void*>(::amx_Register_addr), ::amx_Register_code, 5);
    int error = amx_Register(amx, nativelist, number);

    // Store natives in our global container
    for (int i = 0; nativelist[i].name != 0 && (i < number || number == -1); ++i) {
        sampgdk::Wrapper::GetInstance()->SetNative(nativelist[i].name, nativelist[i].func);
    }

    // Set the jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), (void*)::my_amx_Register, ::amx_Register_code);

    return error;
}

static uint32_t amx_FindPublic_addr;
static unsigned char amx_FindPublic_code[5];

static AMX *pGamemode = 0;
static std::string lastPublicName;

static int my_amx_FindPublic(AMX *amx, const char *name, int *index) {
    // Restore the original code so we can call the function
    memcpy(reinterpret_cast<void*>(::amx_FindPublic_addr), ::amx_FindPublic_code, 5);
    int error = amx_FindPublic(amx, name, index);

    if (amx == ::pGamemode && ::pGamemode != 0) {
        if (error != AMX_ERR_NONE) {
            // The requested public doesn't exist but we say it does
            // to let the server subsequently execute it.
            *index = AMX_EXEC_CHEAT;
            error = AMX_ERR_NONE;
        }
        ::lastPublicName = name;
    }

    // Set the jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_FindPublic_addr), (void*)::my_amx_FindPublic, ::amx_FindPublic_code);

    return error;
}

static uint32_t amx_Exec_addr;
static unsigned char amx_Exec_code[5];

static int my_amx_Exec(AMX *amx, cell *retval, int index) {
    bool canDoExec = true;

    if (index == AMX_EXEC_MAIN) {
        // main() is being called => this is the gamemode
        ::pGamemode = amx;
        // Manually call OnGameModeInit from here as it's usually called 
        // before main() and is impossible to catch using the current method
        canDoExec = sampgdk::Wrapper::GetInstance()->ExecutePublicHook(::pGamemode, retval, "OnGameModeInit");
    }

    if (amx == ::pGamemode && ::pGamemode != 0) {
        if (index != AMX_EXEC_MAIN && index != AMX_EXEC_CONT) {
            canDoExec = sampgdk::Wrapper::GetInstance()->ExecutePublicHook(::pGamemode, retval, ::lastPublicName);
        }
    } 

    // Restore the original code so we can call the function
    memcpy(reinterpret_cast<void*>(::amx_Exec_addr), ::amx_Exec_code, 5);

    int error;
    if (canDoExec) {
        error = amx_Exec(amx, retval, index);
        if (index == AMX_EXEC_CHEAT && error == AMX_ERR_INDEX) {
            error == AMX_ERR_NONE;
        }
    }

    // Set the jump again to catch further calls
    SetJump(reinterpret_cast<void*>(::amx_Exec_addr), (void*)::my_amx_Exec, ::amx_Exec_code);

    return error;
}

namespace sampgdk {

PublicHook::PublicHook(PublicHook::Handler handler, cell breakingReturn)
    : handler_(handler), breakingReturn_(breakingReturn)
{
}

bool PublicHook::Execute(AMX *amx, cell *retval) const
{
    return ((*retval = handler_(amx)) != breakingReturn_);
}

Wrapper::Wrapper() {}

Wrapper *Wrapper::GetInstance() {
    static Wrapper w;
    return &w;
}

void Wrapper::Initialize(void **ppPluginData) {
    // Very important things
    ::pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];

    // Hook amx_Register
    ::amx_Register_addr = reinterpret_cast<uint32_t>((static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Register]);
    SetJump(reinterpret_cast<void*>(::amx_Register_addr), (void*)::my_amx_Register, ::amx_Register_code);

    // Hook amx_FindPublic
    ::amx_FindPublic_addr = reinterpret_cast<uint32_t>((static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_FindPublic]);
    SetJump(reinterpret_cast<void*>(::amx_FindPublic_addr), (void*)::my_amx_FindPublic, ::amx_FindPublic_code);

    // Hook amx_Exec
    ::amx_Exec_addr = reinterpret_cast<uint32_t>((static_cast<void**>(pAMXFunctions))[PLUGIN_AMX_EXPORT_Exec]);
    SetJump(reinterpret_cast<void*>(::amx_Exec_addr), (void*)::my_amx_Exec, ::amx_Exec_code);

    // Set handlers for all SA:MP callbacks
    sampgdk::InitializeCallbacks();
}

void Wrapper::SetNative(const std::string &name, AMX_NATIVE native) {
    if (!name.empty()) {
        natives_[name] = native;
    }
}
    
AMX_NATIVE Wrapper::GetNative(const std::string &name) const {
    std::map<std::string, AMX_NATIVE>::const_iterator it = natives_.find(name);
    if (it != natives_.end()) {
        return it->second;
    } 
    return 0;
}

void Wrapper::SetPublicHook(const std::string &name, PublicHook handler) {
    publicHooks_.insert(std::make_pair(name, handler));
}

bool Wrapper::ExecutePublicHook(AMX *amx, cell *retval, const std::string &name) const {
    std::map<std::string, PublicHook>::const_iterator it = publicHooks_.find(name);
    if (it != publicHooks_.end()) {
        return it->second.Execute(amx, retval);
    }
    return true;
}

} // namespace sampgdk

