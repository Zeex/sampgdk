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

#ifndef SAMPGDK_PLAYERS_H
#define SAMPGDK_PLAYERS_H

#include <sampgdk/config.h>

namespace sampgdk {

const int SPECIAL_ACTION_NONE = 0;
const int SPECIAL_ACTION_DUCK = 1;
const int SPECIAL_ACTION_USEJETPACK = 2;
const int SPECIAL_ACTION_ENTER_VEHICLE = 3;
const int SPECIAL_ACTION_EXIT_VEHICLE = 4;
const int SPECIAL_ACTION_DANCE1 = 5;
const int SPECIAL_ACTION_DANCE2 = 6;
const int SPECIAL_ACTION_DANCE3 = 7;
const int SPECIAL_ACTION_DANCE4 = 8;
const int SPECIAL_ACTION_HANDSUP = 10;
const int SPECIAL_ACTION_USECELLPHONE = 11;
const int SPECIAL_ACTION_SITTING = 12;
const int SPECIAL_ACTION_STOPUSECELLPHONE = 13;
const int SPECIAL_ACTION_DRINK_BEER = 20;
const int SPECIAL_ACTION_SMOKE_CIGGY = 21;
const int SPECIAL_ACTION_DRINK_WINE = 22;
const int SPECIAL_ACTION_DRINK_SPRUNK = 23;

const int FIGHT_STYLE_NORMAL = 4;
const int FIGHT_STYLE_BOXING = 5;
const int FIGHT_STYLE_KUNGFU = 6;
const int FIGHT_STYLE_KNEEHEAD = 7;
const int FIGHT_STYLE_GRABKICK = 15;
const int FIGHT_STYLE_ELBOW = 16;

const int WEAPONSKILL_PISTOL = 0;
const int WEAPONSKILL_PISTOL_SILENCED = 1;
const int WEAPONSKILL_DESERT_EAGLE = 2;
const int WEAPONSKILL_SHOTGUN = 3;
const int WEAPONSKILL_SAWNOFF_SHOTGUN = 4;
const int WEAPONSKILL_SPAS12_SHOTGUN = 5;
const int WEAPONSKILL_MICRO_UZI = 6;
const int WEAPONSKILL_MP5 = 7;
const int WEAPONSKILL_AK47 = 8;
const int WEAPONSKILL_M4 = 9;
const int WEAPONSKILL_SNIPERRIFLE = 10;

const int WEAPONSTATE_UNKNOWN = -1;
const int WEAPONSTATE_NO_BULLETS = 0;
const int WEAPONSTATE_LAST_BULLET = 1;
const int WEAPONSTATE_MORE_BULLETS = 2;
const int WEAPONSTATE_RELOADING = 3;

// Player
bool SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
bool SpawnPlayer(int playerid);

// Player info
bool SetPlayerPos(int playerid, float x, float y, float z);
bool SetPlayerPosFindZ(int playerid, float x, float y, float z);
bool GetPlayerPos(int playerid, float &x, float &y, float &z);
bool SetPlayerFacingAngle(int playerid, float angle);
bool GetPlayerFacingAngle(int playerid, float &angle);
bool IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z);
float GetPlayerDistanceFromPoint(int playerid, float x, float y, float z);
bool IsPlayerStreamedIn(int playerid, int forplayerid);
bool SetPlayerInterior(int playerid, int interiorid);
int GetPlayerInterior(int playerid);
bool SetPlayerHealth(int playerid, float health);
bool GetPlayerHealth(int playerid, float &health);
bool SetPlayerArmour(int playerid, float armour);
bool GetPlayerArmour(int playerid, float &armour);
bool SetPlayerAmmo(int playerid, int weaponslot, int ammo);
int GetPlayerAmmo(int playerid);
int GetPlayerWeaponState(int playerid);
int GetPlayerTargetPlayer(int playerid);
bool SetPlayerTeam(int playerid, int teamid);
int GetPlayerTeam(int playerid);
bool SetPlayerScore(int playerid, long score);
long GetPlayerScore(int playerid);
int GetPlayerDrunkLevel(int playerid);
bool SetPlayerDrunkLevel(int playerid, int level);
bool SetPlayerColor(int playerid, long color);
long GetPlayerColor(int playerid);
bool SetPlayerSkin(int playerid, int skinid);
int GetPlayerSkin(int playerid);
bool GivePlayerWeapon(int playerid, int weaponid, int ammo);
bool ResetPlayerWeapons(int playerid);
bool SetPlayerArmedWeapon(int playerid, int weaponid);
bool GetPlayerWeaponData(int playerid, int slot, int &weapon, int &ammo);
bool GivePlayerMoney(int playerid, long money);
bool ResetPlayerMoney(int playerid);
int SetPlayerName(int playerid, const char *name);
long GetPlayerMoney(int playerid);
int GetPlayerState(int playerid);
bool GetPlayerIp(int playerid, char *ip, size_t size);
int GetPlayerPing(int playerid);
int GetPlayerWeapon(int playerid);
bool GetPlayerKeys(int playerid, int &keys, int &updown, int &leftright);
bool GetPlayerName(int playerid, char *name, size_t size);
bool SetPlayerTime(int playerid, int hour, int minute);
bool GetPlayerTime(int playerid, int &hour, int &minute);
bool TogglePlayerClock(int playerid, bool toggle);
bool SetPlayerWeather(int playerid, int weather);
bool ForceClassSelection(int playerid);
bool SetPlayerWantedLevel(int playerid, int level);
int GetPlayerWantedLevel(int playerid);
bool SetPlayerFightingStyle(int playerid, int style);
int GetPlayerFightingStyle(int playerid);
bool SetPlayerVelocity(int playerid, float x, float y, float z);
bool GetPlayerVelocity( int playerid, float &x, float &y, float &z);
bool PlayCrimeReportForPlayer(int playerid, int suspectid, int crime);
bool PlayAudioStreamForPlayer(int playerid, const char *url, float posX = 0.0, float posY = 0.0, float posZ = 0.0, float distance = 50.0, bool usepos = false);
bool StopAudioStreamForPlayer(int playerid);

