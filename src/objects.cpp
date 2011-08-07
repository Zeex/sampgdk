// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#include <sampgdk/objects.h>
#include <sampgdk/wrapper.h>

#include "fakeamx.h"

namespace sampgdk {

SAMPGDK_EXPORT int SAMPGDK_CALL CreateObject(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreateObject");
    cell params[] = {
        8 * 4,
        modelid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ),
        amx_ftoc(DrawDistance)
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, 
    float frotX, float frotY, float frotZ)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AttachObjectToVehicle");
    cell params[] = {
        8 * 4,
        objectid,
        vehicleid,
        amx_ftoc(fOffsetX),
        amx_ftoc(fOffsetY),
        amx_ftoc(fOffsetZ),
        amx_ftoc(frotX),
        amx_ftoc(frotY),
        amx_ftoc(frotZ)
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectPos(int objectid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetObjectPos");
    cell params[] = {
        4 * 4,
        objectid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectPos(int objectid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetObjectPos");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        objectid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.GetAsFloat();
    y = y_.GetAsFloat();
    z = z_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetObjectRot(int objectid, float rotX, float rotY, float rotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetObjectRot");
    cell params[] = {
        4 * 4,
        objectid,
        amx_ftoc(rotX),
        amx_ftoc(rotY),
        amx_ftoc(rotZ)
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetObjectRot(int objectid, float &rotX, float &rotY, float &rotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetObjectRot");
    FakeAmxHeapObject rotX_;
    FakeAmxHeapObject rotY_;
    FakeAmxHeapObject rotZ_;
    cell params[] = {
        4 * 4,
        objectid,
        rotX_.address(),
        rotY_.address(),
        rotZ_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    rotX = rotX_.GetAsFloat();
    rotY = rotY_.GetAsFloat();
    rotZ = rotZ_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsValidObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL DestroyObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MoveObject(int objectid, float x, float y, float z, float Speed) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("MoveObject");
    cell params[] = {
        5 * 4,
        objectid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(Speed)
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StopObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerObject(int playerid, int modelid, float x, float y, float z, 
    float rX, float rY, float rZ, float DrawDistance)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreatePlayerObject");
    cell params[] = {
        9 * 4,
        playerid,
        modelid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ),
        amx_ftoc(DrawDistance)
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerObjectPos");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectPos(int playerid, int objectid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerObjectPos");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.GetAsFloat();
    y = y_.GetAsFloat();
    z = z_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerObjectRot");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        amx_ftoc(rotX),
        amx_ftoc(rotY),
        amx_ftoc(rotZ)
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerObjectRot(int playerid, int objectid, float &rotX, float &rotY, float &rotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerObjectRot");
    FakeAmxHeapObject rotX_;
    FakeAmxHeapObject rotY_;
    FakeAmxHeapObject rotZ_;
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        rotX_.address(),
        rotY_.address(),
        rotZ_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    rotX = rotX_.GetAsFloat();
    rotY = rotY_.GetAsFloat();
    rotZ = rotZ_.GetAsFloat();
    return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsValidPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL DestroyPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MovePlayerObject(int playerid, int objectid, float x, float y, float z, float Speed) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("MovePlayerObject");
    cell params[] = {
        6 * 4,
        playerid,
        objectid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(Speed)
    };
    return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StopPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, 
    float rX, float rY, float rZ)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AttachObjectToPlayer");
    cell params[] = {
        8 * 4,
        objectid,
        playerid,
        amx_ftoc(OffsetX),
        amx_ftoc(OffsetY),
        amx_ftoc(OffsetZ),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ)
    };
    native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, 
    float OffsetX, float OffsetY, float OffsetZ, float rX, float rY, float rZ)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AttachPlayerObjectToPlayer");
    cell params[] = {
        9 * 4,
        objectplayer,
        objectid,
        attachplayer,
        amx_ftoc(OffsetX),
        amx_ftoc(OffsetY),
        amx_ftoc(OffsetZ),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ)
    };
    native(&::fakeAmx, params);
}

} // namespace sampgdk

