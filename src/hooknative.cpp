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

#include <cstring>

#include <sampgdk/amx/amx.h>

AMX_NATIVE HookNative(AMX *amx, const char *nativeName, AMX_NATIVE native) {
    AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
    AMX_FUNCSTUBNT *natives = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base + hdr->natives);

    int numberOfNatives;
    amx_NumNatives(amx, &numberOfNatives);

    for (int i = 0; i < numberOfNatives; i++) {
        char *currentName = reinterpret_cast<char*>(amx->base + natives[i].nameofs);
        if (std::strcmp(currentName, nativeName) == 0) {
            cell address = natives[i].address;
            natives[i].address = reinterpret_cast<cell>(native);
            return reinterpret_cast<AMX_NATIVE>(address);
        }
    }

    return 0;
}

