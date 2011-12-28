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
#include <cstdio>
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

int CallbackManager::HandleCallback(const char *name, int badRetVal) {
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
			// Since we are on x86 cell/char*/float are all of the same size
			switch (args_.size()) {
			case 0:
				retVal = ((int (PLUGIN_CALL*)())function)();
				break;
			case 1:
				retVal = ((int (PLUGIN_CALL*)(cell))function)(
					args_[0]->as_cell());
				break;
			case 2:
				retVal = ((int (PLUGIN_CALL*)(cell, cell))function)(
					args_[0]->as_cell(),
					args_[1]->as_cell());
				break;
			case 3:
				retVal = ((int (PLUGIN_CALL*)(cell, cell, cell))function)(
					args_[0]->as_cell(),
					args_[1]->as_cell(),
					args_[2]->as_cell());
				break;
			case 4:
				retVal = ((int (PLUGIN_CALL*)(cell, cell, cell, cell))function)(
					args_[0]->as_cell(),
					args_[1]->as_cell(),
					args_[2]->as_cell(),
					args_[3]->as_cell());
				break;
			case 5:
				retVal = ((int (PLUGIN_CALL*)(cell, cell, cell, cell, cell))function)(
					args_[0]->as_cell(),
					args_[1]->as_cell(),
					args_[2]->as_cell(),
					args_[3]->as_cell(),
					args_[4]->as_cell());
				break;
			default:
				assert(0 && "Got more than 5 arguments");
			}
			if (retVal == badRetVal) {
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
