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

#include <sampgdk/amxplugin.h>

#include "amxapihooks.h"
#include "wrapperimpl.h"

extern void *pAMXFunctions;

namespace sampgdk {

WrapperImpl::WrapperImpl() {}

void WrapperImpl::Initialize(void **ppPluginData) {
	void *pAMXFunctions = ppPluginData[PLUGIN_DATA_AMX_EXPORTS];
	// Hook amx_Register, amx_FindPublic and amx_Exec.
	AmxApiHooks::GetInstance().Initialize(static_cast<void**>(pAMXFunctions)); 
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

