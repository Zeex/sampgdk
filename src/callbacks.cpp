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

#include <string>
#include <map>

#include <sampgdk/config.h>
#include <sampgdk/amx.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include "callbacks.h"

namespace {
	#include "generated/callbacks.cpp"
}

namespace sampgdk {

Callbacks::Callbacks() {
	RegisterCallbacks();
}

Callbacks &Callbacks::GetInstance() {
	static Callbacks callbacks;
	return callbacks;
}

void Callbacks::RegisterPlugin(void *plugin) {
	pluginMap_.insert(std::make_pair(plugin, PluginSymbolMap()));
}

void Callbacks::UnregisterPlugin(void *plugin) {
	pluginMap_.erase(plugin);
}

void Callbacks::AddHandler(const std::string &name, CallbackHandler handler) {
	callbackHandlerMap_[name] = handler;
}

static inline unsigned char *GetAmxDataPtr(AMX *amx) {
	unsigned char *dataPtr = amx->data;
	if (dataPtr == 0) {
		AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
		dataPtr = amx->base + hdr->dat;
	}
	return dataPtr;
}

cell Callbacks::GetStackCell(AMX *amx, int index) const {
	cell *stackPtr = reinterpret_cast<cell*>(GetAmxDataPtr(amx) + amx->stk);
	return stackPtr[index];
}

bool Callbacks::GetStackBool(AMX *amx, int index) const {
	return GetStackCell(amx, index) != 0;
}

float Callbacks::GetStackFloat(AMX *amx, int index) const {
	cell value = GetStackCell(amx, index);
	return amx_ctof(value);
}

std::string Callbacks::GetStackString(AMX *amx, int index) const {
	cell address = GetStackCell(amx, index);
	cell *stringPtr = reinterpret_cast<cell*>(GetAmxDataPtr(amx) + address);

	std::string string;
	for (cell c; (c = *stringPtr) != '\0'; stringPtr++) {
		string.push_back(static_cast<char>(c & 0xFF));
	}

	return string;
}

bool Callbacks::HandleCallback(AMX *amx, const std::string &name, cell *retval) {
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

} // namespace sampgdk
