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

#ifndef SAMP_PLAYERS_H
#define SAMP_PLAYERS_H

namespace sampgdk {

#define SPECIAL_ACTION_NONE              0
#define SPECIAL_ACTION_DUCK              1
#define SPECIAL_ACTION_USEJETPACK        2
#define SPECIAL_ACTION_ENTER_VEHICLE     3
#define SPECIAL_ACTION_EXIT_VEHICLE      4
#define SPECIAL_ACTION_DANCE1            5
#define SPECIAL_ACTION_DANCE2            6
#define SPECIAL_ACTION_DANCE3            7
#define SPECIAL_ACTION_DANCE4            8
#define SPECIAL_ACTION_HANDSUP           10
#define SPECIAL_ACTION_USECELLPHONE      11
#define SPECIAL_ACTION_SITTING           12
#define SPECIAL_ACTION_STOPUSECELLPHONE  13
#define SPECIAL_ACTION_DRINK_BEER        20
#define SPECIAL_ACTION_SMOKE_CIGGY       21
#define SPECIAL_ACTION_DRINK_WINE        22
#define SPECIAL_ACTION_DRINK_SPRUNK      23

#define FIGHT_STYLE_NORMAL               4
#define FIGHT_STYLE_BOXING               5
#define FIGHT_STYLE_KUNGFU               6
#define FIGHT_STYLE_KNEEHEAD             7
#define FIGHT_STYLE_GRABKICK             15
#define FIGHT_STYLE_ELBOW                16

#define WEAPONSKILL_PISTOL                0
#define WEAPONSKILL_PISTOL_SILENCED       1
#define WEAPONSKILL_DESERT_EAGLE          2
#define WEAPONSKILL_SHOTGUN               3
#define WEAPONSKILL_SAWNOFF_SHOTGUN       4
#define WEAPONSKILL_SPAS12_SHOTGUN        5
#define WEAPONSKILL_MICRO_UZI             6
#define WEAPONSKILL_MP5                   7
#define WEAPONSKILL_AK47                  8
#define WEAPONSKILL_M4                    9
#define WEAPONSKILL_SNIPERRIFLE           10

#define WEAPONSTATE_UNKNOWN              -1
#define WEAPONSTATE_NO_BULLETS            0
#define WEAPONSTATE_LAST_BULLET           1
#define WEAPONSTATE_MORE_BULLETS          2
#define WEAPONSTATE_RELOADING             3

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
bool GetPlayerName(int playerid, char (&name)[MAX_PLAYER_NAME]);
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
bool SetPlayerShopName(int playerid, const char *shopname);
bool SetPlayerSkillLevel(int playerid, int skill, int level);
int GetPlayerSurfingVehicleID(int playerid);

// Attached to bone objects

#define MAX_PLAYER_ATTACHED_OBJECTS 5 // This is the number of attached indexes available ie 5 = 0-4

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
#define PLAYER_VARTYPE_NONE         0
#define PLAYER_VARTYPE_INT          1
#define PLAYER_VARTYPE_STRING       2
#define PLAYER_VARTYPE_FLOAT        3

int GetPVarsUpperIndex(int playerid);
bool GetPVarNameAtIndex(int playerid, int index, char *varname, size_t size);
int GetPVarType(int playerid, const char *varname);

#define MAX_CHATBUBBLE_LENGTH 144
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

#define MAPICON_LOCAL             0 // displays in the player's local are
#define MAPICON_GLOBAL            1 // displays always
#define MAPICON_LOCAL_CHECKPOINT  2 // displays in the player's local area and has a checkpoint marker
#define MAPICON_GLOBAL_CHECKPOINT 3 // displays always and has a checkpoint marker

bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, long color, int style = MAPICON_LOCAL);
bool RemovePlayerMapIcon(int playerid, int iconid);

bool AllowPlayerTeleport(int playerid, bool allow);

// Player camera
bool SetPlayerCameraPos(int playerid, float x, float y, float z);
bool SetPlayerCameraLookAt(int playerid, float x, float y, float z);
bool SetCameraBehindPlayer(int playerid);
bool GetPlayerCameraPos(int playerid, float &x, float &y, float &z);
bool GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z);

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
#define SPECTATE_MODE_NORMAL    1
#define SPECTATE_MODE_FIXED     2
#define SPECTATE_MODE_SIDE      3

bool TogglePlayerSpectating(int playerid, bool toggle);
bool PlayerSpectatePlayer(int playerid, int targetplayerid, int mode = SPECTATE_MODE_NORMAL);
bool PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode = SPECTATE_MODE_NORMAL);

// Recording for NPC playback
#define PLAYER_RECORDING_TYPE_NONE      0
#define PLAYER_RECORDING_TYPE_DRIVER    1
#define PLAYER_RECORDING_TYPE_ONFOOT    2

bool StartRecordingPlayerData(int playerid, int recordtype, const char *recordname);
bool StopRecordingPlayerData(int playerid);

} // namespace sampgdk

#endif

