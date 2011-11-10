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

#ifndef SAMPGDK_SAMP_H
#define SAMPGDK_SAMP_H

#include <sampgdk.h>

namespace sampgdk {

// Limits and internal constants
const int MAX_PLAYER_NAME = 24;
const int MAX_PLAYERS = 500;
const int MAX_VEHICLES = 2000;
const int INVALID_PLAYER_ID = 0xFFFF;
const int INVALID_VEHICLE_ID = 0xFFFF;
const int NO_TEAM = 255;
const int MAX_OBJECTS = 1000;
const int INVALID_OBJECT_ID = 0xFFFF;
const int MAX_GANG_ZONES = 1024;
const int MAX_TEXT_DRAWS = 2048;
const int MAX_MENUS = 128;
const int MAX_3DTEXT_GLOBAL = 1024;
const int MAX_3DTEXT_PLAYER = 1024;
const int MAX_PICKUPS = 4096;
const int INVALID_MENU = 0xFF;
const int INVALID_TEXT_DRAW = 0xFFFF;
const int INVALID_GANG_ZONE = -1;
const int INVALID_3DTEXT_ID = 0xFFFF;

// Util
bool SendClientMessage(int playerid, long color, const char *message);
void SendClientMessageToAll(long color, const char *message);
bool SendPlayerMessageToPlayer(int playerid, int senderid, const char *message);
bool SendPlayerMessageToAll(int senderid, const char *message);
bool SendDeathMessage(int killer, int killee, int weapon);
bool GameTextForAll(const char *text, long time, int style);
bool GameTextForPlayer(int playerid, const char *text, long time, int style);
long GetTickCount();
int GetMaxPlayers();

// Game
void SetGameModeText(const char *text);
void SetTeamCount(long count);
int AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
int AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
int AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2);
int AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay);
int AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld = 0);
int CreatePickup(int model, int type, float x, float y, float z, long virtualworld = 0);
bool DestroyPickup(int pickup);
void ShowNameTags(bool show);
void ShowPlayerMarkers(bool mode);
void GameModeExit();
bool SetWorldTime(short hour);
bool GetWeaponName(int weaponid, char *name, size_t size);
void EnableTirePopping(bool enable);
void AllowInteriorWeapons(bool allow);
void SetWeather(int weatherid);
void SetGravity(float gravity);
void AllowAdminTeleport(bool allow);
void SetDeathDropAmount(long amount);
void CreateExplosion(float x, float y, float z, short type, float radius);
void EnableZoneNames(bool enable);
void UsePlayerPedAnims();        // Will cause the players to use CJ running/walking animations
void DisableInteriorEnterExits();  // will disable all interior enter/exits in the game.
void SetNameTagDrawDistance(float distance); // Distance at which nametags will start rendering on the client.
void DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking
void LimitGlobalChatRadius(float chat_radius);
void LimitPlayerMarkerRadius(float marker_radius);

// Npc
bool ConnectNPC(const char *name, const char *script);
bool IsPlayerNPC(int playerid);

// Admin
bool IsPlayerAdmin(int playerid);
bool Kick(int playerid);
bool Ban(int playerid);
bool BanEx(int playerid, const char *reason);
void SendRconCommand(const char *command);
bool GetServerVarAsString(const char *varname, char *value, size_t size);
int GetServerVarAsInt(const char *varname);
bool GetServerVarAsBool(const char *varname);
bool GetPlayerNetworkStats(int playerid, char *retstr, size_t size);
bool GetPlayerNetworkStats(int playerid, char (&retstr)[401]);
bool GetNetworkStats(char *retstr, size_t size);
bool GetNetworkStats(char (&retstr)[401]);

// Menu
int CreateMenu(const char *title, int columns, float x, float y, float col1width, float col2width = 0.0f);
bool DestroyMenu(int menuid);
int AddMenuItem(int menuid, int column, const char *menutext);
bool SetMenuColumnHeader(int menuid, int column, const char *columnheader);
bool ShowMenuForPlayer(int menuid, int playerid);
bool HideMenuForPlayer(int menuid, int playerid);
bool IsValidMenu(int menuid);
bool DisableMenu(int menuid);
bool DisableMenuRow(int menuid, int row);
int GetPlayerMenu(int playerid);

// Text Draw
int TextDrawCreate(float x, float y, const char *text);
bool TextDrawDestroy(int text);
bool TextDrawLetterSize(int text, float x, float y);
bool TextDrawTextSize(int text, float x, float y);
bool TextDrawAlignment(int text, int alignment);
bool TextDrawColor(int text, long color);
bool TextDrawUseBox(int text, bool use);
bool TextDrawBoxColor(int text, long color);
bool TextDrawSetShadow(int text, int size);
bool TextDrawSetOutline(int text, int size);
bool TextDrawBackgroundColor(int text, long color);
bool TextDrawFont(int text, int font);
bool TextDrawSetProportional(int text, bool set);
bool TextDrawShowForPlayer(int playerid, int text);
bool TextDrawHideForPlayer(int playerid, int text);
bool TextDrawShowForAll(int text);
bool TextDrawHideForAll(int text);
bool TextDrawSetString(int text, const char *string);

// Gang Zones
int GangZoneCreate(float minx, float miny, float maxx, float maxy);
bool GangZoneDestroy(int zone);
bool GangZoneShowForPlayer(int playerid, int zone, long color);
bool GangZoneShowForAll(int zone, long color);
bool GangZoneHideForPlayer(int playerid, int zone);
bool GangZoneHideForAll(int zone);
bool GangZoneFlashForPlayer(int playerid, int zone, long flashcolor);
bool GangZoneFlashForAll(int zone, long flashcolor);
bool GangZoneStopFlashForPlayer(int playerid, int zone);
bool GangZoneStopFlashForAll(int zone);

