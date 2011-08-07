// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <cstring>
#include <limits>

#include "fakeamx.h"

static cell fakeAmxData[4096];

AMX_HEADER fakeAmxHeader = {
    0, // size
    AMX_MAGIC, // magic
    MIN_FILE_VERSION, // file_version
    MIN_AMX_VERSION, // amx_version
    0, // flags
    0, // defsize
    0, // cod
    reinterpret_cast<int32_t>(::fakeAmxData) - 
        reinterpret_cast<int32_t>(&::fakeAmxHeader), // dat
    0, // hea 
    0, // stp
    0, // cip
    0, // publics
    0, // natives
    0, // libraries
    0, // pubvars
    0, // tags
    0, // nametable
};

AMX fakeAmx = {
    reinterpret_cast<unsigned char*>(&::fakeAmxHeader), // base
    reinterpret_cast<unsigned char*>(::fakeAmxData), // data
    amx_Callback, // callback
    0, // debug hook
    0, // cip
    0, // frm
    0, // hea
    0, // hlw
    0, // stk
    std::numeric_limits<int32_t>::max(), // stp
    0, // flags
    {0}, // usertags
    {0}, // userdata
    AMX_ERR_NONE, // error
    0, // paramcount 
    0, // pri
    0, // alt
    0, // reset_stk
    0, // reset_hea
    0, // sysreq_d
};

cell FakeAmxPush(size_t cells) {
    cell address = ::fakeAmx.hea;
    ::fakeAmx.hea += cells * sizeof(cell);
    return address;
}

cell FakeAmxPush(const char *s) {
    cell address = FakeAmxPush(strlen(s));
    amx_SetString(::fakeAmxData + address, s, 0, 0, strlen(s) + 1);
    return address;
}

void FakeAmxGet(cell address, cell &value) {
    value = *reinterpret_cast<cell*>(::fakeAmx.data + address);
}

void FakeAmxGet(cell address, char *value, size_t size) {
    cell *ptr = reinterpret_cast<cell*>(::fakeAmx.data + address);
    amx_GetString(value, ptr, 0, size);
}

void FakeAmxPop(cell address) {
    if (::fakeAmx.hea > address) {
        ::fakeAmx.hea = address;
    }
}