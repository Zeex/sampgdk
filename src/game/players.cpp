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
    FakeAmxHeapObject x_(&x, 1);
    FakeAmxHeapObject y_(&y, 1);
    FakeAmxHeapObject z_(&z, 1);
    cell params[] = {
        4 * 4,
        playerid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.asFloat();
    y = y_.asFloat();
    z = z_.asFloat();
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
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(&angle)
    };
    return native(&::fakeAmx, params) != 0;
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
    FakeAmxHeapObject health_(&health, 1);
    cell params[] = {
        2 * 4,
        playerid,
        health_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    health = health_.asFloat();
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
    FakeAmxHeapObject armour_(&armour, 1);
    cell params[] = {
        2 * 4,
        playerid,
        armour_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    armour = armour_.asFloat();
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
    cell params[] = {
        4 * 4,
        playerid,
        slot,
        reinterpret_cast<cell>(&weapon),
        reinterpret_cast<cell>(&ammo),
    };
    return native(&::fakeAmx, params) != 0;
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

int SetPlayerName(int playerid, const std::string &name) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerName");
    cstring name_(name.begin(), name.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(name_.c_str())
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

std::string GetPlayerIp(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerIp");
    cstring ip_(16, 0);
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(ip_.data()),
        16
    };
    native(&::fakeAmx, params);
    int length;
    amx_StrLen(ip_.data(), &length);
    return std::string(ip_.begin(), ip_.begin() + length);
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
    FakeAmxHeapObject keys_(&keys, 1);
    FakeAmxHeapObject updown_(&updown, 1);
    FakeAmxHeapObject leftright_(&leftright, 1);
    cell params[] = {
        4 * 4,
        playerid,
        keys_.address(),
        updown_.address(),
        leftright_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    keys = keys_.asCell();
    updown = updown_.asCell();
    leftright = leftright_.asCell();
    return ret;
}

std::string GetPlayerName(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerName");
    cstring name_(MAX_PLAYER_NAME, 0);
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(name_.data()),
        MAX_PLAYER_NAME
    };
    native(&::fakeAmx, params);
    int length;
    amx_StrLen(name_.data(), &length);
    return std::string(name_.begin(), name_.begin() + length);
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
    FakeAmxHeapObject hour_(&hour, 1);
    FakeAmxHeapObject minute_(&minute, 1);
    cell params[] = {
        3 * 4,
        playerid,
        hour_.address(),
        minute_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    hour = hour_.asCell();
    minute = minute_.asCell();
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
    FakeAmxHeapObject x_(&x, 1);
    FakeAmxHeapObject y_(&y, 1);
    FakeAmxHeapObject z_(&z, 1);
    cell params[] = {
        4 * 4,
        playerid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.asFloat();
    y = y_.asFloat();
    z = z_.asFloat();
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

bool SetPlayerShopName(int playerid, const std::string &shopname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerShopName");
    cstring shopname_(shopname.begin(), shopname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(shopname_.c_str())
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

bool SetPVarInt(int playerid, const std::string &varname, int value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarInt");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str()),
        value
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPVarInt(int playerid, const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarInt");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetPVarString(int playerid, const std::string &varname, const std::string &value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarString");
    cstring varname_(varname.begin(), varname.end());
    cstring value_(value.begin(), value.end());
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str()),
        reinterpret_cast<cell>(value_.c_str()),
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPVarString(int playerid, const std::string &varname, std::string &value, size_t maxlength) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarString");
    cstring varname_(varname.begin(), varname.end());
    cstring value_(maxlength + 1, 0);
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str()),
        reinterpret_cast<cell>(value_.data()),
        maxlength + 1
    };
    cell ret = native(&::fakeAmx, params);
    int length;
    amx_StrLen(value_.data(), &length);
    value.reserve(length + 1);
    amx_GetString(&value[0], value_.c_str(), 0, length + 1);
    return ret != 0;
}

bool SetPVarFloat(int playerid, const std::string &varname, float value) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPVarFloat");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str()),
        amx_ftoc(value)
    };
    return native(&::fakeAmx, params) != 0;
}

float GetPVarFloat(int playerid, const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarFloat");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    cell ret = native(&::fakeAmx, params);
    return amx_ctof(ret);
}

bool DeletePVar(int playerid, const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DeletePVar");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
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

bool GetPVarNameAtIndex(int playerid, int index, std::string &varname, size_t maxlength) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarNameAtIndex");
    cstring varname_(maxlength + 1, 0);
    cell params[] = {
        4 * 4,
        playerid,
        index,
        reinterpret_cast<cell>(varname_.data()),
        maxlength + 1
    };
    cell ret =  native(&::fakeAmx, params);
    int length;
    amx_StrLen(varname_.data(), &length);
    varname.reserve(length + 1);
    amx_GetString(&varname[0], varname_.c_str(), 0, length + 1);
    return ret != 0;
}

int GetPVarType(int playerid, const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPVarType");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerChatBubble(int playerid, const std::string &text, long color, float drawdistance, long expiretime) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetPlayerChatBubble");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        5 * 4,
        playerid,
        reinterpret_cast<cell>(text_.c_str()),
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

bool ApplyAnimation(int playerid, const std::string &animlib, const std::string &animname, 
    float fDelta, bool loop, bool lockx, bool locky, bool freeze, long time, bool forcesync)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ApplyAnimation");
    cstring animlib_(animlib.begin(), animlib.end());
    cstring animname_(animname.begin(), animname.end());
    cell params[] = {
        10 * 4,
        playerid,
        reinterpret_cast<cell>(animlib_.c_str()),
        reinterpret_cast<cell>(animname_.c_str()),
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

bool GetAnimationName(int index, std::string &animlib, size_t len1, std::string &animname, size_t len2) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetAnimationName");
    cstring animlib_(len1 + 1, 0);
    cstring animname_(len2 + 1, 0);
    cell params[] = {
        5 * 4,
        index,
        reinterpret_cast<cell>(animlib_.data()),
        len1 + 1,
        reinterpret_cast<cell>(animname_.data()),
        len2 + 1
    };
    cell ret =  native(&::fakeAmx, params);
    int trueLen1;
    amx_StrLen(animlib_.data(), &trueLen1);
    animlib.reserve(trueLen1 + 1);
    amx_GetString(&animlib[0], animlib_.c_str(), 0, trueLen1 + 1);
    int trueLen2;
    amx_StrLen(animname_.data(), &trueLen2);
    animname.reserve(trueLen2 + 1);
    amx_GetString(&animname[0], animname_.c_str(), 0, trueLen2 + 1);
    return ret != 0;
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
    FakeAmxHeapObject x_(&x, 1);
    FakeAmxHeapObject y_(&y, 1);
    FakeAmxHeapObject z_(&z, 1);
    cell params[] = {
        4 * 4,
        playerid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.asFloat();
    y = y_.asFloat();
    z = z_.asFloat();
    return ret;
}

bool GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerCameraFrontVector");
    FakeAmxHeapObject x_(&x, 1);
    FakeAmxHeapObject y_(&y, 1);
    FakeAmxHeapObject z_(&z, 1);
    cell params[] = {
        4 * 4,
        playerid,
        x_.address(),
        y_.address(),
        z_.address()
    };
    bool ret = native(&::fakeAmx, params) != 0;
    x = x_.asFloat();
    y = y_.asFloat();
    z = z_.asFloat();
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

bool StartRecordingPlayerData(int playerid, int recordtype, const std::string &recordname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("StartRecordingPlayerData");
    cstring recordname_(recordname.begin(), recordname.end());
    cell params[] = {
        3 * 4,
        playerid,
        recordtype,
        reinterpret_cast<cell>(recordname_.c_str())
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

