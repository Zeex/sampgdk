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

#ifndef SAMPGDK_AMXHOOKS_H
#define SAMPGDK_AMXHOOKS_H
#pragma once

#include <sampgdk/amx.h>

#include <map>
#include <string>
#include <vector>

#include "jump-x86.h"

namespace sampgdk {

class AmxHooks  {
public:
	static void Initialize(void **ppPluginData);
	static void Finalize();

	static int amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
	static int amx_FindPublic(AMX *amx, const char *name, int *index);
	static int amx_Exec(AMX *amx, cell *retval, int index);
	static int amx_Callback(AMX *amx, cell index, cell *result, cell *params);

	static const std::vector<AMX_NATIVE_INFO> &GetNatives() {
		return native_info_;
	}

private:
	static void RegisterCallbacks();

	static AMX *gamemode_;

	static std::string currentPublic_;

	static JumpX86 amx_FindPublicHook_;
	static JumpX86 amx_ExecHook_;
	static JumpX86 amx_RegisterHook_;
	static JumpX86 amx_CallbackHook_;

	static std::vector<AMX_NATIVE_INFO> native_info_;
};

} // namespace sampgdk

#endif // !SAMPGDK_AMXHOOKS_H
