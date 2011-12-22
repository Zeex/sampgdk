// Copyright (c) 2011 Zeex
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

#include <dyncall.h>
#include <dyncall_callvm.h>

#include <sampgdk/config.h>
#include <sampgdk/core.h>
#include <sampgdk/amx/amx.h>

#include "callbacks.h"

CallbackManager::CallbackManager()
	: cache_()
{
}

CallbackManager &CallbackManager::GetInstance() {
	static CallbackManager inst;
	return inst;
}

void CallbackManager::RegisterCallbackHandler(void *handler) {
	cache_.insert(std::make_pair(handler, std::map<std::string, void*>()));
}

void CallbackManager::PushArg(cell value) {
	Arg arg;
	arg.type = ARG_VALUE;
	arg.value = value;
	args_.push_front(arg);
}

void CallbackManager::PushArg(cell *value) {
	Arg arg;
	arg.type = ARG_STRING;
	
	int length;
	amx_StrLen(value, &length);
	std::string string(value, value + length);

	arg.string = string;
	args_.push_front(arg);
}

bool CallbackManager::HandleCallback(const char *name) {
	DCCallVM *vm = dcNewCallVM(4096);

#ifdef _WIN32
	// Assuming they are using PLUGIN_CALL when defining callbacks
	dcMode(vm, DC_CALL_C_X86_WIN32_STD);
#else
	// On Linux, the GCC default calling convention is used (which is AFAIK cdecl)
	dcMode(vm, DC_CALL_C_X86_CDECL);
#endif

	// Push the arguments from left to right
	for (std::size_t i = 0; i < args_.size(); i++) {
		if (args_[i].type == ARG_VALUE) {
			dcArgInt(vm, args_[i].value);
		} else {
			dcArgPointer(vm, (DCpointer)args_[i].string.c_str());
		}
	}

	bool retval = true;

	typedef std::map<std::string, void*> LocalCache;
	typedef std::map<void*, LocalCache> Cache;

	// Call each of the registered handlers until false returned
	for (Cache::iterator cIter = cache_.begin(); cIter != cache_.end(); ++cIter) {
		void *function = 0;

		LocalCache lc = cIter->second;
		LocalCache::iterator lcIter = lc.find(name);
		if (lcIter == lc.end()) {
			if ((function = sampgdk_get_plugin_symbol(cIter->first, name)) != 0) {
				lc.insert(std::make_pair(name, function));
			}
		} else {
			function = lcIter->second;
		}

		if (function != 0) {
			retval = dcCallBool(vm, function) != 0;
			if (!retval) {
				break;
			}
		}
	}

	// Pop stored args 
	args_.clear();

	// Destroy the call VM
	dcFree(vm);

	return retval;
}

