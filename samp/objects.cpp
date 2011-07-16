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

#include "fakeamx.h"
#include "wrapper.h"

namespace samp {

int CreateObject(int modelid, float X, float Y, float Z, float rX, float rY, float rZ, float DrawDistance) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreateObject");
    cell params[] = {
        8 * 4,
        modelid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ),
        amx_ftoc(DrawDistance)
    };
    return native(&::fakeAmx, params);
}

bool AttachObjectToVehicle(int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, 
    float fRotX, float fRotY, float fRotZ)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AttachObjectToVehicle");
    cell params[] = {
        8 * 4,
        objectid,
        vehicleid,
        amx_ftoc(fOffsetX),
        amx_ftoc(fOffsetY),
        amx_ftoc(fOffsetZ),
        amx_ftoc(fRotX),
        amx_ftoc(fRotY),
        amx_ftoc(fRotZ)
    };
    return native(&::fakeAmx, params) != 0;
}

void SetObjectPos(int objectid, float X, float Y, float Z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetObjectPos");
    cell params[] = {
        4 * 4,
        objectid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z)
    };
    native(&::fakeAmx, params);
}

bool GetObjectPos(int objectid, float &X, float &Y, float &Z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetObjectPos");
    cell params[] = {
        4 * 4,
        objectid,
        reinterpret_cast<cell>(&X),
        reinterpret_cast<cell>(&Y),
        reinterpret_cast<cell>(&Z)
    };
    return native(&::fakeAmx, params) != 0;
}

void SetObjectRot(int objectid, float RotX, float RotY, float RotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetObjectRot");
    cell params[] = {
        4 * 4,
        objectid,
        amx_ftoc(RotX),
        amx_ftoc(RotY),
        amx_ftoc(RotZ)
    };
    native(&::fakeAmx, params);
}

bool GetObjectRot(int objectid, float &RotX, float &RotY, float &RotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetObjectRot");
    cell params[] = {
        4 * 4,
        objectid,
        reinterpret_cast<cell>(&RotX),
        reinterpret_cast<cell>(&RotY),
        reinterpret_cast<cell>(&RotZ)
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsValidObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsValidObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

void DestroyObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    native(&::fakeAmx, params);
}

int MoveObject(int objectid, float X, float Y, float Z, float Speed) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("MoveObject");
    cell params[] = {
        5 * 4,
        objectid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z),
        amx_ftoc(Speed)
    };
    return native(&::fakeAmx, params);
}

bool StopObject(int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StopObject");
    cell params[] = {
        1 * 4,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

int CreatePlayerObject(int playerid, int modelid, float X, float Y, float Z, 
    float rX, float rY, float rZ, float DrawDistance)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreatePlayerObject");
    cell params[] = {
        9 * 4,
        playerid,
        modelid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z),
        amx_ftoc(rX),
        amx_ftoc(rY),
        amx_ftoc(rZ),
        amx_ftoc(DrawDistance)
    };
    return native(&::fakeAmx, params);
}

void SetPlayerObjectPos(int playerid, int objectid, float X, float Y, float Z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerObjectPos");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z)
    };
    native(&::fakeAmx, params);
}

bool GetPlayerObjectPos(int playerid, int objectid, float &X, float &Y, float &Z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerObjectPos");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        reinterpret_cast<cell>(&X),
        reinterpret_cast<cell>(&Y),
        reinterpret_cast<cell>(&Z)
    };
    return native(&::fakeAmx, params) != 0;
}

void SetPlayerObjectRot(int playerid, int objectid, float RotX, float RotY, float RotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerObjectRot");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        amx_ftoc(RotX),
        amx_ftoc(RotY),
        amx_ftoc(RotZ)
    };
    native(&::fakeAmx, params);
}

bool GetPlayerObjectRot(int playerid, int objectid, float &RotX, float &RotY, float &RotZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerObjectRot");
    cell params[] = {
        5 * 4,
        playerid,
        objectid,
        reinterpret_cast<cell>(&RotX),
        reinterpret_cast<cell>(&RotY),
        reinterpret_cast<cell>(&RotZ)
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsValidPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsValidPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

void DestroyPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    native(&::fakeAmx, params);
}

int MovePlayerObject(int playerid, int objectid, float X, float Y, float Z, float Speed) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("MovePlayerObject");
    cell params[] = {
        6 * 4,
        playerid,
        objectid,
        amx_ftoc(X),
        amx_ftoc(Y),
        amx_ftoc(Z),
        amx_ftoc(Speed)
    };
    return native(&::fakeAmx, params);
}

bool StopPlayerObject(int playerid, int objectid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StopPlayerObject");
    cell params[] = {
        2 * 4,
        playerid,
        objectid
    };
    return native(&::fakeAmx, params) != 0;
}

void AttachObjectToPlayer(int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, 
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

void AttachPlayerObjectToPlayer(int objectplayer, int objectid, int attachplayer, 
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

} // namespace samp