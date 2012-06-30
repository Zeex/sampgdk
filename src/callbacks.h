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

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include <map>
#include <string>

namespace sampgdk {

typedef bool (*CallbackHandler)(AMX *amx, void *callback, cell *retval);

class Callbacks {
public:
	// Should be called before any callback is executed.
	static void Initialize();

	static void RegisterPlugin(void *plugin);
	static void UnregisterPlugin(void *plugin);

	static void AddHandler(const std::string &name, CallbackHandler handler);

	static cell GetStackCell(AMX *amx, int index);
	static bool GetStackBool(AMX *amx, int index);
	static float GetStackFloat(AMX *amx, int index);
	static std::string GetStackString(AMX *amx, int index);

	static bool HandleCallback(AMX *amx, const std::string &name, cell *retval);

private:
	Callbacks();

private:
	typedef std::map<std::string, CallbackHandler> CallbackHandlerMap;
	static CallbackHandlerMap callbackHandlerMap_;

	typedef std::map<std::string, void*> PluginSymbolMap;
	typedef std::map<void*, PluginSymbolMap> PluginMap;
	static PluginMap pluginMap_;
};

} // namespace sampgdk

#endif // !SAMPGDK_CALLBACKS_H
