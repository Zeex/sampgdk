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

#include <sampgdk/config.h>
#include <sampgdk/export.h>

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
SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessage(int playerid, long color, const char *message);
SAMPGDK_EXPORT void SAMPGDK_CALL SendClientMessageToAll(long color, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToPlayer(int playerid, int senderid, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToAll(int senderid, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendDeathMessage(int killer, int killee, int weapon);
SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForAll(const char *text, long time, int style);
SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForPlayer(int playerid, const char *text, long time, int style);
SAMPGDK_EXPORT long SAMPGDK_CALL GetTickCount();
SAMPGDK_EXPORT int SAMPGDK_CALL GetMaxPlayers();

// Game
SAMPGDK_EXPORT void SAMPGDK_CALL SetGameModeText(const char *text);
SAMPGDK_EXPORT void SAMPGDK_CALL SetTeamCount(long count);
SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, long color1, long color2);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, long color1, long color2, long respawn_delay);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld = 0);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePickup(int model, int type, float x, float y, float z, long virtualworld = 0);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPickup(int pickup);
SAMPGDK_EXPORT void SAMPGDK_CALL ShowNameTags(bool show);
SAMPGDK_EXPORT void SAMPGDK_CALL ShowPlayerMarkers(bool mode);
SAMPGDK_EXPORT void SAMPGDK_CALL GameModeExit();
SAMPGDK_EXPORT bool SAMPGDK_CALL SetWorldTime(short hour);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetWeaponName(int weaponid, char *name, size_t size);
SAMPGDK_EXPORT void SAMPGDK_CALL EnableTirePopping(bool enable);
SAMPGDK_EXPORT void SAMPGDK_CALL AllowInteriorWeapons(bool allow);
SAMPGDK_EXPORT void SAMPGDK_CALL SetWeather(int weatherid);
SAMPGDK_EXPORT void SAMPGDK_CALL SetGravity(float gravity);
SAMPGDK_EXPORT void SAMPGDK_CALL AllowAdminTeleport(bool allow);
SAMPGDK_EXPORT void SAMPGDK_CALL SetDeathDropAmount(long amount);
SAMPGDK_EXPORT void SAMPGDK_CALL CreateExplosion(float x, float y, float z, short type, float radius);
SAMPGDK_EXPORT void SAMPGDK_CALL EnableZoneNames(bool enable);
SAMPGDK_EXPORT void SAMPGDK_CALL UsePlayerPedAnims();        // Will cause the players to use CJ running/walking animations
SAMPGDK_EXPORT void SAMPGDK_CALL DisableInteriorEnterExits();  // will disable all interior enter/exits in the game.
SAMPGDK_EXPORT void SAMPGDK_CALL SetNameTagDrawDistance(float distance); // Distance at which nametags will start rendering on the client.
SAMPGDK_EXPORT void SAMPGDK_CALL DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking
SAMPGDK_EXPORT void SAMPGDK_CALL LimitGlobalChatRadius(float chat_radius);
SAMPGDK_EXPORT void SAMPGDK_CALL LimitPlayerMarkerRadius(float marker_radius);

// Npc
SAMPGDK_EXPORT bool SAMPGDK_CALL ConnectNPC(const char *name, const char *script);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerNPC(int playerid);

// Admin
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAdmin(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL Kick(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL Ban(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL BanEx(int playerid, const char *reason);
SAMPGDK_EXPORT void SAMPGDK_CALL SendRconCommand(const char *command);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsString(const char *varname, char *value, size_t size);
SAMPGDK_EXPORT int SAMPGDK_CALL GetServerVarAsInt(const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsBool(const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerNetworkStats(int playerid, char *retstr, size_t size);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetNetworkStats(char *retstr, size_t size);

// Menu
SAMPGDK_EXPORT int SAMPGDK_CALL CreateMenu(const char *title, int columns, float x, float y, float col1width, float col2width = 0.0f);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyMenu(int menuid);
SAMPGDK_EXPORT int SAMPGDK_CALL AddMenuItem(int menuid, int column, const char *menutext);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetMenuColumnHeader(int menuid, int column, const char *columnheader);
SAMPGDK_EXPORT bool SAMPGDK_CALL ShowMenuForPlayer(int menuid, int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL HideMenuForPlayer(int menuid, int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidMenu(int menuid);
SAMPGDK_EXPORT bool SAMPGDK_CALL DisableMenu(int menuid);
SAMPGDK_EXPORT bool SAMPGDK_CALL DisableMenuRow(int menuid, int row);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerMenu(int playerid);

// Text Draw
SAMPGDK_EXPORT int SAMPGDK_CALL TextDrawCreate(float x, float y, const char *text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawDestroy(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawLetterSize(int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawTextSize(int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawAlignment(int text, int alignment);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawColor(int text, long color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawUseBox(int text, bool use);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBoxColor(int text, long color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetShadow(int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetOutline(int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBackgroundColor(int text, long color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawFont(int text, int font);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetProportional(int text, bool set);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForPlayer(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForPlayer(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForAll(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForAll(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetString(int text, const char *string);

// Gang Zones
SAMPGDK_EXPORT int SAMPGDK_CALL GangZoneCreate(float minx, float miny, float maxx, float maxy);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneDestroy(int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForPlayer(int playerid, int zone, long color);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForAll(int zone, long color);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForPlayer(int playerid, int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForAll(int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForPlayer(int playerid, int zone, long flashcolor);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForAll(int zone, long flashcolor);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForPlayer(int playerid, int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForAll(int zone);

// Global 3D Text Labels
SAMPGDK_EXPORT int SAMPGDK_CALL Create3DTextLabel(const char *text, long color, float x, float y, float z, float DrawDistance, long virtualworld, bool testLOS = false);
SAMPGDK_EXPORT bool SAMPGDK_CALL Delete3DTextLabel(int id);
SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL Update3DTextLabelText(int id, long color, const char *text);

// Per-player 3D Text Labels
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayer3DTextLabel(int playerid, const char *text, long color, float x, float y, float z, float DrawDistance, int attachedplayer = INVALID_PLAYER_ID, int attachedvehicle = INVALID_VEHICLE_ID, bool testLOS = false);
SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePlayer3DTextLabel(int playerid, int id);
SAMPGDK_EXPORT bool SAMPGDK_CALL UpdatePlayer3DTextLabelText(int playerid, int id, long color, const char *text);

// Player GUI Dialog
const int DIALOG_STYLE_MSGBOX = 0;
const int DIALOG_STYLE_INPUT = 1;
const int DIALOG_STYLE_LIST = 2;

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption, const char *info, const char *button1, const char *button2);

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

// Marker modes used SAMPGDK_EXPORT by SAMPGDK_CALL ShowPlayerMarkers()
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

template<size_t N> inline bool GetNetworkStats(char (&retstr)[N]) { 
	return GetNetworkStats(retstr, N); 
}

template<size_t N> inline bool GetPlayerNetworkStats(int playerid, char (&retstr)[N]) { 
	return GetPlayerNetworkStats(playerid, retstr, N); 
}

template<size_t N> inline bool GetWeaponName(int weaponid, char (&name)[N]) {
	return GetWeaponName(weaponid, name, N);
}

#endif // SAMPGDK_SAMP_H
