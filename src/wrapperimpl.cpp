// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <sampgdk/amxplugin.h>

#include "amxapihooks.h"
#include "wrapperimpl.h"

extern void *pAMXFunctions;

namespace sampgdk {

WrapperImpl::WrapperImpl() {}

void WrapperImpl::Initialize(void **ppPluginData) {
    ::pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];

    // Hook amx_Register, amx_FindPublic and amx_Exec.
    AmxApiHooks::GetInstance()->Initialize(static_cast<void**>(pAMXFunctions)); 
}

void WrapperImpl::SetNative(const char *name, AMX_NATIVE native) {
    natives_[std::string(name)] = native;
}
    
AMX_NATIVE WrapperImpl::GetNative(const char *name) const {
    std::map<std::string, AMX_NATIVE>::const_iterator it = natives_.find(name);
    if (it != natives_.end()) {
        return it->second;
    } 
    return 0;
}

void WrapperImpl::SetPublicHook(const char *name, PublicHook handler) {
    publicHooks_.insert(std::make_pair(std::string(name), handler));
}

bool WrapperImpl::ExecutePublicHook(AMX *amx, cell *retval, const char *name) const {
    std::map<std::string, PublicHook>::const_iterator it = publicHooks_.find(name);
    if (it != publicHooks_.end()) {
        return it->second.Execute(amx, retval);
    }
    return true;
}

} // namespace sampgdk

