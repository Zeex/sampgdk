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

#include <sampgdk/wrapper/wrapper.h>

#include "fakeamx.h"

namespace samp {

bool SendClientMessage(int playerid, long color, const std::string &message) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendClientMessage");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        3 * 4,
        playerid,
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

void SendClientMessageToAll(long color, const std::string &message) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendClientMessageToAll");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        2 * 4,
        color,
        reinterpret_cast<cell>(message_.c_str())
    };
    native(&::fakeAmx, params);
}

bool SendPlayerMessageToPlayer(int playerid, int senderid, const std::string &message) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendPlayerMessageToPlayer");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        3 * 4,
        playerid,
        senderid,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool SendPlayerMessageToAll(int senderid, const std::string &message) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendPlayerMessageToAll");
    cstring message_(message.begin(), message.end());
    cell params[] = {
        2 * 4,
        senderid,
        reinterpret_cast<cell>(message_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool SendDeathMessage(int killer, int killee, int weapon) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendDeathMessage");
    cell params[] = {
        3 * 4,
        killer,
        killee,
        weapon
    };
    return native(&::fakeAmx, params) != 0;
}

bool GameTextForAll(const std::string &text, long time, int style) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GameTextForAll");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        3 * 4,
        reinterpret_cast<cell>(text_.c_str()),
        time,
        style
    };
    return native(&::fakeAmx, params) != 0;
}

bool GameTextForPlayer(int playerid, const std::string &text, long time, int style) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GameTextForPlayer");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        4 * 4,
        playerid,
        reinterpret_cast<cell>(text_.c_str()),
        time,
        style
    };
    return native(&::fakeAmx, params) != 0;
}

long GetTickCount() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetTickCount");
    return native(&::fakeAmx, 0);
}

int GetMaxPlayers() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetMaxPlayers");
    return native(&::fakeAmx, 0);
}

void SetGameModeText(const std::string &text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetGameModeText");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        1 * 4, 
        reinterpret_cast<cell>(text_.c_str())
    };
    native(&::fakeAmx, params);
}

void SetTeamCount(int count) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetTeamCount");
    cell params[] = {
        1 * 4, 
        count
    };
    native(&::fakeAmx, params);
}

int AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) 
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddPlayerClass");
    cell params[] = {
        11 * 4, 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        weapon1,
        weapon1_ammo,
        weapon2,
        weapon2_ammo,
        weapon3,
        weapon3_ammo
    };
    return native(&::fakeAmx, params);
}

int AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddPlayerClassEx");
    cell params[] = {
        12 * 4, 
        teamid,
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        weapon1,
        weapon1_ammo,
        weapon2,
        weapon2_ammo,
        weapon3,
        weapon3_ammo
    };
    return native(&::fakeAmx, params);
}

int AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddStaticVehicle");
    cell params[] = {
        7 * 4, 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        color1,
        color2
    };
    return native(&::fakeAmx, params);
}

int AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
    long color1, long color2, long respawn_delay) 
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddStaticVehicleEx");
    cell params[] = {
        8 * 4, 
        modelid,
        amx_ftoc(spawn_x),
        amx_ftoc(spawn_y),
        amx_ftoc(spawn_z),
        amx_ftoc(z_angle),
        color1,
        color2,
        respawn_delay
    };
    return native(&::fakeAmx, params);
}

int AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddStaticPickup");
    cell params[] = {
        6 * 4, 
        model,
        type,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        virtualworld
    };
    return native(&::fakeAmx, params);
}

int CreatePickup(int model, int type, float x, float y, float z, long virtualworld) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreatePickup");
    cell params[] = {
        6 * 4, 
        model,
        type,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        virtualworld
    };
    return native(&::fakeAmx, params);
}

bool DestroyPickup(int pickup) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyPickup");
    cell params[] = {
        1 * 4,
        pickup
    };
    return native(&::fakeAmx, params) != 0;
}

void ShowNameTags(int show) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ShowNameTags");
    cell params[] = {
        1 * 4,
        show
    };
    native(&::fakeAmx, params);
}

void ShowPlayerMarkers(int mode) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ShowPlayerMarkers");
    cell params[] = {
        1 * 4,
        mode
    };
    native(&::fakeAmx, params);
}

void GameModeExit() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GameModeExit");
    native(&::fakeAmx, 0);
}

bool SetWorldTime(int hour) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetWorldTime");
    cell params[] = {
        1 * 4,
        hour
    };
    return native(&::fakeAmx, params) != 0;
}

