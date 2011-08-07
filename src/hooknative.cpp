// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <cstring>

#include "hooknative.h"

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

