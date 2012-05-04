// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SAMPGDK_CALLBACKS_H
#define SAMPGDK_CALLBACKS_H
#pragma once

#include <sampgdk/amx.h>

#include <map>
#include <string>

namespace sampgdk {

typedef bool (*CallbackHandler)(AMX *amx, void *callback, cell *retval);

class Callbacks {
public:
	Callbacks();

	static Callbacks &GetInstance();

	void RegisterPlugin(void *plugin);
	void UnregisterPlugin(void *plugin);

	void AddHandler(const std::string &name, CallbackHandler handler);

	cell        GetStackCell(AMX *amx, int index) const;
	bool        GetStackBool(AMX *amx, int index) const;
	float       GetStackFloat(AMX *amx, int index) const;
	std::string GetStackString(AMX *amx, int index) const;

	bool HandleCallback(AMX *amx, const std::string &name, cell *retval);

private:
	typedef std::map<std::string, CallbackHandler> CallbackHandlerMap;
	CallbackHandlerMap callbackHandlerMap_;

	typedef std::map<std::string, void*> PluginSymbolMap;
	typedef std::map<void*, PluginSymbolMap> PluginMap;
	PluginMap pluginMap_;
};

} // namespace sampgdk

#endif // !SAMPGDK_CALLBACKS_H
