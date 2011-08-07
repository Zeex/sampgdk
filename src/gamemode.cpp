// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <cassert>

#include "gamemode.h"

static AMX *pGameMode;

AMX *GetGameMode() {
    return pGameMode;
}

void SetGameMode(AMX *amx) {
    assert(amx != 0);
    ::pGameMode = amx;
}
