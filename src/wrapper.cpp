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
#include <sampgdk/plugin.h>
#include <sampgdk/wrapper.h>

#include "amxapihooks.h"
#include "callbacks.h"

extern void *pAMXFunctions;

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
    ::pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];

    // Hook amx_Register, amx_FindPublic and amx_Exec.
    AmxApiHooks::GetInstance()->Initialize(static_cast<void**>(pAMXFunctions)); 

    // Set handlers for all known SA:MP callbacks.
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

