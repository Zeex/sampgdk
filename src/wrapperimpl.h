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

#include <map>
#include <string>

#include <sampgdk/wrapper.h>

namespace sampgdk {

class PublicHook {
public:
	PublicHook(Wrapper::PublicHandler handler, cell badReturn) 
		: handler_(handler), badReturn_(badReturn)
	{}

	inline bool Execute(AMX *amx, cell *retval) const {
		return ((*retval = handler_(amx)) != badReturn_);
	}

private:
	Wrapper::PublicHandler handler_;
	cell                   badReturn_;
};

class WrapperImpl {
public:
	WrapperImpl();

	void Initialize(void **ppPluginData);

	void SetNative(const char *name, AMX_NATIVE native);
	AMX_NATIVE GetNative(const char *name) const;

	void SetPublicHook(const char *name, PublicHook handler);
	bool ExecutePublicHook(AMX *amx, cell *retval, const char *name) const;

private:
	std::map<std::string, AMX_NATIVE> natives_;
	std::map<std::string, PublicHook> publicHooks_;
};

} // namespace sampgdk
