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

#include <sampgdk/amxplugin.h>
#include <sampgdk/export.h>

namespace sampgdk {

class WrapperImpl;

class SAMPGDK_EXPORT Wrapper {
public:
	typedef cell (SAMPGDK_CALL *PublicHandler)(AMX *amx);

	~Wrapper();

	static Wrapper *GetInstance();

	void Initialize(void **ppPluginData);

	void SetNative(const char *name, AMX_NATIVE native);
	AMX_NATIVE GetNative(const char *name) const;

	void SetPublicHook(const char *name, PublicHandler handler, cell badReturn);
	bool ExecutePublicHook(AMX *amx, cell *retval, const char *name) const;

private:
	Wrapper();
	WrapperImpl *pimpl_;
};

} // namespace sampgdk

#endif