bool SetPlayerShopName(int playerid, const char *shopname);
bool SetPlayerSkillLevel(int playerid, int skill, int level);
int GetPlayerSurfingVehicleID(int playerid);
int GetPlayerSurfingObjectID(int playerid);
bool RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius);

// Attached to bone objects

const int MAX_PLAYER_ATTACHED_OBJECTS = 10; // This is the number of attached indexes available ie 5 = 0-4

bool SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX = 0.0, float fOffsetY = 0.0, float fOffsetZ = 0.0, float fRotX = 0.0, float fRotY = 0.0, float fRotZ = 0.0, float fScaleX = 1.0, float fScaleY = 1.0, float fScaleZ = 1.0);
bool RemovePlayerAttachedObject(int playerid, int index);
bool IsPlayerAttachedObjectSlotUsed(int playerid, int index);

// Per-player variable system (PVars)
bool SetPVarInt(int playerid, const char *varname, int value);
int GetPVarInt(int playerid, const char *varname);
bool SetPVarString(int playerid, const char *varname, const char *value);
bool GetPVarString(int playerid, const char *varname, char *value, size_t size);
bool SetPVarFloat(int playerid, const char *varname, float value);
float GetPVarFloat(int playerid, const char *varname);
bool DeletePVar(int playerid, const char *varname);

// PVar enumeration
const int PLAYER_VARTYPE_NONE = 0;
const int PLAYER_VARTYPE_INT = 1;
const int PLAYER_VARTYPE_STRING = 2;
const int PLAYER_VARTYPE_FLOAT = 3;

int GetPVarsUpperIndex(int playerid);
bool GetPVarNameAtIndex(int playerid, int index, char *varname, size_t size);
int GetPVarType(int playerid, const char *varname);

const int MAX_CHATBUBBLE_LENGTH = 144;
bool SetPlayerChatBubble(int playerid, const char *text, long color, float drawdistance, long expiretime);

