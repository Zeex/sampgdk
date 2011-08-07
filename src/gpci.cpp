// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <sampgdk/gpci.h>
#include <sampgdk/wrapper.h>

#include "fakeamx.h"

namespace sampgdk {

SAMPGDK_EXPORT bool SAMPGDK_CALL gpci(int playerid, char *buffer, std::size_t size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("gpci");
    FakeAmxHeapObject buffer_(size);
    cell params[] = {
        3 * 4,
        playerid,
        buffer_.address(),
        size
    };
    bool ret = native(&::fakeAmx, params) != 0;
    buffer_.GetAsString(buffer, size);
    return ret;
}

} // namespace sampgdk