std::string GetWeaponName(int weaponid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetWeaponName");
    cstring name_(50, 0); 
    cell params[] = {
        3 * 4,
        weaponid,
        reinterpret_cast<cell>(name_.data()),
        50
    };
    native(&::fakeAmx, params);
    int length;
    amx_StrLen(name_.data(), &length);
    return std::string(name_.begin(), name_.begin() + length);
}

void EnableTirePopping(bool enable) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("EnableTirePopping");
    cell params[] = {
        1 * 4,
        enable
    };
    native(&::fakeAmx, params);
}

void AllowInteriorWeapons(bool allow) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AllowInteriorWeapons");
    cell params[] = {
        1 * 4,
        allow
    };
    native(&::fakeAmx, params);
}

void SetWeather(int weatherid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetWeather");
    cell params[] = {
        1 * 4,
        weatherid
    };
    native(&::fakeAmx, params);
}

void SetGravity(float gravity) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetGravity");
    cell params[] = {
        1 * 4,
        amx_ftoc(gravity)
    };
    native(&::fakeAmx, params);
}

void AllowAdminTeleport(bool allow) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AllowAdminTeleport");
    cell params[] = {
        1 * 4,
        allow
    };
    native(&::fakeAmx, params);
}

void SetDeathDropAmount(long amount) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetDeathDropAmount");
    cell params[] = {
        1 * 4,
        amount
    };
    native(&::fakeAmx, params);
}

void CreateExplosion(float x, float y, float z, short type, float radius) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreateExplosion");
    cell params[] = {
        5 * 4, 
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        type,
        amx_ftoc(radius)
    };
    native(&::fakeAmx, params);
}

void EnableZoneNames(bool enable) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("EnableZoneNames");
    cell params[] = {
        1 * 4,
        enable
    };
    native(&::fakeAmx, params);
}

void UsePlayerPedAnims() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("UsePlayerPedAnims");
    native(&::fakeAmx, 0);
}

void DisableInteriorEnterExits() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisableInteriorEnterExits");
    native(&::fakeAmx, 0);
}

void SetNameTagDrawDistance(float distance) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetNameTagDrawDistance");
    cell params[] = {
        1 * 4,
        amx_ftoc(distance)
    };
    native(&::fakeAmx, params);
}

void DisableNameTagLOS() {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisableNameTagLOS");
    native(&::fakeAmx, 0);
}

void LimitGlobalChatRadius(float chat_radius) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("LimitGlobalChatRadius");
    cell params[] = {
        1 * 4,
        amx_ftoc(chat_radius)
    };
    native(&::fakeAmx, params);
}

void LimitPlayerMarkerRadius(float marker_radius) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("LimitPlayerMarkerRadius");
    cell params[] = {
        1 * 4,
        amx_ftoc(marker_radius)
    };
    native(&::fakeAmx, params);
}