// Global 3D Text Labels
int Create3DTextLabel(const char *text, long color, float x, float y, float z, float DrawDistance, long virtualworld, bool testLOS = false);
bool Delete3DTextLabel(int id);
bool Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ);
bool Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ);
bool Update3DTextLabelText(int id, long color, const char *text);

// Per-player 3D Text Labels
int CreatePlayer3DTextLabel(int playerid, const char *text, long color, float x, float y, float z, float DrawDistance, int attachedplayer = INVALID_PLAYER_ID, int attachedvehicle = INVALID_VEHICLE_ID, bool testLOS = false);
bool DeletePlayer3DTextLabel(int playerid, int id);
bool UpdatePlayer3DTextLabelText(int playerid, int id, long color, const char *text);

// Player GUI Dialog
const int DIALOG_STYLE_MSGBOX = 0;
const int DIALOG_STYLE_INPUT = 1;
const int DIALOG_STYLE_LIST = 2;

bool ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption, const char *info, const char *button1, const char *button2);

// States
const int PLAYER_STATE_NONE = 0;
const int PLAYER_STATE_ONFOOT = 1;
const int PLAYER_STATE_DRIVER = 2;
const int PLAYER_STATE_PASSENGER = 3;
const int PLAYER_STATE_EXIT_VEHICLE = 4; 
const int PLAYER_STATE_ENTER_VEHICLE_DRIVER = 5; 
const int PLAYER_STATE_ENTER_VEHICLE_PASSENGER = 6; 
const int PLAYER_STATE_WASTED = 7;
const int PLAYER_STATE_SPAWNED = 8;
const int PLAYER_STATE_SPECTATING = 9;

// Marker modes used by ShowPlayerMarkers()
const int PLAYER_MARKERS_MODE_OFF = 0;
const int PLAYER_MARKERS_MODE_GLOBAL = 1;
const int PLAYER_MARKERS_MODE_STREAMED = 2;

// Weapons
const int WEAPON_BRASSKNUCKLE = 1;
const int WEAPON_GOLFCLUB = 2;
const int WEAPON_NITESTICK = 3;
const int WEAPON_KNIFE = 4;
const int WEAPON_BAT = 5;
const int WEAPON_SHOVEL = 6;
const int WEAPON_POOLSTICK = 7;
const int WEAPON_KATANA = 8;
const int WEAPON_CHAINSAW = 9;
const int WEAPON_DILDO = 10;
const int WEAPON_DILDO2 = 11;
const int WEAPON_VIBRATOR = 12;
const int WEAPON_VIBRATOR2 = 13;
const int WEAPON_FLOWER = 14;
const int WEAPON_CANE = 15;
const int WEAPON_GRENADE = 16;
const int WEAPON_TEARGAS = 17;
const int WEAPON_MOLTOV = 18;
const int WEAPON_COLT45 = 22;
const int WEAPON_SILENCED = 23;
const int WEAPON_DEAGLE = 24;
const int WEAPON_SHOTGUN = 25;
const int WEAPON_SAWEDOFF = 26;
const int WEAPON_SHOTGSPA = 27;
const int WEAPON_UZI = 28;
const int WEAPON_MP5 = 29;
const int WEAPON_AK47 = 30;
const int WEAPON_M4 = 31;
const int WEAPON_TEC9 = 32;
const int WEAPON_RIFLE = 33;
const int WEAPON_SNIPER = 34;
const int WEAPON_ROCKETLAUNCHER = 35;
const int WEAPON_HEATSEEKER = 36;
const int WEAPON_FLAMETHROWER = 37;
const int WEAPON_MINIGUN = 38;
const int WEAPON_SATCHEL = 39;
const int WEAPON_BOMB = 40;
const int WEAPON_SPRAYCAN = 41;
const int WEAPON_FIREEXTINGUISHER = 42;
const int WEAPON_CAMERA = 43;
const int WEAPON_PARACHUTE = 46;
const int WEAPON_VEHICLE = 49;
const int WEAPON_DROWN = 53;
const int WEAPON_COLLISION = 54;

// Keys
const int KEY_ACTION = 1;
const int KEY_CROUCH = 2;
const int KEY_FIRE = 4;
const int KEY_SPRINT = 8;
const int KEY_SECONDARY_ATTACK = 16;
const int KEY_JUMP = 32;
const int KEY_LOOK_RIGHT = 64;
const int KEY_HANDBRAKE = 128;
const int KEY_LOOK_LEFT = 256;
const int KEY_SUBMISSION = 512;
const int KEY_LOOK_BEHIND = 512;
const int KEY_WALK = 1024;
const int KEY_ANALOG_UP = 2048;
const int KEY_ANALOG_DOWN = 4096;
const int KEY_ANALOG_LEFT = 8192;
const int KEY_ANALOG_RIGHT = 16384;

const int KEY_YES = 65536;
const int KEY_NO = 131072;
const int KEY_CTRL_BACK = 262144;

const int KEY_UP = -128;
const int KEY_DOWN = 128;
const int KEY_LEFT = -128;
const int KEY_RIGHT = 128;

const int CLICK_SOURCE_SCOREBOARD = 0;

// Convenience templates for some functions (to avoid specifying output buffer size explicitly
// when it's known at compile time (i.e. fixed-size buffers))

template<size_t N> bool GetNetworkStats(char (&retstr)[N]) { 
	return GetNetworkStats(retstr, N); 
}

template<size_t N> bool GetPlayerNetworkStats(int playerid, char (&retstr)[N]) { 
	return GetPlayerNetworkStats(playerid, retstr, N); 
}

template<size_t N> bool GetWeaponName(int weaponid, char (&name)[N]) {
	return GetWeaponName(weaponid, name, N);
}

} // namespace sampgdk

#endif

