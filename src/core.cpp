// Copyright (C) 2011-2012, Zeex
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

#include <cstdlib>
#include <sampgdk/config.h>
#include <sampgdk/core.h>

#ifdef SAMPGDK_WINDOWS
	#include <windows.h>
#else
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE 1
	#endif
	#include <dlfcn.h>
#endif

#include "amxhooks.h"
#include "callbacks.h"
#include "natives.h"

static void *plugin_data;

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppPluginData) {
	static bool initialized = false;
	if (!initialized) {
		::plugin_data = ppPluginData;
		AmxHooks::Initialize(ppPluginData);
		initialized = true;
	}
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_data() {
	return plugin_data;
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize() {
	// nothing
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_register_plugin(void *plugin) {
	Callbacks::RegisterCallbackHandler(plugin);
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol) {
#ifdef SAMPGDK_WINDOWS
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(symbol, &mbi, sizeof(mbi));
	return (void*)mbi.AllocationBase;
#else
	Dl_info info;
	dladdr(symbol, &info);
	return dlopen(info.dli_fname, RTLD_NOW); /* should be already loaded by the server */
#endif
}

SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name)  {
#ifdef SAMPGDK_WINDOWS
	return (void*)GetProcAddress((HMODULE)plugin, name);
#else
	return dlsym(plugin, name);
#endif
}

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives() {
	return &(AmxHooks::GetNatives()[0]);
}
