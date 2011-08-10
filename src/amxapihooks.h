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
