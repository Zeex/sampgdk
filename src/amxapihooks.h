// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#ifndef SAMPGDK_AMXAPIHOOKS_H
#define SAMPGDK_AMXAPIHOOKS_H

#include <sampgdk/amxplugin.h>

#include "jump.h"

#define AMX_EXEC_GDK (-10)

namespace sampgdk {

class AmxApiHooks {
public:
    static AmxApiHooks *GetInstance() {
        static AmxApiHooks inst;
        return &inst;
    }

    void Initialize(void **amxExportsTable);

private:
    AmxApiHooks();

    static int AMXAPI Register(AMX *amx, AMX_NATIVE_INFO *nativelist, int number);
    static int AMXAPI FindPublic(AMX *amx, const char *name, int *index);
    static int AMXAPI Exec(AMX *amx, cell *retval, int index);

    Jump amxRegisterHook;
    Jump amxFindPublicHook;
    Jump amxExecHook;
};

} // namespace sampgdk

#endif
