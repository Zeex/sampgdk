// Copyright (C) 2011-2012, Zeex
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

#include <sampgdk/config.h>
#include <sampgdk/amx.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include <string>
#include <map>

#include "callbacks.h"
#include "util.h"

namespace {

#include "generated/callback-handlers-impl.cpp"

typedef std::map<std::string, sampgdk::callbacks::CallbackHandler> CallbackHandlerMap;
CallbackHandlerMap callbackHandlerMap_;

typedef std::map<std::string, void*> PluginSymbolMap;
typedef std::map<void*, PluginSymbolMap> PluginMap;
PluginMap pluginMap_;

} // namespace

namespace sampgdk {
namespace callbacks {

void RegisterPlugin(void *plugin) {
	static bool ok = false;

	if (!ok) {
		RegisterCallbacks();
		ok = true;
	}

	pluginMap_.insert(std::make_pair(plugin, PluginSymbolMap()));
}

void UnregisterPlugin(void *plugin) {
	pluginMap_.erase(plugin);
}

void AddCallbackHandler(const std::string &name, CallbackHandler handler) {
	callbackHandlerMap_[name] = handler;
}

bool HandleCallback(AMX *amx, const std::string &name, cell *retval) {
	CallbackHandler callbackHandler = 0;

	CallbackHandlerMap::const_iterator cbHandlerIter = callbackHandlerMap_.find(name);
	if (cbHandlerIter != callbackHandlerMap_.end()) {
		callbackHandler = cbHandlerIter->second;
	}

	if (callbackHandler != 0) {
		for (PluginMap::const_iterator pluginIter = pluginMap_.begin(); 
				pluginIter != pluginMap_.end(); ++pluginIter) 
		{
			void *plugin = pluginIter->first;

			PluginSymbolMap symbols = pluginIter->second;
			PluginSymbolMap::const_iterator symbolIter = symbols.find(name);

			void *callback = 0;

			if (symbolIter == symbols.end()) {
				if ((callback = sampgdk_get_plugin_symbol(plugin, name.c_str())) != 0) {
					symbols.insert(std::make_pair(name, callback));
				}
			} else {
				callback = symbolIter->second;
			}

			if (callback != 0) {
				bool ok = callbackHandler(amx, callback, retval);
				if (!ok) {
					return false;
				}
			}
		}
	}

	return true;
}

} // namespace callbacks
} // namespace sampgdk
