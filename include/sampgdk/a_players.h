/* Copyright (C) 2011-2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_A_PLAYERS_H
#define SAMPGDK_A_PLAYERS_H

#include <sampgdk/a_samp.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/generated/a_players-defs.h>

#include <stddef.h>

#define SPECIAL_ACTION_NONE             (0)
#define SPECIAL_ACTION_DUCK             (1)
#define SPECIAL_ACTION_USEJETPACK       (2)
#define SPECIAL_ACTION_ENTER_VEHICLE    (3)
#define SPECIAL_ACTION_EXIT_VEHICLE     (4)
#define SPECIAL_ACTION_DANCE1           (5)
#define SPECIAL_ACTION_DANCE2           (6)
#define SPECIAL_ACTION_DANCE3           (7)
#define SPECIAL_ACTION_DANCE4           (8)
#define SPECIAL_ACTION_HANDSUP          (10)
#define SPECIAL_ACTION_USECELLPHONE     (11)
#define SPECIAL_ACTION_SITTING          (12)
#define SPECIAL_ACTION_STOPUSECELLPHONE (13)
#define SPECIAL_ACTION_DRINK_BEER       (20)
#define SPECIAL_ACTION_SMOKE_CIGGY      (21)
#define SPECIAL_ACTION_DRINK_WINE       (22)
#define SPECIAL_ACTION_DRINK_SPRUNK     (23)

#define FIGHT_STYLE_NORMAL    (4)
#define FIGHT_STYLE_BOXING    (5)
#define FIGHT_STYLE_KUNGFU    (6)
#define FIGHT_STYLE_KNEEHEAD  (7)
#define FIGHT_STYLE_GRABKICK  (15)
#define FIGHT_STYLE_ELBOW     (16)

#define WEAPONSKILL_PISTOL          (0)
#define WEAPONSKILL_PISTOL_SILENCED (1)
#define WEAPONSKILL_DESERT_EAGLE    (2)
#define WEAPONSKILL_SHOTGUN         (3)
#define WEAPONSKILL_SAWNOFF_SHOTGUN (4)
#define WEAPONSKILL_SPAS12_SHOTGUN  (5)
#define WEAPONSKILL_MICRO_UZI       (6)
#define WEAPONSKILL_MP5             (7)
#define WEAPONSKILL_AK47            (8)
#define WEAPONSKILL_M4              (9)
#define WEAPONSKILL_SNIPERRIFLE     (10)

#define WEAPONSTATE_UNKNOWN      (-1)
#define WEAPONSTATE_NO_BULLETS   (0)
#define WEAPONSTATE_LAST_BULLET  (1)
#define WEAPONSTATE_MORE_BULLETS (2)
#define WEAPONSTATE_RELOADING    (3)

SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));
SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid));

SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle));
SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float *angle));
SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z));
SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid));
SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid));
SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health));
SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float *health));
SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour));
SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float *armour));
SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponslot, int ammo));
SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid));
SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid));
SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid));
SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score));
SAMPGDK_NATIVE(int, GetPlayerScore(int playerid));
SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level));
SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color));
SAMPGDK_NATIVE(int, GetPlayerColor(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid));
SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid));
SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo));
SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid));
SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int *weapon, int *ammo));
SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money));
SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid));
SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char *name));
SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid));
SAMPGDK_NATIVE(int, GetPlayerState(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char *ip, int size));
SAMPGDK_NATIVE(int, GetPlayerPing(int playerid));
SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int *keys, int *updown, int *leftright));
SAMPGDK_NATIVE(bool, GetPlayerName(int playerid, char *name, int size));
SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute));
SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int *hour, int *minute));
SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather));
SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level));
SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style));
SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, GetPlayerVelocity( int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime));
SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char *url, float posX, float posY, float posZ, float distance, bool usepos));
SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char *shopname));
SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level));
SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid));
SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid));
SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius));

#define MAX_PLAYER_ATTACHED_OBJECTS (10)

SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2));
SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index));
SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index));
SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index));

SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char *text));
SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y));
SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y));
SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment));
SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use));
SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size));
SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color));
SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set));
SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text));
SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char *string));

#define PLAYER_VARTYPE_NONE   (0)
#define PLAYER_VARTYPE_INT    (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT  (3)

SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char *varname, int value));
SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char *varname));
SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char *varname, const char *value));
SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char *varname, char *value, int size));
SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char *varname, float value));
SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char *varname));
SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char *varname));

SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid));
SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char *varname, int size));
SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char *varname));

#define MAX_CHATBUBBLE_LENGTH (144)

SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char *text, int color, float drawdistance, int expiretime));

SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid));
SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid));
SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid));
SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid));
SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z));
SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync));
SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync));
SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid));
SAMPGDK_NATIVE(bool, GetAnimationName(int index, char *animlib, int animlib_size, char *animname, int animname_size));
SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid));

SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size));
SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size));
SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min));
SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color));
SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show));

#define MAPICON_LOCAL             (0)
#define MAPICON_GLOBAL            (1)
#define MAPICON_LOCAL_CHECKPOINT  (2)
#define MAPICON_GLOBAL_CHECKPOINT (3)

SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style));
SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid));

SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow));

#define CAMERA_CUT  2
#define CAMERA_MOVE 1

SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z));
SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut));
SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid));
SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float *x, float *y, float *z));
SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid));
SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid));
SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid));
SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));
SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid));
SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid));
SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid));

SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid));
SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid));

SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable));
SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable));

#define SPECTATE_MODE_NORMAL  (1)
#define SPECTATE_MODE_FIXED   (2)
#define SPECTATE_MODE_SIDE    (3)

SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle));
SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode));
SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode));

#define PLAYER_RECORDING_TYPE_NONE   (0)
#define PLAYER_RECORDING_TYPE_DRIVER (1)
#define PLAYER_RECORDING_TYPE_ONFOOT (2)

SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char *recordname));
SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid));

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>
#include <vector>

template<size_t N> inline bool GetPlayerName(int playerid, char (&name)[N]) {
	return GetPlayerName(playerid, name, N);
}
template<size_t N> inline bool GetPlayerIp(int playerid, char (&ip)[N]) {
	return GetPlayerIp(playerid, ip, N);
}
template<size_t N> inline bool GetPVarString(int playerid, const char *varname, char (&value)[N]) {
	return GetPVarString(playerid, varname, value, N);
}
template<size_t N> inline bool GetPVarNameAtIndex(int playerid, int index, char (&varname)[N]) {
	return GetPVarNameAtIndex(playerid, index, varname, N);
}
template<size_t N1, size_t N2> inline bool GetAnimationName(int index, char (&animlib)[N1], char (&animname)[N2]) {
	return GetAnimationName(index, animlib, N1, animname, N2);
}

class Player {
public:
	// Construct from a player ID
	Player(int playerid) : id_(playerid) { assert(id_ != INVALID_PLAYER_ID); }
	virtual ~Player() {}

	// Implicit conversion to 'int'
	operator int() const { return id_; }

	// Explicit ID request
	int GetId() const { return id_; }

	bool Spawn() const
		{ return ::SpawnPlayer(id_); }
	bool SetPos(float x, float y, float z) const
		{ return ::SetPlayerPos(id_, x, y, z); }
	bool SetPosFindZ(float x, float y, float z) const
		{ return ::SetPlayerPosFindZ(id_, x, y, z); }
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetPlayerPos(id_, x, y, z); }
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetPlayerPos(id_, &x, &y, &z); }
	bool SetFacingAngle(float angle) const
		{ return ::SetPlayerFacingAngle(id_, angle); }
	bool GetFacingAngle(float *angle) const
		{ return ::GetPlayerFacingAngle(id_, angle); }
	bool GetFacingAngle(float &angle) const
		{ return ::GetPlayerFacingAngle(id_, &angle); }
	bool IsInRangeOfPoint(float range, float x, float y, float z) const
		{ return ::IsPlayerInRangeOfPoint(id_, range, x, y, z); }
	float GetDistanceFromPoint(float x, float y, float z) const
		{ return ::GetPlayerDistanceFromPoint(id_, x, y, z); }
	bool IsStreamedInFor(int playerid) const
		{ return ::IsPlayerStreamedIn(id_, playerid); }
	bool SetInterior(int interiorid) const
		{ return ::SetPlayerInterior(id_, interiorid); }
	int GetInterior() const 
		{ return ::GetPlayerInterior(id_); }
	bool SetHealth(float health) const
		{ return ::SetPlayerHealth(id_, health); }
	float GetHealth() const { 
		float health; 
		::GetPlayerHealth(id_, &health); 
		return health;
	}
	bool SetArmour(float armour) const
		{ return ::SetPlayerArmour(id_, armour); }
	float GetArmour() const {
		float armour;
		::GetPlayerArmour(id_, &armour);
		return armour;
	}
	bool SetAmmo(int weaponslot, int ammo) const
		{ return ::SetPlayerAmmo(id_, weaponslot, ammo); }
	int GetAmmo() const
		{ return ::GetPlayerAmmo(id_); }
	int GetWeaponState() const
		{ return ::GetPlayerWeaponState(id_); }
	int GetTargetPlayer() const
		{ return ::GetPlayerTargetPlayer(id_); }
	bool SetPlayerTeam(int teamid) const
		{ return ::SetPlayerTeam(id_, teamid); }
	int GetPlayerTeam() const
		{ return ::GetPlayerTeam(id_); }
	bool SetScore(int score) const
		{ return ::SetPlayerScore(id_, score); }
	int GetScore() const 
		{ return ::GetPlayerScore(id_); }
	int GetDrunkLevel() const 
		{ return ::GetPlayerDrunkLevel(id_); }
	bool SetDrunkLevel(int level) const
		{ return ::SetPlayerDrunkLevel(id_, level); }
	bool SetColor(int color) const
		{ return ::SetPlayerColor(id_, color); }
	int GetColor() const
		{ return ::GetPlayerColor(id_); }
	bool SetSkin(int skinid) const
		{ return ::SetPlayerSkin(id_, skinid); }
	int GetSkin() const
		{ return ::GetPlayerSkin(id_); }
	bool GiveWeapon(int weaponid, int ammo) const
		{ return ::GivePlayerWeapon(id_, weaponid, ammo); }
	bool ResetWeapons() const
		{ return ::ResetPlayerWeapons(id_); }
	bool SetArmedWeapon(int weaponid) const
		{ return ::SetPlayerArmedWeapon(id_, weaponid); }
	bool GetWeaponData(int slot, int *weapon, int *ammo) const
		{ return ::GetPlayerWeaponData(id_, slot, weapon, ammo); }
	bool GetWeaponData(int slot, int &weapon, int &ammo) const
		{ return ::GetPlayerWeaponData(id_, slot, &weapon, &ammo); }
	bool GiveMoney(int money) const
		{ return ::GivePlayerMoney(id_, money); }
	bool ResetMoney() const
		{ return ::ResetPlayerMoney(id_); }
	bool SetName(const char *name) const
		{ return ::SetPlayerName(id_, name) > 0; }
	bool SetName(const std::string &name) const
		{ return ::SetPlayerName(id_, name.c_str()) > 0; }
	int GetMoney() const
		{ return ::GetPlayerMoney(id_); }
	int GetState() const
		{ return ::GetPlayerState(id_); }
	bool GetIp(char *ip, int size) const
		{ return ::GetPlayerIp(id_, ip, size); }
	int GetPing() const
		{ return ::GetPlayerPing(id_); }
	int GetWeapon() const
		{ return ::GetPlayerWeapon(id_); }
	bool GetKeys(int *keys, int *updown, int *leftright) const
		{ return ::GetPlayerKeys(id_, keys, updown, leftright); }
	bool GetKeys(int &keys, int &updown, int &leftright) const
		{ return ::GetPlayerKeys(id_, &keys, &updown, &leftright); }
	bool GetName(char *name, int size) const
		{ return ::GetPlayerName(id_, name, size); }
	std::string GetName() const {
		std::vector<char> name(MAX_PLAYER_NAME);
		::GetPlayerName(id_, &name[0], MAX_PLAYER_NAME);
		return std::string(&name[0]);
	}
	bool SetTime(int hour, int minute) const
		{ return ::SetPlayerTime(id_, hour, minute); }
	bool GetTime(int *hour, int *minute) const
		{ return ::GetPlayerTime(id_, hour, minute); }
	bool GetTime(int &hour, int &minute) const
		{ return ::GetPlayerTime(id_, &hour, &minute); }
	bool ToggleClock(bool toggle) const
		{ return ::TogglePlayerClock(id_, toggle); }
	bool SetWeather(int weather) const
		{ return ::SetPlayerWeather(id_, weather); }
	bool ForceClassSelection() const
		{ return ::ForceClassSelection(id_); }
	bool SetWantedLevel(int level) const
		{ return ::SetPlayerWantedLevel(id_, level); }
	int GetWantedLevel() const 
		{ return ::GetPlayerWantedLevel(id_); }
	bool SetFightingStyle(int style) const
		{ return ::SetPlayerFightingStyle(id_, style); }
	int GetFightingStyle() const
		{ return ::GetPlayerFightingStyle(id_); }
	bool SetVelocity(float x, float y, float z) const
		{ return ::SetPlayerVelocity(id_, x, y, z); }
	bool GetVelocity(float *x, float *y, float *z) const
		{ return ::GetPlayerVelocity(id_, x, y, z); }
	bool GetVelocity(float &x, float &y, float &z) const
		{ return ::GetPlayerVelocity(id_, &x, &y, &z); }
	float GetSpeed() const {
		float velX, velY, velZ;
		GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}
	bool PlayCrimeReport(int suspectid, int crime) const
		{ return ::PlayCrimeReportForPlayer(id_, suspectid, crime); }
	bool PlayAudioStream(const char *url, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float distance = 50.0f, bool usepos = false) const
		{ return ::PlayAudioStreamForPlayer(id_, url, posX, posY, posZ, distance, usepos); }
	bool PlayAudioStream(const std::string &url, float posX, float posY, float posZ, float distance, bool usepos) const
		{ return ::PlayAudioStreamForPlayer(id_, url.c_str(), posX, posY, posZ, distance, usepos); }
	bool StopAudioStream() const
		{ return ::StopAudioStreamForPlayer(id_); }
	bool SetShopName(const char *shopname) const
		{ return ::SetPlayerShopName(id_, shopname); }
	bool SetShopName(const std::string &shopname) const
		{ return ::SetPlayerShopName(id_, shopname.c_str()); }
	bool SetSkillLevel(int skill, int level) const
		{ return ::SetPlayerSkillLevel(id_, skill, level); }
	int GetSurfingVehicleID() const
		{ return ::GetPlayerSurfingVehicleID(id_); }
	int GetSurfingObjectID() const
		{ return ::GetPlayerSurfingObjectID(id_); }
	bool RemoveBuilding(int modelid, float fX, float fY, float fZ, float fRadius) const
		{ return ::RemoveBuildingForPlayer(id_, modelid, fX, fY, fZ, fRadius);	}

	bool SetAttachedObject(int index, int modelid, int bone, float fOffsetX = 0.0f, float fOffsetY = 0.0f, float fOffsetZ = 0.0f, 
		float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, float fScaleX = 1.0f, float fScaleY = 1.0f, float fScaleZ = 1.0f,
		int materialcolor1 = 0, int materialcolor2 = 0) const
	{ 
		::SetPlayerAttachedObject(id_, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2); 
	}
	bool RemoveAttachedObject(int index) const
		{ return ::RemovePlayerAttachedObject(id_, index); }
	bool IsPlayerAttachedObjectSlotUsed(int index) const
		{ return ::IsPlayerAttachedObjectSlotUsed(id_, index); }

	bool SetChatBubble(const char *text, int color, float drawdistance, int expiretime) const
		{ return ::SetPlayerChatBubble(id_, text, color, drawdistance, expiretime); }
	bool SetChatBubble(const std::string &text, int color, float drawdistance, int expiretime) const
		{ return ::SetPlayerChatBubble(id_, text.c_str(), color, drawdistance, expiretime); }

	bool PutInVehicle(int vehicleid, int seatid) const
		{ return ::PutPlayerInVehicle(id_, vehicleid, seatid); }
	int GetVehicleID() const
		{ return ::GetPlayerVehicleID(id_); }
	int GetVehicleSeat() const
		{ return ::GetPlayerVehicleSeat(id_); }
	bool RemoveFromVehicle() const
		{ return ::RemovePlayerFromVehicle(id_); }
	bool ToggleControllable(bool toggle) const
		{ return ::TogglePlayerControllable(id_, toggle); }
	bool PlaySound(int soundid, float x, float y, float z) const
		{ return ::PlayerPlaySound(id_, soundid, x, y, z); }
	bool ApplyAnimation(const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync = false) const
		{ return ::ApplyAnimation(id_, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync); }
	bool ClearAnimations(bool forcesync = false) const
		{ return ::ClearAnimations(id_, forcesync); }
	int GetAnimationIndex() const
		{ return ::GetPlayerAnimationIndex(id_); }
	int GetSpecialAction() const
		{ return ::GetPlayerSpecialAction(id_); }
	bool SetSpecialAction(int actionid) const
		{ return ::SetPlayerSpecialAction(id_, actionid); }

	bool SetCheckpoint(float x, float y, float z, float size) const
		{ return ::SetPlayerCheckpoint(id_, x, y, z, size); }
	bool DisableCheckpoint() const
		{ return ::DisablePlayerCheckpoint(id_); }
	bool SetRaceCheckpoint(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size) const
		{ return ::SetPlayerRaceCheckpoint(id_, type, x, y, z, nextx, nexty, nextz, size); }
	bool DisableRaceCheckpoint() const
		{ return ::DisablePlayerRaceCheckpoint(id_); }
	bool SetWorldBounds(float x_max, float x_min, float y_max, float y_min) const
		{ return ::SetPlayerWorldBounds(id_, x_max, x_min, y_max, y_min); }
	bool SerMarkerFor(int playerid, int color) const
		{ return ::SetPlayerMarkerForPlayer(playerid, id_, color); }
	bool ShowNameTagForPlayer(int playerid, bool show) const
		{ return ::ShowPlayerNameTagForPlayer(playerid, id_, show); } 

	bool SetMapIcon(int iconid, float x, float y, float z, int markertype, int color, int style = MAPICON_LOCAL) const
		{ return ::SetPlayerMapIcon(id_, iconid, x, y, z, markertype, color, style); }
	bool RemoveMapIcon(int iconid) const
		{ return ::RemovePlayerMapIcon(id_, iconid); }

	bool AllowTeleport(bool allow) const
		{ return ::AllowPlayerTeleport(id_, allow); }

	bool SetCameraPos(float x, float y, float z) const
		{ return ::SetPlayerCameraPos(id_, x, y, z); }
	bool SetCameraLookAt(float x, float y, float z, int cut = CAMERA_CUT) const
		{ return ::SetPlayerCameraLookAt(id_, x ,y, z, cut); }
	bool SetCameraBehind() const
		{ return ::SetCameraBehindPlayer(id_); }
	bool GetCameraPos(float *x, float *y, float *z) const
		{ return ::GetPlayerCameraPos(id_, x, y, z); }
	bool GetCameraPos(float &x, float &y, float &z) const
		{ return ::GetPlayerCameraPos(id_, &x, &y, &z); }
	bool GetCameraFrontVector(float *x, float *y, float *z) const
		{ return ::GetPlayerCameraFrontVector(id_, x, y, z); }
	bool GetCameraFrontVector(float &x, float &y, float &z) const
		{ return ::GetPlayerCameraFrontVector(id_, &x, &y, &z); }
	int GetCameraMode() const
		{ return ::GetPlayerCameraMode(id_); }
	bool AttachCameraToObject(int objectid) const
		{ return ::AttachCameraToObject(id_, objectid); }
	bool AttachCameraToPlayerObject(int playerobjectid) const
		{ return ::AttachCameraToPlayerObject(id_, playerobjectid); }
	bool InterpolateCameraPos(float FromX, float FromY, float FromZ, 
			float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) const
		{ return ::InterpolateCameraPos(id_, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut); }
	bool InterpolateCameraLookAt(float FromX, float FromY, float FromZ, 
			float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) const
		{ return ::InterpolateCameraLookAt(id_, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut); }

	bool IsPlayerConnected() const
		{ return ::IsPlayerConnected(id_); }
	bool IsPlayerInVehicle(int vehicleid) const
		{ return ::IsPlayerInVehicle(id_, vehicleid); }
	bool IsPlayerInAnyVehicle() const
		{ return ::IsPlayerInAnyVehicle(id_); }
	bool IsPlayerInCheckpoint() const
		{ return ::IsPlayerInCheckpoint(id_); }
	bool IsPlayerInRaceCheckpoint() const
		{ return ::IsPlayerInRaceCheckpoint(id_); }

	bool SetVirtualWorld(int worldid) const
		{ return ::SetPlayerVirtualWorld(id_, worldid); }
	int GetVirtualWorld() const
		{ return ::GetPlayerVirtualWorld(id_); }

	bool EnableStuntBonus(bool enable) const
		{ return ::EnableStuntBonusForPlayer(id_, enable); }

	bool TogglePlayerSpectating(bool toggle) const
		{ return ::TogglePlayerSpectating(id_, toggle); }
	bool SpectatePlayer(int playerid, int mode = SPECTATE_MODE_NORMAL) const 
		{ return ::PlayerSpectatePlayer(id_, playerid, mode); }
	bool SpectateVehicle(int vehicleid, int mode = SPECTATE_MODE_NORMAL) const
		{ return ::PlayerSpectateVehicle(id_, vehicleid, mode); }

	bool StartRecordingData(int recordtype, const char *recordname) const
		{ return ::StartRecordingPlayerData(id_, recordtype, recordname); }
	bool StartRecordingData(int recordtype, const std::string &recordname) const
		{ return ::StartRecordingPlayerData(id_, recordtype, recordname.c_str()); }
	bool StopRecordingData() const
		{ return ::StopRecordingPlayerData(id_); }

	// From samp.h
	bool IsNPC() const 
		{ return ::IsPlayerNPC(id_); }
	bool IsAdmin() const
		{ return ::IsPlayerAdmin(id_); }
	bool Kick() const
		{ return ::Kick(id_); }
	bool Ban() const
		{ return ::Ban(id_); }
	bool BanEx(const char *reason) const
		{ return ::BanEx(id_, reason); }
	bool BanEx(const std::string &reason) const
		{ return ::BanEx(id_, reason.c_str()); }
	bool GetNetworkStats(char *retstr, int size) const
		{ return ::GetPlayerNetworkStats(id_, retstr, size); }
	int GetMenu() const
		{ return ::GetPlayerMenu(id_); }
	bool SendMessage(int color, const char *message) const
		{ return ::SendClientMessage(id_, color, message); }
	bool SendMessage(int color, const std::string &message) const
		{ return ::SendClientMessage(id_, color, message.c_str()); }
	bool GameText(const char *text, int time, int style) const
		{ return ::GameTextForPlayer(id_, text, time, style); }
	bool GameText(const std::string &text, int time, int style) const
		{ return ::GameTextForPlayer(id_, text.c_str(), time, style); }
	bool GetVersion(char *version, int len) const
		{ return ::GetPlayerVersion(id_, version, len); }
	bool SelectTextDraw(int hovercolor) const
		{ return ::SelectTextDraw(id_, hovercolor); }
	bool CancelSelectTextDraw() const
		{ return ::CancelSelectTextDraw(id_); }

private:
	const int id_;
};

class PlayerTextDraw {
public:
	PlayerTextDraw(int id, int playerid) : id_(id), playerid_(playerid) {}
	virtual ~PlayerTextDraw() {}

	int GetId() const { return id_; }
	int GetPlayerId() const { return playerid_; }	

	static PlayerTextDraw Create(int playerid, float x, float y, const char *text) 
		{ return PlayerTextDraw(::CreatePlayerTextDraw(playerid, x, y, text), playerid); }
	static PlayerTextDraw Create(int playerid, float x, float y, const std::string &text) 
		{ return PlayerTextDraw(::CreatePlayerTextDraw(playerid, x, y, text.c_str()), playerid); }

	bool Destroy() const 
		{ return ::PlayerTextDrawDestroy(playerid_, id_); }
	bool SetLetterSize(float x, float y) const
		{ return ::PlayerTextDrawLetterSize(playerid_, id_, x, y); }
	bool SetTextSize(float x, float y) const 
		{ return ::PlayerTextDrawTextSize(playerid_, id_, x, y); }
	bool SetAlignment(int alignment) const 
		{ return ::PlayerTextDrawAlignment(playerid_, id_, alignment); }
	bool SetColor(int color) const 
		{ return ::PlayerTextDrawColor(playerid_, id_, color); }
	bool SetBackgroundColor(int color) const 
		{ return ::PlayerTextDrawBackgroundColor(playerid_, id_, color); }
	bool UseBox(bool use) const 
		{ return ::PlayerTextDrawUseBox(playerid_, id_, use); }
	bool SetBoxColor(int color) const 
		{ return ::PlayerTextDrawBoxColor(playerid_, id_, color); }
	bool SetShadow(int size) const 
		{ return ::PlayerTextDrawSetShadow(playerid_, id_, size); }
	bool SetOutline(int size) const 
		{ return ::PlayerTextDrawSetOutline(playerid_, id_, size); }
	bool SetFont(int font) const 
		{ return ::PlayerTextDrawFont(playerid_, id_, font); }
	bool SetProportional(bool set) const 
		{ return ::PlayerTextDrawSetProportional(playerid_, id_, set); }
	bool SetString(const char *string) const
		{ return ::PlayerTextDrawSetString(playerid_, id_, string); }
	bool SetString(const std::string &string) const
		{ return ::PlayerTextDrawSetString(playerid_, id_, string.c_str()); }
	bool SetSelectable(bool set) const
		{ return ::PlayerTextDrawSetSelectable(playerid_, id_, set); }
	bool Show() const
		{ return ::PlayerTextDrawShow(playerid_, id_); }
	bool Hide() const 
		{ return ::PlayerTextDrawHide(playerid_, id_); }

private:
	const int id_;
	const int playerid_;	
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_PLAYERS_H */
