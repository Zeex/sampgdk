// Copyright (c) 2011 Zeex
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

#include <sampgdk/config.h>
#include <sampgdk/amx/amx.h>

#include <deque>
#include <map>
#include <string>

class CallbackArg {
public:
	enum Type {
		CELL,
		STRING
	};

	CallbackArg(cell value);
	CallbackArg(const char *string);
	~CallbackArg();

	cell as_cell() const 
		{ return value_.as_cell; }
	const char *as_string() const 
		{ return value_.as_string; }

	Type type() const 
		{ return type_; }

private:
	// Disable copying
	CallbackArg(const CallbackArg &);
	CallbackArg &operator=(const CallbackArg &);

	union {
		cell        as_cell;
		const char *as_string;
	} value_;
	Type     type_;
};

class CallbackManager {
public:
	static CallbackManager &GetInstance();

	void RegisterCallbackHandler(void *handler);

	template<typename T>
	void PushArgBack(const T &v) { args_.push_back(new CallbackArg(v)); }

	template<typename T>
	void PushArgFront(const T &v) { args_.push_front(new CallbackArg(v)); }

	void ClearArgs();

	int HandleCallback(const char *name,  int badRetVal);

private:
	CallbackManager();

	std::deque<CallbackArg*> args_;
	std::map<void*, std::map<std::string, void*> > cache_;
};

#endif
