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

#include <sampgdk/config.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

#include "callbacks.h"

#include <cassert>
#include <cstddef>
#include <cstring>

CallbackArg::CallbackArg(cell value)
	: type_(CELL)
{
	value_.as_cell = value;
}

CallbackArg::CallbackArg(const char *string)
	: type_(STRING)
{
	std::size_t size = std::strlen(string) + 1;
	char *buf = new char[size];
	std::memcpy(buf, string, size);
	value_.as_string = buf;
}

CallbackArg::~CallbackArg() {
	if (type_ == STRING) {
		delete[] value_.as_string;
	}
}

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

int CallbackManager::HandleCallback(const char *name, CallbackRetVal badRetVal) {
	int retVal = !badRetVal;

	typedef std::map<std::string, void*> PluginCache;
	typedef std::map<void*, PluginCache> Cache;

	// Call each of the registered handlers until false returned
	for (Cache::iterator cIter = cache_.begin(); cIter != cache_.end(); ++cIter) {
		void *function = 0;

		PluginCache pc = cIter->second;
		PluginCache::iterator pcIter = pc.find(name);

		if (pcIter == pc.end()) {
			if ((function = sampgdk_get_plugin_symbol(cIter->first, name)) != 0) {
				pc.insert(std::make_pair(name, function));
			}
		} else {
			function = pcIter->second;
		}

		if (function != 0) {
			int i = args_.size();
			#if defined _MSC_VER
				cell arg;
				while (--i >= 0) {
					arg = args_[i]->as_cell();
					__asm push dword ptr [arg]
				}
				__asm call dword ptr [function]
				__asm mov dword ptr [retVal], eax
			#elif defined __GNUC__
				while (--i >= 0) {
					__asm__ __volatile__ (
						"pushl %0;"  :: "r"(args_[i]->as_cell()));
				}
				__asm__ __volatile__ (
					"calll *%0;" :: "r"(function));
				__asm__ __volatile__ (
					"movl %%eax, %0;" : "=r"(retVal));
				#if defined LINUX
					__asm__ __volatile__ (
						"addl %0, %%esp;" :: "r"(args_.size() * 4));
				#endif
			#else
				#error Unsupported compiler
			#endif

			if (badRetVal.IsSet() && retVal == badRetVal) {
				break;
			}
		}
	}

	ClearArgs();
	return retVal;
}

void CallbackManager::ClearArgs() {
	for (std::deque<CallbackArg*>::iterator iterator = args_.begin();
			iterator != args_.end(); ++iterator) {
		delete *iterator;
	}
	args_.clear();
}
