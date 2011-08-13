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

// Some popular SA:MP scripts/includes use funcidx() to hook callbacks, etc.
// Since we hook amx_FindPublic to force it always return AMX_ERR_NONE, 
// the funcidx() function have become bugged and doesn't return -1 anymore
// but AMX_EXEC_GDK (which is not -1).
// So we provide our own implementation of funcidx which takes that fact into account.
// Thanks to Incognito for finding this bug.

#include <cstdlib>

#if defined HAVE_MALLOC_H
	#include <malloc.h>
#endif

#include <sampgdk/core.h>

#include "amx/amx.h"

// native funcidx(const funcname[]);
cell AMX_NATIVE_CALL funcidx(AMX *amx, cell *params) {
	char *funcname;
	amx_StrParam(amx, params[1], funcname);
	int index;
	int error = amx_FindPublic(amx, funcname, &index);
	if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE && index == AMX_EXEC_GDK)) {
		return -1;
	}
	return index;
}