// Player controls
bool PutPlayerInVehicle(int playerid, int vehicleid, int seatid);
int GetPlayerVehicleID(int playerid);
int GetPlayerVehicleSeat(int playerid);
bool RemovePlayerFromVehicle(int playerid);
bool TogglePlayerControllable(int playerid, bool toggle);
bool PlayerPlaySound(int playerid, int soundid, float x, float y, float z);
bool ApplyAnimation(int playerid, const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, long time, bool forcesync = false);
bool ClearAnimations(int playerid, bool forcesync = false);
int GetPlayerAnimationIndex(int playerid); // return the index of any running applied animations (0 if none are running)
bool GetAnimationName(int index, char *animlib, size_t animlib_size, char *animname, size_t animname_size); // get the animation lib/name for the index
int GetPlayerSpecialAction(int playerid);
bool SetPlayerSpecialAction(int playerid, int actionid);

// Player world/map related
bool SetPlayerCheckpoint(int playerid, float x, float y, float z, float size);
bool DisablePlayerCheckpoint(int playerid);
bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size);
bool DisablePlayerRaceCheckpoint(int playerid);
bool SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min);
bool SetPlayerMarkerForPlayer(int playerid, int showplayerid, long color);
bool ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show);

const int MAPICON_LOCAL = 0; // displays in the player's local are
const int MAPICON_GLOBAL = 1; // displays always
const int MAPICON_LOCAL_CHECKPOINT = 2; // displays in the player's local area and has a checkpoint marker
const int MAPICON_GLOBAL_CHECKPOINT = 3; // displays always and has a checkpoint marker

bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, long color, int style = MAPICON_LOCAL);
bool RemovePlayerMapIcon(int playerid, int iconid);

bool AllowPlayerTeleport(int playerid, bool allow);

// Player camera
bool SetPlayerCameraPos(int playerid, float x, float y, float z);
bool SetPlayerCameraLookAt(int playerid, float x, float y, float z);
bool SetCameraBehindPlayer(int playerid);
bool GetPlayerCameraPos(int playerid, float &x, float &y, float &z);
bool GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z);
int GetPlayerCameraMode(int playerid);

// Player conditionals
bool IsPlayerConnected(int playerid);
bool IsPlayerInVehicle(int playerid, int vehicleid);
bool IsPlayerInAnyVehicle(int playerid);
bool IsPlayerInCheckpoint(int playerid);
bool IsPlayerInRaceCheckpoint(int playerid);

// Virtual Worlds
bool SetPlayerVirtualWorld(int playerid, long worldid);
long GetPlayerVirtualWorld(int playerid);

// Insane Stunts
bool EnableStuntBonusForPlayer(int playerid, bool enable);
void EnableStuntBonusForAll(bool enable);

// Spectating
const int SPECTATE_MODE_NORMAL = 1;
const int SPECTATE_MODE_FIXED = 2;
const int SPECTATE_MODE_SIDE = 3;

bool TogglePlayerSpectating(int playerid, bool toggle);
bool PlayerSpectatePlayer(int playerid, int targetplayerid, int mode = SPECTATE_MODE_NORMAL);
bool PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode = SPECTATE_MODE_NORMAL);

// Recording for NPC playback
const int PLAYER_RECORDING_TYPE_NONE = 0;
const int PLAYER_RECORDING_TYPE_DRIVER = 1;
const int PLAYER_RECORDING_TYPE_ONFOOT = 2;

bool StartRecordingPlayerData(int playerid, int recordtype, const char *recordname);
bool StopRecordingPlayerData(int playerid);

// Convenience templates for some functions (to avoid specifying output buffer size explicitly
// when it's known at compile time (i.e. fixed-size buffers))
template<size_t N> bool GetPlayerName(int playerid, char (&name)[N]) { 
	return GetPlayerName(playerid, name, N); 
}
template<size_t N> bool GetPlayerIp(int playerid, char (&ip)[N]) { 
	return GetPlayerIp(playerid, ip, N); 
}
template<size_t N> bool GetPVarString(int playerid, const char *varname, char (&value)[N]) {
	return GetPVarString(playerid, varname, value, N);
}
template<size_t N> bool GetPVarNameAtIndex(int playerid, int index, char (&varname)[N]) {
	return GetPVarNameAtIndex(playerid, index, varname, N);
}
template<size_t N1, size_t N2> bool GetAnimationName(int index, char (&animlib)[N1], char (&animname)[N2]) {
	return GetAnimationName(index, animlib, N1, animname, N2);
}

} // namespace sampgdk

#endif

