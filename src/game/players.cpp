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

#include <string>

#include <sampgdk/game/samp.h>
#include <sampgdk/wrapper/wrapper.h>

#include "fakeamx.h"

namespace sampgdk {

bool SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetSpawnInfo");
    cell params[] = {
        13 * 4,
        playerid,
        team,
        skin,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(rotation),
        weapon1,
        weapon1_ammo,
        weapon2,
        weapon2_ammo,
        weapon3,
        weapon3_ammo
    };
    return native(&::fakeAmx, params) != 0;
}

bool SpawnPlayer(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SpawnPlayer");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerPos(int playerid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerPos");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerPosFindZ(int playerid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerPosFindZ");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerPos(int playerid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerPos");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        playerid,
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

bool SetPlayerFacingAngle(int playerid, float angle) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerFacingAngle");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(angle)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerFacingAngle(int playerid, float &angle) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerFacingAngle");
    FakeAmxHeapObject a_;
    cell params[] = {
        2 * 4,
        playerid,
        a_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    angle = a_.GetAsFloat();
    return ret;
}

bool IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerInRangeOfPoint");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(range),
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerStreamedIn(int playerid, int forplayerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerStreamedIn");
    cell params[] = {
        2 * 4,
        playerid,
        forplayerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerInterior(int playerid, int interiorid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerInterior");
    cell params[] = {
        2 * 4,
        playerid,
        interiorid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerInterior(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerInterior");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerHealth(int playerid, float health) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerHealth");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(health)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerHealth(int playerid, float &health) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerHealth");
    FakeAmxHeapObject health_;
    cell params[] = {
        2 * 4,
        playerid,
        health_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    health = health_.GetAsFloat();
    return ret;
}

bool SetPlayerArmour(int playerid, float armour) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerArmour");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(armour)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerArmour(int playerid, float &armour) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerArmour");
    FakeAmxHeapObject armour_;
    cell params[] = {
        2 * 4,
        playerid,
        armour_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    armour = armour_.GetAsFloat();
    return ret;
}

bool SetPlayerAmmo(int playerid, int weaponslot, int ammo) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerAmmo");
    cell params[] = {
        3 * 4,
        playerid,
        weaponslot,
        ammo
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerAmmo(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerAmmo");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerWeaponState(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerWeaponState");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerTeam(int playerid, int teamid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerTeam");
    cell params[] = {
        2 * 4,
        playerid,
        teamid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerTeam(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerTeam");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerScore(int playerid, long score) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerScore");
    cell params[] = {
        2 * 4,
        playerid,
        score
    };
    return native(&::fakeAmx, params) != 0;
}

long GetPlayerScore(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerScore");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerDrunkLevel(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerDrunkLevel");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerDrunkLevel(int playerid, int level) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerDrunkLevel");
    cell params[] = {
        2 * 4,
        playerid,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerColor(int playerid, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerColor");
    cell params[] = {
        2 * 4,
        playerid,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

long GetPlayerColor(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerColor");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerSkin(int playerid, int skinid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerSkin");
    cell params[] = {
        2 * 4,
        playerid,
        skinid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerSkin(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerSkin");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GivePlayerWeapon(int playerid, int weaponid, int ammo) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GivePlayerWeapon");
    cell params[] = {
        3 * 4,
        playerid,
        weaponid,
        ammo
    };
    return native(&::fakeAmx, params) != 0;
}

bool ResetPlayerWeapons(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ResetPlayerWeapons");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerArmedWeapon(int playerid, int weaponid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerArmedWeapon");
    cell params[] = {
        2 * 4,
        playerid,
        weaponid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerWeaponData(int playerid, int slot, int &weapon, int &ammo) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerWeaponData");
    FakeAmxHeapObject weapon_;
    FakeAmxHeapObject ammo_;
    cell params[] = {
        4 * 4,
        playerid,
        slot,
        weapon_.address(),
        ammo_.address(),
    };
    bool ret = native(&::fakeAmx, params) != 0;
    weapon = weapon_.Get();
    ammo = weapon_.Get();
    return ret;
}

bool GivePlayerMoney(int playerid, long money) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GivePlayerMoney");
    cell params[] = {
        2 * 4,
        playerid,
        money
    };
    return native(&::fakeAmx, params) != 0;
}

bool ResetPlayerMoney(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ResetPlayerMoney");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

int SetPlayerName(int playerid, const char *name) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerName");
    FakeAmxHeapObject name_(name);
    cell params[] = {
        2 * 4,
        playerid,
        name_.address()
    };
    return native(&::fakeAmx, params);
}

long GetPlayerMoney(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerMoney");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerState(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerState");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetPlayerIp(int playerid, char *ip, size_t size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerIp");
    FakeAmxHeapObject ip_(size);
    cell params[] = {
        3 * 4,
        playerid,
        ip_.address(),
        size
    };
    bool ret = native(&::fakeAmx, params) != 0;
    ip_.GetAsString(ip, size);
    return ret;
}

bool GetPlayerIp(int playerid, char (&ip)[16]) {
    return GetPlayerIp(playerid, ip, 16);
}

int GetPlayerPing(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerPing");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerWeapon(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerWeapon");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetPlayerKeys(int playerid, int &keys, int &updown, int &leftright) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerKeys");
    FakeAmxHeapObject keys_;
    FakeAmxHeapObject updown_;
    FakeAmxHeapObject leftright_;
    cell params[] = {
        4 * 4,
        playerid,
        keys_.address(),
        updown_.address(),
        leftright_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    keys = keys_.Get();
    updown = updown_.Get();
    leftright = leftright_.Get();
    return ret;
}

bool GetPlayerName(int playerid, char *name, size_t size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerName");
    FakeAmxHeapObject name_(size);
    cell params[] = {
        3 * 4,
        playerid,
        name_.address(),
        size
    };
    bool ret = native(&::fakeAmx, params) != 0;
    name_.GetAsString(name, size);
    return ret;
}

bool GetPlayerName(int playerid, char (&name)[MAX_PLAYER_NAME]) {
    return GetPlayerName(playerid, name, MAX_PLAYER_NAME);
}

bool SetPlayerTime(int playerid, int hour, int minute) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerTime");
    cell params[] = {
        3 * 4,
        playerid,
        hour,
        minute
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerTime(int playerid, int &hour, int &minute) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerTime");
    FakeAmxHeapObject hour_;
    FakeAmxHeapObject minute_;
    cell params[] = {
        3 * 4,
        playerid,
        hour_.address(),
        minute_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    hour = hour_.Get();
    minute = minute_.Get();
    return ret;
}

bool TogglePlayerClock(int playerid, bool toggle) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TogglePlayerClock");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWeather(int playerid, int weather) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerWeather");
    cell params[] = {
        2 * 4,
        playerid,
        weather
    };
    return native(&::fakeAmx, params) != 0;
}

bool ForceClassSelection(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ForceClassSelection");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWantedLevel(int playerid, int level) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerWantedLevel");
    cell params[] = {
        2 * 4,
        playerid,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerWantedLevel(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerWantedLevel");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerFightingStyle(int playerid, int style) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerFightingStyle");
    cell params[] = {
        2 * 4,
        playerid,
        style
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerFightingStyle(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerFightingStyle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerVelocity(int playerid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerVelocity");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerVelocity( int playerid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerVelocity");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        playerid,
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

bool PlayCrimeReportForPlayer(int playerid, int suspectid, int crime) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("PlayCrimeReportForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        suspectid,
        crime
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerShopName(int playerid, const char *shopname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerShopName");
    FakeAmxHeapObject shopname_(shopname);
    cell params[] = {
        2 * 4,
        playerid,
        shopname_.address()
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerSkillLevel(int playerid, int skill, int level) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerSkillLevel");
    cell params[] = {
        3 * 4,
        playerid,
        skill,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerSurfingVehicleID(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerSurfingVehicleID");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, 
    float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, 
    float fScaleY, float fScaleZ) 
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerAttachedObject");
    cell params[] = {
        13 * 4,
        playerid,
        index,
        modelid,
        bone,
        amx_ftoc(fOffsetX),
        amx_ftoc(fOffsetY),
        amx_ftoc(fOffsetZ),
        amx_ftoc(fRotX),
        amx_ftoc(fRotY),
        amx_ftoc(fRotZ),
        amx_ftoc(fScaleX),
        amx_ftoc(fScaleY),
        amx_ftoc(fScaleZ)
    };
    return native(&::fakeAmx, params) != 0;
}

bool RemovePlayerAttachedObject(int playerid, int index) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("RemovePlayerAttachedObject");
    cell params[] = {
        2 * 4,
        playerid,
        index
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerAttachedObjectSlotUsed(int playerid, int index) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerAttachedObjectSlotUsed");
    cell params[] = {
        2 * 4,
        playerid,
        index
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPVarInt(int playerid, const char *varname, int value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarInt");
    FakeAmxHeapObject varname_(varname);
    cell params[] = {
        3 * 4,
        playerid,
        varname_.address(),
        value
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPVarInt(int playerid, const char *varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarInt");
    FakeAmxHeapObject varname_(varname);;
    cell params[] = {
        2 * 4,
        playerid,
        varname_.address()
    };
    return native(&::fakeAmx, params);
}

bool SetPVarString(int playerid, const char *varname, const char *value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarString");
    FakeAmxHeapObject varname_(varname);
    FakeAmxHeapObject value_(value);
    cell params[] = {
        3 * 4,
        playerid,
        varname_.address(),
        value_.address()
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPVarString(int playerid, const char *varname, char *value, size_t size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarString");
    FakeAmxHeapObject varname_(varname);
    FakeAmxHeapObject value_(size);
    cell params[] = {
        4 * 4,
        playerid,
        varname_.address(),
        value_.address(),
        size
    };
    bool ret = native(&::fakeAmx, params) != 0;
    value_.GetAsString(value, size);
    return ret;
}

bool SetPVarFloat(int playerid, const char *varname, float value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarFloat");
    FakeAmxHeapObject varname_(varname);
    cell params[] = {
        3 * 4,
        playerid,
        varname_.address(),
        amx_ftoc(value)
    };
    return native(&::fakeAmx, params) != 0;
}

float GetPVarFloat(int playerid, const char *varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarFloat");
    FakeAmxHeapObject varname_(varname);
    cell params[] = {
        2 * 4,
        playerid,
        varname_.address()
    };
    cell ret = native(&::fakeAmx, params);
    return amx_ctof(ret);
}

bool DeletePVar(int playerid, const char *varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DeletePVar");
    FakeAmxHeapObject varname_(varname);
    cell params[] = {
        2 * 4,
        playerid,
        varname_.address()
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPVarsUpperIndex(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarsUpperIndex");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetPVarNameAtIndex(int playerid, int index, char *varname, size_t size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarNameAtIndex");
    FakeAmxHeapObject varname_(size);
    cell params[] = {
        4 * 4,
        playerid,
        index,
        varname_.address(),
        size
    };
    bool ret =  native(&::fakeAmx, params) != 0;
    return ret;
}

int GetPVarType(int playerid, const char *varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarType");
    FakeAmxHeapObject varname_(varname);
    cell params[] = {
        2 * 4,
        playerid,
        varname_.address()
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerChatBubble(int playerid, const char *text, long color, float drawdistance, long expiretime) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerChatBubble");
    FakeAmxHeapObject text_(text);
    cell params[] = {
        5 * 4,
        playerid,
        text_.address(),
        color,
        amx_ftoc(drawdistance),
        expiretime
    };
    return native(&::fakeAmx, params) != 0;
}

bool PutPlayerInVehicle(int playerid, int vehicleid, int seatid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("PutPlayerInVehicle");
    cell params[] = {
        3 * 4,
        playerid,
        vehicleid,
        seatid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerVehicleID(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerVehicleID");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerVehicleSeat(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerVehicleSeat");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool RemovePlayerFromVehicle(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("RemovePlayerFromVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool TogglePlayerControllable(int playerid, bool toggle) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TogglePlayerControllable");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerPlaySound(int playerid, int soundid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("PlayerPlaySound");
    cell params[] = {
        5 * 4,
        playerid,
        soundid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool ApplyAnimation(int playerid, const char *animlib, const char *animname, 
    float fDelta, bool loop, bool lockx, bool locky, bool freeze, long time, bool forcesync)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ApplyAnimation");
    FakeAmxHeapObject animlib_(animlib);
    FakeAmxHeapObject animname_(animname);
    cell params[] = {
        10 * 4,
        playerid,
        animlib_.address(),
        animname_.address(),
        amx_ftoc(fDelta),
        loop,
        lockx,
        locky,
        freeze,
        time,
        forcesync
    };
    return native(&::fakeAmx, params) != 0;
}

bool ClearAnimations(int playerid, bool forcesync) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ClearAnimations");
    cell params[] = {
        2 * 4,
        playerid,
        forcesync
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerAnimationIndex(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerAnimationIndex");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetAnimationName(int index, char *animlib, size_t animlib_size, char *animname, size_t animname_size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetAnimationName");
    FakeAmxHeapObject animlib_(animlib_size);
    FakeAmxHeapObject animname_(animname_size);
    cell params[] = {
        5 * 4,
        index,
        animlib_.address(),
        animlib_size,
        animname_.address(),
        animname_size
    };
    bool ret =  native(&::fakeAmx, params) != 0;
    animlib_.GetAsString(animlib, animlib_size);
    animname_.GetAsString(animname, animname_size);
    return ret;
}

int GetPlayerSpecialAction(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerSpecialAction");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerSpecialAction(int playerid, int actionid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerSpecialAction");
    cell params[] = {
        2 * 4,
        playerid,
        actionid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerCheckpoint(int playerid, float x, float y, float z, float size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerCheckpoint");
    cell params[] = {
        5 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(size)
    };
    return native(&::fakeAmx, params) != 0;
}

bool DisablePlayerCheckpoint(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisablePlayerCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, 
    float nextx, float nexty, float nextz, float size) 
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerRaceCheckpoint");
    cell params[] = {
        9 * 4,
        playerid,
        type,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(nextx),
        amx_ftoc(nexty),
        amx_ftoc(nextz),
        amx_ftoc(size)
    };
    return native(&::fakeAmx, params) != 0;
}

bool DisablePlayerRaceCheckpoint(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisablePlayerRaceCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerWorldBounds");
    cell params[] = {
        5 * 4,
        playerid,
        amx_ftoc(x_max),
        amx_ftoc(x_min),
        amx_ftoc(y_max),
        amx_ftoc(y_min)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerMarkerForPlayer(int playerid, int showplayerid, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerMarkerForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        showplayerid,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ShowPlayerNameTagForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        showplayerid,
        show
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, long color, int style) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerMapIcon");
    cell params[] = {
        8 * 4,
        playerid,
        iconid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        markertype,
        color,
        style
    };
    return native(&::fakeAmx, params) != 0;
}

bool RemovePlayerMapIcon(int playerid, int iconid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("RemovePlayerMapIcon");
    cell params[] = {
        2 * 4,
        playerid,
        iconid
    };
    return native(&::fakeAmx, params) != 0;
}

bool AllowPlayerTeleport(int playerid, bool allow) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AllowPlayerTeleport");
    cell params[] = {
        2 * 4,
        playerid,
        allow
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerCameraPos(int playerid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerCameraPos");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerCameraLookAt(int playerid, float x, float y, float z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerCameraLookAt");
    cell params[] = {
        4 * 4,
        playerid,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetCameraBehindPlayer(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetCameraBehindPlayer");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerCameraPos(int playerid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerCameraPos");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        playerid,
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

bool GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerCameraFrontVector");
    FakeAmxHeapObject x_;
    FakeAmxHeapObject y_;
    FakeAmxHeapObject z_;
    cell params[] = {
        4 * 4,
        playerid,
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

bool IsPlayerConnected(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerConnected");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInVehicle(int playerid, int vehicleid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerInVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInAnyVehicle(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerInAnyVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInCheckpoint(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerInCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInRaceCheckpoint(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerInRaceCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerVirtualWorld(int playerid, long worldid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerVirtualWorld");
    cell params[] = {
        2 * 4,
        playerid,
        worldid
    };
    return native(&::fakeAmx, params) != 0;
}

long GetPlayerVirtualWorld(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerVirtualWorld");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool EnableStuntBonusForPlayer(int playerid, bool enable) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("EnableStuntBonusForPlayer");
    cell params[] = {
        2 * 4,
        playerid,
        enable
    };
    return native(&::fakeAmx, params) != 0;
}

void EnableStuntBonusForAll(bool enable) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("EnableStuntBonusForAll");
    cell params[] = {
        1 * 4,
        enable
    };
    native(&::fakeAmx, params);
}

bool TogglePlayerSpectating(int playerid, bool toggle) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TogglePlayerSpectating");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerSpectatePlayer(int playerid, int targetplayerid, int mode) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("PlayerSpectatePlayer");
    cell params[] = {
        3 * 4,
        playerid,
        targetplayerid,
        mode
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("PlayerSpectateVehicle");
    cell params[] = {
        3 * 4,
        playerid,
        targetvehicleid,
        mode
    };
    return native(&::fakeAmx, params) != 0;
}

bool StartRecordingPlayerData(int playerid, int recordtype, const char *recordname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StartRecordingPlayerData");
    FakeAmxHeapObject recordname_(recordname);
    cell params[] = {
        3 * 4,
        playerid,
        recordtype,
        recordname_.address()
    };
    return native(&::fakeAmx, params) != 0;
}

bool StopRecordingPlayerData(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StopRecordingPlayerData");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

} // namespace sampgdk