bool ConnectNPC(const std::string &name, const std::string &script) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ConnectNPC");
    cstring name_(name.begin(), name.end());
    cstring script_(script.begin(), script.end());
    cell params[] = {
        2 * 4,
        reinterpret_cast<cell>(name_.c_str()),
        reinterpret_cast<cell>(script_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerNPC(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerNPC");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsPlayerAdmin(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsPlayerAdmin");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool Kick(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Kick");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool Ban(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Ban");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool BanEx(int playerid, const std::string &reason) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("BanEx");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

void SendRconCommand(const std::string &command) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SendRconCommand");
    cstring command_(command.begin(), command.end());
    cell params[] = {
        1 * 4,
        reinterpret_cast<cell>(command_.c_str()),
    };
    native(&::fakeAmx, params);
}

std::string GetServerVarAsString(const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetServerVarAsString");
    cstring varname_(varname.begin(), varname.end());
    cstring var_(128, '\0'); 
    cell params[] = {
        3 * 4,
        reinterpret_cast<cell>(varname_.c_str()),
        reinterpret_cast<cell>(var_.data()),
        var_.length()
    };
    native(&::fakeAmx, params);
    return std::string(var_.begin(), var_.end());
}

int GetServerVarAsInt(const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetServerVarAsInt");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        1 * 4,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool GetServerVarAsBool(const std::string &varname) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetServerVarAsBool");
    cstring varname_(varname.begin(), varname.end());
    cell params[] = {
        1 * 4,
        reinterpret_cast<cell>(varname_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

int CreateMenu(const std::string &title, int columns, float x, float y, float col1width, float col2width) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreateMenu");
    cstring title_(title.begin(), title.end());
    cell params[] = {
        6 * 4,
        reinterpret_cast<cell>(title_.c_str()),
        columns,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(col1width),
        amx_ftoc(col2width)
    };
    return native(&::fakeAmx, params);
}

bool DestroyMenu(int menuid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DestroyMenu");
    cell params[] = {
        1 * 4,
        menuid
    };
    return native(&::fakeAmx, params) != 0;
}

int AddMenuItem(int menuid, int column, const std::string &menutext) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("AddMenuItem");
    cstring menutext_(menutext.begin(), menutext.end());
    cell params[] = {
        3 * 4,
        menuid,
        column,
        reinterpret_cast<cell>(menutext_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool SetMenuColumnHeader(int menuid, int column, const std::string &columnheader) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("SetMenuColumnHeader");
    cstring columnheader_(columnheader.begin(), columnheader.end());
    cell params[] = {
        3 * 4,
        menuid,
        column,
        reinterpret_cast<cell>(columnheader_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool ShowMenuForPlayer(int menuid, int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ShowMenuForPlayer");
    cell params[] = {
        2 * 4,
        menuid,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool HideMenuForPlayer(int menuid, int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("HideMenuForPlayer");
    cell params[] = {
        2 * 4,
        menuid,
        playerid
    };
    return native(&::fakeAmx, params) != 0;
}

bool IsValidMenu(int menuid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("IsValidMenu");
    cell params[] = {
        1 * 4,
        menuid
    };
    return native(&::fakeAmx, params) != 0;
}

bool DisableMenu(int menuid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisableMenu");
    cell params[] = {
        1 * 4,
        menuid
    };
    return native(&::fakeAmx, params) != 0;
}

bool DisableMenuRow(int menuid, int row) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DisableMenuRow");
    cell params[] = {
        2 * 4,
        menuid,
        row
    };
    return native(&::fakeAmx, params) != 0;
}

int GetPlayerMenu(int playerid) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GetPlayerMenu");
    cell params[] = {
        1 * 4,
        playerid
    };
    return native(&::fakeAmx, params);
}

int TextDrawCreate(float x, float y, const std::string &text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawCreate");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        3 * 4,
        amx_ftoc(x),
        amx_ftoc(y),
        reinterpret_cast<cell>(text_.c_str())
    };
    return native(&::fakeAmx, params);
}

bool TextDrawDestroy(int text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawDestroy");
    cell params[] = {
        1 * 4,
        text
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawLetterSize(int text, float x, float y) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawLetterSize");
    cell params[] = {
        3 * 4,
        text,
        amx_ftoc(x),
        amx_ftoc(y)
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawTextSize(int text, float x, float y) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawTextSize");
    cell params[] = {
        3 * 4,
        text,
        amx_ftoc(x),
        amx_ftoc(y)
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawAlignment(int text, int alignment) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawAlignment");
    cell params[] = {
        2 * 4,
        text,
        alignment
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawColor(int text, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawColor");
    cell params[] = {
        2 * 4,
        text,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawUseBox(int text, bool use) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawUseBox");
    cell params[] = {
        2 * 4,
        text,
        use
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawBoxColor(int text, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawBoxColor");
    cell params[] = {
        2 * 4,
        text,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawSetShadow(int text, int size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawSetShadow");
    cell params[] = {
        2 * 4,
        text,
        size
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawSetOutline(int text, int size) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawSetOutline");
    cell params[] = {
        2 * 4,
        text,
        size
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawBackgroundColor(int text, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawBackgroundColor");
    cell params[] = {
        2 * 4,
        text,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawFont(int text, int font) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawFont");
    cell params[] = {
        2 * 4,
        text,
        font
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawSetProportional(int text, bool set) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawSetProportional");
    cell params[] = {
        2 * 4,
        text,
        set
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawShowForPlayer(int playerid, int text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawShowForPlayer");
    cell params[] = {
        2 * 4,
        text,
        text
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawHideForPlayer(int playerid, int text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawHideForPlayer");
    cell params[] = {
        2 * 4,
        playerid,
        text
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawShowForAll(int text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawShowForAll");
    cell params[] = {
        1 * 4,
        text
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawHideForAll(int text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawHideForAll");
    cell params[] = {
        1 * 4,
        text
    };
    return native(&::fakeAmx, params) != 0;
}

bool TextDrawSetString(int text, const std::string &string) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("TextDrawSetString");
    cstring string_(string.begin(), string.end());
    cell params[] = {
        2 * 4,
        text,
        reinterpret_cast<cell>(string_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

int GangZoneCreate(float minx, float miny, float maxx, float maxy) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneCreate");
    cell params[] = {
        4 * 4,
        amx_ftoc(minx),
        amx_ftoc(miny),
        amx_ftoc(maxx),
        amx_ftoc(maxy)
    };
    return native(&::fakeAmx, params);
}

bool GangZoneDestroy(int zone) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneDestroy");
    cell params[] = {
        1 * 4,
        zone
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneShowForPlayer(int playerid, int zone, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneShowForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        zone,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneShowForAll(int zone, long color) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneShowForAll");
    cell params[] = {
        2 * 4,
        zone,
        color
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneHideForPlayer(int playerid, int zone) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneHideForPlayer");
    cell params[] = {
        2 * 4,
        playerid,
        zone
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneHideForAll(int zone) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneHideForAll");
    cell params[] = {
        1 * 4,
        zone
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneFlashForPlayer(int playerid, int zone, long flashcolor) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneFlashForPlayer");
    cell params[] = {
        3 * 4,
        playerid,
        zone,
        flashcolor
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneFlashForAll(int zone, long flashcolor) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneFlashForAll");
    cell params[] = {
        2 * 4,
        zone,
        flashcolor
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneStopFlashForPlayer(int playerid, int zone) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneStopFlashForPlayer");
    cell params[] = {
        2 * 4,
        playerid,
        zone
    };
    return native(&::fakeAmx, params) != 0;
}

bool GangZoneStopFlashForAll(int zone) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("GangZoneStopFlashForAll");
    cell params[] = {
        1 * 4,
        zone
    };
    return native(&::fakeAmx, params) != 0;
}

int Create3DTextLabel(const std::string &text, long color, float x, float y, float z, float DrawDistance, long virtualworld, bool testLOS) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Create3DTextLabel");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        8 * 4,
        reinterpret_cast<cell>(text_.c_str()),
        color,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(DrawDistance),
        virtualworld,
        testLOS
    };
    return native(&::fakeAmx, params);
}

bool Delete3DTextLabel(int id) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Delete3DTextLabel");
    cell params[] = {
        1 * 4,
        id
    };
    return native(&::fakeAmx, params) != 0;
}

bool Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Attach3DTextLabelToPlayer");
    cell params[] = {
        5 * 4,
        id,
        playerid,
        amx_ftoc(OffsetX),
        amx_ftoc(OffsetY),
        amx_ftoc(OffsetZ)
    };
    return native(&::fakeAmx, params) != 0;
}

bool Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Attach3DTextLabelToVehicle");
    cell params[] = {
        5 * 4,
        id,
        vehicleid,
        amx_ftoc(OffsetX),
        amx_ftoc(OffsetY),
        amx_ftoc(OffsetZ)
    };
    return native(&::fakeAmx, params) != 0;
}

bool Update3DTextLabelText(int id, long color, const std::string &text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("Update3DTextLabelText");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        3 * 4,
        id,
        color,
        reinterpret_cast<cell>(text_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

int CreatePlayer3DTextLabel(int playerid, const std::string &text, long color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("CreatePlayer3DTextLabel");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        10 * 4,
        playerid,
        reinterpret_cast<cell>(text_.c_str()),
        color,
        amx_ftoc(x),
        amx_ftoc(y),
        amx_ftoc(z),
        amx_ftoc(DrawDistance),
        attachedplayer,
        attachedvehicle,
        testLOS
    };
    return native(&::fakeAmx, params);
}

bool DeletePlayer3DTextLabel(int playerid, int id) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("DeletePlayer3DTextLabel");
    cell params[] = {
        2 * 4,
        playerid,
        id
    };
    return native(&::fakeAmx, params) != 0;
}

bool UpdatePlayer3DTextLabelText(int playerid, int id, long color, const std::string &text) {
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("UpdatePlayer3DTextLabelText");
    cstring text_(text.begin(), text.end());
    cell params[] = {
        4 * 4,
        playerid,
        id,
        color,
        reinterpret_cast<cell>(text_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

bool ShowPlayerDialog(int playerid, int dialogid, int style, const std::string &caption, 
    const std::string &info, const std::string &button1, const std::string &button2)
{
    static AMX_NATIVE native = Wrapper::GetInstance()->GetNative("ShowPlayerDialog");
    cstring caption_(caption.begin(), caption.end());
    cstring info_(info.begin(), info.end());
    cstring button1_(button1.begin(), button1.end());
    cstring button2_(button2.begin(), button2.end());
    cell params[] = {
        7 * 4,
        playerid,
        dialogid,
        style,
        reinterpret_cast<cell>(caption_.c_str()),
        reinterpret_cast<cell>(info_.c_str()),
        reinterpret_cast<cell>(button1_.c_str()),
        reinterpret_cast<cell>(button2_.c_str())
    };
    return native(&::fakeAmx, params) != 0;
}

} // namespace samp

