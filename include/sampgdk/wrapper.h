// Copyright (c) 2011 Zeex
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

#ifndef SAMPGDK_WRAPPER_H
#define SAMPGDK_WRAPPER_H

#include <map>
#include <string>

#include <sampgdk/amx.h>

#define AMX_EXEC_GDK (-10)

namespace sampgdk {

typedef cell (*PublicHookProc)(AMX *amx);

class PublicHook {
public:
	PublicHook(PublicHookProc fun, cell badRet) 
		: fun_(fun), badRet_(badRet)
	{}

	inline bool Call(AMX *amx, cell *retval) const {
		return ((*retval = fun_(amx)) != badRet_);
	}

private:
	PublicHookProc fun_;
	cell badRet_;
};

class Wrapper {
public:
	static Wrapper &GetInstance();
	static void Initialize(void **ppPluginData);

	void SetNative(const char *name, AMX_NATIVE native);
	AMX_NATIVE GetNative(const char *name) const;

	void SetPublicHook(const char *name, PublicHook hook);
	bool CallPublicHook(AMX *amx, cell *retval, const char *name) const;

private:
	Wrapper();

	std::map<std::string, AMX_NATIVE> natives_;
	std::map<std::string, PublicHook> publicHooks_;
};

} // namespace sampgdk

#endif

