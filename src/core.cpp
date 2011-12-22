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

#include <sampgdk/config.h>
#include <sampgdk/core.h>

#include <sampgdk/version.h>

#include "wrapper.h"

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **ppPluginData) {
	static bool initialized = false;
	if (!initialized) {
		Wrapper::Initialize(ppPluginData);
		initialized = true;
	}
}

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize() {
	// nothing
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_major() {
	return SAMPGDK_VERSION_MAJOR;
}

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_minor() {
	return SAMPGDK_VERSION_MINOR;
}

SAMPGDK_EXPORT const char *SAMPGDK_CALL sampgdk_version() {
	return SAMPGDK_VERSION_STRING;
}
