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
#include "samp.h"
#include "wrapper.h"

#include <string>

namespace samp {

bool SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) {
    static auto native = Wrapper::GetInstance()->GetNative("SetSpawnInfo");
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
    static auto native = Wrapper::GetInstance()->GetNative("SpawnPlayer");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerPos(int playerid, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerPos");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerPosFindZ");
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
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerPos");
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerFacingAngle(int playerid, float angle) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerFacingAngle");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(angle)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerFacingAngle(int playerid, float &angle) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerFacingAngle");
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(&angle)
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerInRangeOfPoint");
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
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerStreamedIn");
    cell params[] = {
        2 * 4,
        playerid,
        forplayerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerInterior(int playerid, int interiorid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerInterior");
    cell params[] = {
        2 * 4,
        playerid,
        interiorid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerInterior(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerInterior");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerHealth(int playerid, float health) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerHealth");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(health)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerHealth(int playerid, float &health) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerHealth");
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(&health)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerArmour(int playerid, float armour) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerArmour");
    cell params[] = {
        2 * 4,
        playerid,
        amx_ftoc(armour)
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerArmour(int playerid, float &armour) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerArmour");
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(&armour)
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerAmmo(int playerid, int weaponslot, int ammo) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerAmmo");
    cell params[] = {
        3 * 4,
        playerid,
        weaponslot,
        ammo
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerAmmo(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerAmmo");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerWeaponState(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerWeaponState");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerTeam(int playerid, int teamid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerTeam");
    cell params[] = {
        2 * 4,
        playerid,
        teamid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerTeam(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerTeam");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerScore(int playerid, int score) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerScore");
    cell params[] = {
        2 * 4,
        playerid,
        score
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerScore(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerScore");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerDrunkLevel(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerDrunkLevel");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerDrunkLevel(int playerid, int level) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerDrunkLevel");
    cell params[] = {
        2 * 4,
        playerid,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerColor(int playerid, long color) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerColor");
    cell params[] = {
        2 * 4,
        playerid,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

long GetPlayerColor(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerColor");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerSkin(int playerid, int skinid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerSkin");
    cell params[] = {
        2 * 4,
        playerid,
        skinid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerSkin(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerSkin");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GivePlayerWeapon(int playerid, int weaponid, int ammo) {
    static auto native = Wrapper::GetInstance()->GetNative("GivePlayerWeapon");
    cell params[] = {
        3 * 4,
        playerid,
        weaponid,
        ammo
    };
    return native(&::fakeAmx, params) != 0;
}

bool ResetPlayerWeapons(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("ResetPlayerWeapons");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerArmedWeapon(int playerid, int weaponid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerArmedWeapon");
    cell params[] = {
        2 * 4,
        playerid,
        weaponid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerWeaponData(int playerid, int slot, int &weapon, int &ammo) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerWeaponData");
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
    static auto native = Wrapper::GetInstance()->GetNative("GivePlayerMoney");
    cell params[] = {
        2 * 4,
        playerid,
        money
    };
    return native(&::fakeAmx, params) != 0;
}

bool ResetPlayerMoney(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("ResetPlayerMoney");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

int SetPlayerName(int playerid, const std::string &name) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerName");
    cstring name_(name.begin(), name.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(name_.c_str())
    };
    return native(&::fakeAmx, params);
}

long GetPlayerMoney(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerMoney");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerState(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerState");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

std::string GetPlayerIp(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerIp");
    cstring name_(16, '\0');
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(name_.data()),
        name_.length()
    };
    native(&::fakeAmx, params);
    return std::string(name_.begin(), name_.end());
}

int GetPlayerPing(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerPing");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerWeapon(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerWeapon");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetPlayerKeys(int playerid, int &keys, int &updown, int &leftright) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerKeys");
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(&keys),
        reinterpret_cast<cell>(&updown),
        reinterpret_cast<cell>(&leftright),
    };
    return native(&::fakeAmx, params) != 0;
}

std::string GetPlayerName(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerName");
    cstring name_(MAX_PLAYER_NAME, '\0');
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(name_.data()),
        name_.length()
    };
    native(&::fakeAmx, params);
    return std::string(name_.begin(), name_.end());
}

bool SetPlayerTime(int playerid, int hour, int minute) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerTime");
    cell params[] = {
        3 * 4,
        playerid,
        hour,
        minute
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerTime(int playerid, int &hour, int &minute) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerTime");
    cell params[] = {
        3 * 4,
        playerid,
        reinterpret_cast<cell>(&hour),
        reinterpret_cast<cell>(&minute)
    };
    return native(&::fakeAmx, params) != 0;
}

bool TogglePlayerClock(int playerid, bool toggle) {
    static auto native = Wrapper::GetInstance()->GetNative("TogglePlayerClock");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWeather(int playerid, int weather) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerWeather");
    cell params[] = {
        2 * 4,
        playerid,
        weather
    };
    return native(&::fakeAmx, params) != 0;
}

bool ForceClassSelection(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("ForceClassSelection");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWantedLevel(int playerid, int level) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerWantedLevel");
    cell params[] = {
        2 * 4,
        playerid,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerWantedLevel(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerWantedLevel");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerFightingStyle(int playerid, int style) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerFightingStyle");
    cell params[] = {
        2 * 4,
        playerid,
        style
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerFightingStyle(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerFightingStyle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerVelocity(int playerid, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerVelocity");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerVelocity");
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z)
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayCrimeReportForPlayer(int playerid, int suspectid, int crime) {
    static auto native = Wrapper::GetInstance()->GetNative("PlayCrimeReportForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        suspectid,
        crime
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerShopName(int playerid, const std::string &shopname) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerShopName");
    cstring shopname_(shopname.begin(), shopname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(shopname_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerSkillLevel(int playerid, int skill, int level) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerSkillLevel");
    cell params[] = {
        3 * 4,
        playerid,
        skill,
        level
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerSurfingVehicleID(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerSurfingVehicleID");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerAttachedObject");
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
    static auto native = Wrapper::GetInstance()->GetNative("RemovePlayerAttachedObject");
    cell params[] = {
        2 * 4,
        playerid,
        index
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerAttachedObjectSlotUsed(int playerid, int index) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerAttachedObjectSlotUsed");
    cell params[] = {
        2 * 4,
        playerid,
        index
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPVarInt(int playerid, const std::string &varname, int value) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPVarInt");
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
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarInt");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetPVarString(int playerid, const std::string &varname, const std::string &value) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPVarString");
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
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarString");
    cstring varname_(varname.begin(), varname.end());
    cstring value_(maxlength, '\0');
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str()),
        reinterpret_cast<cell>(value_.data()),
        maxlength
    };
    auto ret = native(&::fakeAmx, params);
    value.reserve(maxlength);
    amx_GetString(const_cast<char*>(value.data()), value_.c_str(), 0, maxlength);
    return ret != 0;
}

bool SetPVarFloat(int playerid, const std::string &varname, float value) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPVarFloat");
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
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarFloat");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    auto ret = native(&::fakeAmx, params);
    return amx_ctof(ret);
}

bool DeletePVar(int playerid, const std::string &varname) {
    static auto native = Wrapper::GetInstance()->GetNative("DeletePVar");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPVarsUpperIndex(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarsUpperIndex");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetPVarNameAtIndex(int playerid, int index, std::string &varname, size_t maxlength) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarNameAtIndex");
    cstring varname_(maxlength, '\0');
    cell params[] = {
        4 * 4,
        playerid,
        index,
        reinterpret_cast<cell>(varname_.data()),
        maxlength
    };
    auto ret =  native(&::fakeAmx, params);
    varname.reserve(maxlength);
    amx_GetString(const_cast<char*>(varname.data()), varname_.c_str(), 0, maxlength);
    return ret != 0;
}

int GetPVarType(int playerid, const std::string &varname) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPVarType");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        2 * 4,
        playerid,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerChatBubble(int playerid, const std::string &text, long color, float drawdistance, long expiretime) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerChatBubble");
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
    static auto native = Wrapper::GetInstance()->GetNative("PutPlayerInVehicle");
    cell params[] = {
        3 * 4,
        playerid,
        vehicleid,
        seatid
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerVehicleID(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerVehicleID");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int GetPlayerVehicleSeat(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerVehicleSeat");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool RemovePlayerFromVehicle(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("RemovePlayerFromVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool TogglePlayerControllable(int playerid, bool toggle) {
    static auto native = Wrapper::GetInstance()->GetNative("TogglePlayerControllable");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerPlaySound(int playerid, int soundid, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("PlayerPlaySound");
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
    static auto native = Wrapper::GetInstance()->GetNative("ApplyAnimation");
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
    static auto native = Wrapper::GetInstance()->GetNative("ClearAnimations");
    cell params[] = {
        2 * 4,
        playerid,
        forcesync
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerAnimationIndex(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerAnimationIndex");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool GetAnimationName(int index, std::string &animlib, size_t len1, std::string &animname, size_t len2) {
    static auto native = Wrapper::GetInstance()->GetNative("GetAnimationName");
    cstring animlib_(len1, '\0');
    cstring animname_(len2, '\0');
    cell params[] = {
        5 * 4,
        index,
        reinterpret_cast<cell>(animlib_.data()),
        len1,
        reinterpret_cast<cell>(animname_.data()),
        len2
    };
    auto ret =  native(&::fakeAmx, params);
    animlib.reserve(len1);
    amx_GetString(const_cast<char*>(animlib.data()), animlib_.c_str(), 0, len1);
    animname.reserve(len2);
    amx_GetString(const_cast<char*>(animname.data()), animname_.c_str(), 0, len2);
    return ret != 0;
}

int GetPlayerSpecialAction(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerSpecialAction");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool SetPlayerSpecialAction(int playerid, int actionid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerSpecialAction");
    cell params[] = {
        2 * 4,
        playerid,
        actionid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerCheckpoint(int playerid, float x, float y, float z, float size) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerCheckpoint");
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
    static auto native = Wrapper::GetInstance()->GetNative("DisablePlayerCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, 
    float nextx, float nexty, float nextz, float size) 
{
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerRaceCheckpoint");
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
    static auto native = Wrapper::GetInstance()->GetNative("DisablePlayerRaceCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerWorldBounds");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerMarkerForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        showplayerid,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show) {
    static auto native = Wrapper::GetInstance()->GetNative("ShowPlayerNameTagForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        showplayerid,
        show
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, long color, int style) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerMapIcon");
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
    static auto native = Wrapper::GetInstance()->GetNative("RemovePlayerMapIcon");
    cell params[] = {
        2 * 4,
        playerid,
        iconid
    };
    return native(&::fakeAmx, params) != 0;
}

bool AllowPlayerTeleport(int playerid, bool allow) {
    static auto native = Wrapper::GetInstance()->GetNative("AllowPlayerTeleport");
    cell params[] = {
        2 * 4,
        playerid,
        allow
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerCameraPos(int playerid, float x, float y, float z) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerCameraPos");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerCameraLookAt");
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
    static auto native = Wrapper::GetInstance()->GetNative("SetCameraBehindPlayer");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerCameraPos(int playerid, float &x, float &y, float &z) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerCameraPos");
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z),
    };
    return native(&::fakeAmx, params) != 0;
}

bool GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerCameraFrontVector");
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(&x),
        reinterpret_cast<cell>(&y),
        reinterpret_cast<cell>(&z),
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerConnected(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerConnected");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInVehicle(int playerid, int vehicleid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerInVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInAnyVehicle(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerInAnyVehicle");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInCheckpoint(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerInCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerInRaceCheckpoint(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("IsPlayerInRaceCheckpoint");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool SetPlayerVirtualWorld(int playerid, long worldid) {
    static auto native = Wrapper::GetInstance()->GetNative("SetPlayerVirtualWorld");
    cell params[] = {
        2 * 4,
        playerid,
        worldid
    };
    return native(&::fakeAmx, params) != 0;
}

long GetPlayerVirtualWorld(int playerid) {
    static auto native = Wrapper::GetInstance()->GetNative("GetPlayerVirtualWorld");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

bool EnableStuntBonusForPlayer(int playerid, bool enable) {
    static auto native = Wrapper::GetInstance()->GetNative("EnableStuntBonusForPlayer");
    cell params[] = {
        2 * 4,
        playerid,
        enable
    };
    return native(&::fakeAmx, params) != 0;
}

void EnableStuntBonusForAll(bool enable) {
    static auto native = Wrapper::GetInstance()->GetNative("EnableStuntBonusForAll");
    cell params[] = {
        1 * 4,
        enable
    };
    native(&::fakeAmx, params);
}

bool TogglePlayerSpectating(int playerid, bool toggle) {
    static auto native = Wrapper::GetInstance()->GetNative("TogglePlayerSpectating");
    cell params[] = {
        2 * 4,
        playerid,
        toggle
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerSpectatePlayer(int playerid, int targetplayerid, int mode) {
    static auto native = Wrapper::GetInstance()->GetNative("PlayerSpectatePlayer");
    cell params[] = {
        3 * 4,
        playerid,
        targetplayerid,
        mode
    };
    return native(&::fakeAmx, params) != 0;
}

bool PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode) {
    static auto native = Wrapper::GetInstance()->GetNative("PlayerSpectateVehicle");
    cell params[] = {
        3 * 4,
        playerid,
        targetvehicleid,
        mode
    };
    return native(&::fakeAmx, params) != 0;
}

bool StartRecordingPlayerData(int playerid, int recordtype, const std::string &recordname) {
    static auto native = Wrapper::GetInstance()->GetNative("StartRecordingPlayerData");
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
    static auto native = Wrapper::GetInstance()->GetNative("StopRecordingPlayerData");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

} // namespace samp