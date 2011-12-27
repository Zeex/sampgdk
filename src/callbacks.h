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

class CallbackManager {
public:
	static CallbackManager &GetInstance();

	void RegisterCallbackHandler(void *handler);

	template<typename T>
	void PushBack(const T &v) { args_.push_back(v); }

	template<typename T>
	void PushFront(const T &v) { args_.push_front(v); }

	int HandleCallback(const char *name,  int badRetVal);

private:
	CallbackManager();

	enum ArgType {
		ARG_VALUE,
		ARG_STRING
	};

	class Arg {
	public:
		Arg(cell value) : value_(value), type_(ARG_VALUE) {}
		Arg(const char *string) : string_(string), type_(ARG_STRING) {}

		cell value() const { return value_; }
		const std::string &string() const {return string_; }
		ArgType type() const { return type_; }

	private:
		cell        value_;
		std::string string_;
		ArgType     type_;
	};

	std::deque<Arg> args_;
	std::map<void*, std::map<std::string, void*> > cache_;
};

#endif
