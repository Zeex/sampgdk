/* Copyright (c) 2011 Zeex
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

#ifndef SAMPGDK_PLAYERS_H
#define SAMPGDK_PLAYERS_H

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/samp.h>

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

SAMPGDK_EXPORT bool SAMPGDK_CALL SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
SAMPGDK_EXPORT bool SAMPGDK_CALL SpawnPlayer(int playerid);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerPos(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerPosFindZ(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerPos(int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerFacingAngle(int playerid, float angle);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerFacingAngle(int playerid, float *angle);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z);
SAMPGDK_EXPORT float SAMPGDK_CALL GetPlayerDistanceFromPoint(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerStreamedIn(int playerid, int forplayerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerInterior(int playerid, int interiorid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerInterior(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerHealth(int playerid, float health);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerHealth(int playerid, float *health);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerArmour(int playerid, float armour);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerArmour(int playerid, float *armour);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerAmmo(int playerid, int weaponslot, int ammo);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerAmmo(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWeaponState(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerTargetPlayer(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerTeam(int playerid, int teamid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerTeam(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerScore(int playerid, int score);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerScore(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerDrunkLevel(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerDrunkLevel(int playerid, int level);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerColor(int playerid, int color);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerColor(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSkin(int playerid, int skinid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSkin(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GivePlayerWeapon(int playerid, int weaponid, int ammo);
SAMPGDK_EXPORT bool SAMPGDK_CALL ResetPlayerWeapons(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerArmedWeapon(int playerid, int weaponid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerWeaponData(int playerid, int slot, int *weapon, int *ammo);
SAMPGDK_EXPORT bool SAMPGDK_CALL GivePlayerMoney(int playerid, int money);
SAMPGDK_EXPORT bool SAMPGDK_CALL ResetPlayerMoney(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL SetPlayerName(int playerid, const char *name);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerMoney(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerState(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerIp(int playerid, char *ip, size_t size);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerPing(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWeapon(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerKeys(int playerid, int *keys, int *updown, int *leftright);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerName(int playerid, char *name, size_t size);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerTime(int playerid, int hour, int minute);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerTime(int playerid, int *hour, int *minute);
SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerClock(int playerid, bool toggle);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWeather(int playerid, int weather);
SAMPGDK_EXPORT bool SAMPGDK_CALL ForceClassSelection(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWantedLevel(int playerid, int level);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWantedLevel(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerFightingStyle(int playerid, int style);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerFightingStyle(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerVelocity(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerVelocity( int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayCrimeReportForPlayer(int playerid, int suspectid, int crime);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayAudioStreamForPlayer(int playerid, const char *url, float posX, float posY, float posZ, float distance, bool usepos);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopAudioStreamForPlayer(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerShopName(int playerid, const char *shopname);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSkillLevel(int playerid, int skill, int level);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSurfingVehicleID(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSurfingObjectID(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius);

#define MAX_PLAYER_ATTACHED_OBJECTS (10)

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerAttachedObject(int playerid, int index);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAttachedObjectSlotUsed(int playerid, int index);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarInt(int playerid, const char *varname, int value);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarInt(int playerid, const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarString(int playerid, const char *varname, const char *value);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPVarString(int playerid, const char *varname, char *value, size_t size);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarFloat(int playerid, const char *varname, float value);
SAMPGDK_EXPORT float SAMPGDK_CALL GetPVarFloat(int playerid, const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePVar(int playerid, const char *varname);

#define PLAYER_VARTYPE_NONE   (0)
#define PLAYER_VARTYPE_INT    (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT  (3)

SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarsUpperIndex(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPVarNameAtIndex(int playerid, int index, char *varname, size_t size);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarType(int playerid, const char *varname);

#define MAX_CHATBUBBLE_LENGTH (144)
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerChatBubble(int playerid, const char *text, int color, float drawdistance, int expiretime);

SAMPGDK_EXPORT bool SAMPGDK_CALL PutPlayerInVehicle(int playerid, int vehicleid, int seatid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerVehicleID(int playerid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerVehicleSeat(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerFromVehicle(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerControllable(int playerid, bool toggle);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerPlaySound(int playerid, int soundid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL ApplyAnimation(int playerid, const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync);
SAMPGDK_EXPORT bool SAMPGDK_CALL ClearAnimations(int playerid, bool forcesync);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerAnimationIndex(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetAnimationName(int index, char *animlib, size_t animlib_size, char *animname, size_t animname_size);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSpecialAction(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSpecialAction(int playerid, int actionid);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCheckpoint(int playerid, float x, float y, float z, float size);
SAMPGDK_EXPORT bool SAMPGDK_CALL DisablePlayerCheckpoint(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size);
SAMPGDK_EXPORT bool SAMPGDK_CALL DisablePlayerRaceCheckpoint(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show);

#define MAPICON_LOCAL             (0)
#define MAPICON_GLOBAL            (1)
#define MAPICON_LOCAL_CHECKPOINT  (2)
#define MAPICON_GLOBAL_CHECKPOINT (3)

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style);
SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerMapIcon(int playerid, int iconid);

SAMPGDK_EXPORT bool SAMPGDK_CALL AllowPlayerTeleport(int playerid, bool allow);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraPos(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraLookAt(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetCameraBehindPlayer(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraPos(int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraFrontVector(int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerCameraMode(int playerid);

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerConnected(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInVehicle(int playerid, int vehicleid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInAnyVehicle(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInCheckpoint(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInRaceCheckpoint(int playerid);

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerVirtualWorld(int playerid, int worldid);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerVirtualWorld(int playerid);

SAMPGDK_EXPORT bool SAMPGDK_CALL EnableStuntBonusForPlayer(int playerid, bool enable);
SAMPGDK_EXPORT void SAMPGDK_CALL EnableStuntBonusForAll(bool enable);

#define SPECTATE_MODE_NORMAL  (1)
#define SPECTATE_MODE_FIXED   (2)
#define SPECTATE_MODE_SIDE    (3)

SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerSpectating(int playerid, bool toggle);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerSpectatePlayer(int playerid, int targetplayerid, int mode);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode);

#define PLAYER_RECORDING_TYPE_NONE   (0)
#define PLAYER_RECORDING_TYPE_DRIVER (1)
#define PLAYER_RECORDING_TYPE_ONFOOT (2)

SAMPGDK_EXPORT bool SAMPGDK_CALL StartRecordingPlayerData(int playerid, int recordtype, const char *recordname);
SAMPGDK_EXPORT bool SAMPGDK_CALL StopRecordingPlayerData(int playerid);

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>

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
	Player(int playerid) : playerid_(playerid) { assert(playerid_ != INVALID_PLAYER_ID); }

	// Implicit conversion to 'int'
	operator int() const { return playerid_; }

	// Explicit ID request
	int GetPlayerID() const { return playerid_; }

	void SetSpawnInfo(int team, int skin, float x, float y, float z, float rotation, 
		int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) const
	{
		::SetSpawnInfo(playerid_, team, skin, x, y, z, rotation, 
			weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
	}
	void Spawn() const
		{ ::SpawnPlayer(playerid_); }
	void SetPos(float x, float y, float z) const
		{ ::SetPlayerPos(playerid_, x, y, z); }
	void SetPosFindZ(float x, float y, float z) const
		{ ::SetPlayerPosFindZ(playerid_, x, y, z); }
	void GetPos(float *x, float *y, float *z) const
		{ ::GetPlayerPos(playerid_, x, y, z); }
	void GetPos(float &x, float &y, float &z) const
		{ ::GetPlayerPos(playerid_, &x, &y, &z); }
	void SetFacingAngle(float angle) const
		{ ::SetPlayerFacingAngle(playerid_, angle); }
	void GetFacingAngle(float *angle) const
		{ ::GetPlayerFacingAngle(playerid_, angle); }
	void GetFacingAngle(float &angle) const
		{ ::GetPlayerFacingAngle(playerid_, &angle); }
	void IsInRangeOfPoint(float range, float x, float y, float z) const
		{ ::IsPlayerInRangeOfPoint(playerid_, range, x, y, z); }
	float GetDistanceFromPoint(float x, float y, float z) const
		{ return ::GetPlayerDistanceFromPoint(playerid_, x, y, z); }
	bool IsStreamedInFor(int playerid) const
		{ return ::IsPlayerStreamedIn(playerid_, playerid); }
	void SetInterior(int interiorid) const
		{ ::SetPlayerInterior(playerid_, interiorid); }
	int GetInterior() const 
		{ return ::GetPlayerInterior(playerid_); }
	void SetHealth(float health) const
		{ ::SetPlayerHealth(playerid_, health); }
	float GetHealth(int playerid) const { 
		float health; 
		::GetPlayerHealth(playerid_, &health); 
		return health;
	}
	void SetArmour(float armour) const
		{ ::SetPlayerArmour(playerid_, armour); }
	float GetArmour() const {
		float armour;
		::GetPlayerArmour(playerid_, &armour);
		return armour;
	}
	void SetAmmo(int weaponslot, int ammo) const
		{ ::SetPlayerAmmo(playerid_, weaponslot, ammo); }
	int GetAmmo() const
		{ return ::GetPlayerAmmo(playerid_); }
	int GetWeaponState() const
		{ return ::GetPlayerWeaponState(playerid_); }
	int GetTargetPlayer() const
		{ return ::GetPlayerTargetPlayer(playerid_); }
	void SetPlayerTeam(int teamid) const
		{ ::SetPlayerTeam(playerid_, teamid); }
	int GetPlayerTeam() const
		{ return ::GetPlayerTeam(playerid_); }
	void SetScore(int playerid, int score) const
		{ ::SetPlayerScore(playerid_, score); }
	int GetScore() const 
		{ return ::GetPlayerScore(playerid_); }
	int GetDrunkLevel() const 
		{ return ::GetPlayerDrunkLevel(playerid_); }
	void SetDrunkLevel(int level) const
		{ ::SetPlayerDrunkLevel(playerid_, level); }
	void SetColor(int color) const
		{ ::SetPlayerColor(playerid_, color); }
	int GetColor() const
		{ return ::GetPlayerColor(playerid_); }
	void SetSkin(int skinid) const
		{ ::SetPlayerSkin(playerid_, skinid); }
	int GetSkin(int playerid) const
		{ return ::GetPlayerSkin(playerid_); }
	void GiveWeapon(int weaponid, int ammo) const
		{ ::GivePlayerWeapon(playerid_, weaponid, ammo); }
	void ResetWeapons() const
		{ ::ResetPlayerWeapons(playerid_); }
	void SetArmedWeapon(int weaponid) const
		{ ::SetPlayerArmedWeapon(playerid_, weaponid); }
	void GetWeaponData(int slot, int *weapon, int *ammo) const
		{ ::GetPlayerWeaponData(playerid_, slot, weapon, ammo); }
	void GetWeaponData(int slot, int &weapon, int &ammo) const
		{ ::GetPlayerWeaponData(playerid_, slot, &weapon, &ammo); }
	void GiveMoney(int money) const
		{ ::GivePlayerMoney(playerid_, money); }
	void ResetMoney() const
		{ ::ResetPlayerMoney(playerid_); }
	bool SetName(const char *name) const
		{ return ::SetPlayerName(playerid_, name) > 0; }
	bool SetName(const std::string &name) const
		{ return ::SetPlayerName(playerid_, name.c_str()) > 0; }
	int GetMoney() const
		{ return ::GetPlayerMoney(playerid_); }
	int GetState() const
		{ return ::GetPlayerState(playerid_); }
	void GetIp(char *ip, size_t size) const
		{ ::GetPlayerIp(playerid_, ip, size); }
	int GetPing() const
		{ return ::GetPlayerPing(playerid_); }
	int GetWeapon() const
		{ return ::GetPlayerWeapon(playerid_); }
	void GetKeys(int *keys, int *updown, int *leftright) const
		{ ::GetPlayerKeys(playerid_, keys, updown, leftright); }
	void GetKeys(int &keys, int &updown, int &leftright) const
		{ ::GetPlayerKeys(playerid_, &keys, &updown, &leftright); }
	void GetName(char *name, size_t size) const
		{ ::GetPlayerName(playerid_, name, size); }
	std::string GetName() const {
		std::string name(static_cast<std::string::size_type>(MAX_PLAYER_NAME), '\0');
		::GetPlayerName(playerid_, const_cast<char*>(name.data()), MAX_PLAYER_NAME);
		return name;
	}
	void SetTime(int hour, int minute) const
		{ ::SetPlayerTime(playerid_, hour, minute); }
	void GetTime(int *hour, int *minute) const
		{ ::GetPlayerTime(playerid_, hour, minute); }
	void GetTime(int &hour, int &minute) const
		{ ::GetPlayerTime(playerid_, &hour, &minute); }
	void ToggleClock(bool toggle) const
		{ ::TogglePlayerClock(playerid_, toggle); }
	void SetWeather(int weather) const
		{ ::SetPlayerWeather(playerid_, weather); }
	void ForceClassSelection(int playerid) const
		{ ::ForceClassSelection(playerid_); }
	void SetWantedLevel(int level) const
		{ ::SetPlayerWantedLevel(playerid_, level); }
	int GetWantedLevel() const 
		{ return ::GetPlayerWantedLevel(playerid_); }
	void SetFightingStyle(int style) const
		{ ::SetPlayerFightingStyle(playerid_, style); }
	int GetFightingStyle() const
		{ return ::GetPlayerFightingStyle(playerid_); }
	void SetVelocity(float x, float y, float z) const
		{ ::SetPlayerVelocity(playerid_, x, y, z); }
	void GetVelocity(float *x, float *y, float *z) const
		{ ::GetPlayerVelocity(playerid_, x, y, z); }
	void GetVelocity(float &x, float &y, float &z) const
		{ ::GetPlayerVelocity(playerid_, &x, &y, &z); }
	float GetSpeed() const {
		float velX, velY, velZ;
		GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}
	void PlayCrimeReport(int suspectid, int crime) const
		{ ::PlayCrimeReportForPlayer(playerid_, suspectid, crime); }
	bool PlayAudioStream(const char *url, float posX, float posY, float posZ, float distance, bool usepos) const
		{ return ::PlayAudioStreamForPlayer(playerid_, url, posX, posY, posZ, distance, usepos); }
	bool PlayAudioStream(const std::string &url, float posX, float posY, float posZ, float distance, bool usepos) const
		{ return ::PlayAudioStreamForPlayer(playerid_, url.c_str(), posX, posY, posZ, distance, usepos); }
	bool StopAudioStream() const
		{ return ::StopAudioStreamForPlayer(playerid_); }
	void SetShopName(const char *shopname) const
		{ ::SetPlayerShopName(playerid_, shopname); }
	void SetShopName(const std::string &shopname) const
		{ ::SetPlayerShopName(playerid_, shopname.c_str()); }
	void SetSkillLevel(int skill, int level) const
		{ ::SetPlayerSkillLevel(playerid_, skill, level); }
	int GetSurfingVehicleID() const
		{ return ::GetPlayerSurfingVehicleID(playerid_); }
	int GetSurfingObjectID(int playerid) const
		{ return ::GetPlayerSurfingObjectID(playerid_); }
	void RemoveBuilding(int modelid, float fX, float fY, float fZ, float fRadius) const
		{ ::RemoveBuildingForPlayer(playerid_, modelid, fX, fY, fZ, fRadius);	}

	void SetAttachedObject(int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, 
		float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ) const
	{ 
		::SetPlayerAttachedObject(playerid_, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ); 
	}
	void RemoveAttachedObject(int index) const
		{ ::RemovePlayerAttachedObject(playerid_, index); }
	bool IsPlayerAttachedObjectSlotUsed(int playerid, int index) const
		{ return ::IsPlayerAttachedObjectSlotUsed(playerid_, index); }

	void SetChatBubble(const char *text, int color, float drawdistance, int expiretime) const
		{ ::SetPlayerChatBubble(playerid_, text, color, drawdistance, expiretime); }
	void SetChatBubble(const std::string &text, int color, float drawdistance, int expiretime) const
		{ ::SetPlayerChatBubble(playerid_, text.c_str(), color, drawdistance, expiretime); }

	void PutInVehicle(int vehicleid, int seatid) const
		{ ::PutPlayerInVehicle(playerid_, vehicleid, seatid); }
	int GetVehicleID() const
		{ return ::GetPlayerVehicleID(playerid_); }
	int GetVehicleSeat() const
		{ return ::GetPlayerVehicleSeat(playerid_); }
	void RemoveFromVehicle() const
		{ ::RemovePlayerFromVehicle(playerid_); }
	void ToggleControllable(bool toggle) const
		{ ::TogglePlayerControllable(playerid_, toggle); }
	void PlaySound(int playerid, int soundid, float x, float y, float z) const
		{ ::PlayerPlaySound(playerid_, soundid, x, y, z); }
	void ApplyAnimation(const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync) const
		{ ::ApplyAnimation(playerid_, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync); }
	void ClearAnimations(bool forcesync) const
		{ ::ClearAnimations(playerid_, forcesync); }
	int GetAnimationIndex() const
		{ return ::GetPlayerAnimationIndex(playerid_); }
	int GetSpecialAction() const
		{ return ::GetPlayerSpecialAction(playerid_); }
	void SetSpecialAction(int actionid) const
		{ ::SetPlayerSpecialAction(playerid_, actionid); }

	void SetCheckpoint(float x, float y, float z, float size) const
		{ ::SetPlayerCheckpoint(playerid_, x, y, z, size); }
	void DisableCheckpoint() const
		{ ::DisablePlayerCheckpoint(playerid_); }
	void SetRaceCheckpoint(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size) const
		{ ::SetPlayerRaceCheckpoint(playerid_, type, x, y, z, nextx, nexty, nextz, size); }
	void DisableRaceCheckpoint() const
		{ ::DisablePlayerRaceCheckpoint(playerid_); }
	void SetWorldBounds(float x_max, float x_min, float y_max, float y_min) const
		{ ::SetPlayerWorldBounds(playerid_, x_max, x_min, y_max, y_min); }
	void SerMarkerFor(int playerid, int color) const
		{ ::SetPlayerMarkerForPlayer(playerid, playerid_, color); }
	void ShowNameTagForPlayer(int playerid, bool show) const
		{ ::ShowPlayerNameTagForPlayer(playerid, playerid_, show); } 

	void SetMapIcon(int iconid, float x, float y, float z, int markertype, int color, int style) const
		{ ::SetPlayerMapIcon(playerid_, iconid, x, y, z, markertype, color, style); }
	void RemoveMapIcon(int iconid) const
		{ ::RemovePlayerMapIcon(playerid_, iconid); }

	void AllowTeleport(bool allow) const
		{ ::AllowPlayerTeleport(playerid_, allow); }

	void SetPlayerCameraPos(float x, float y, float z) const
		{ ::SetPlayerCameraPos(playerid_, x, y, z); }
	void SetPlayerCameraLookAt(float x, float y, float z) const
		{ ::SetPlayerCameraLookAt(playerid_, x ,y, z); }
	void SetCameraBehind() const
		{ ::SetCameraBehindPlayer(playerid_); }
	void GetCameraPos(float *x, float *y, float *z) const
		{ ::GetPlayerCameraPos(playerid_, x, y, z); }
	void GetCameraPos(float &x, float &y, float &z) const
		{ ::GetPlayerCameraPos(playerid_, &x, &y, &z); }
	void GetCameraFrontVector(float *x, float *y, float *z) const
		{ ::GetPlayerCameraFrontVector(playerid_, x, y, z); }
	void GetCameraFrontVector(float &x, float &y, float &z) const
		{ ::GetPlayerCameraFrontVector(playerid_, &x, &y, &z); }
	int GetCameraMode() const
		{ return ::GetPlayerCameraMode(playerid_); }

	bool IsPlayerConnected() const
		{ return ::IsPlayerConnected(playerid_); }
	bool IsPlayerInVehicle(int vehicleid) const
		{ return ::IsPlayerInVehicle(playerid_, vehicleid); }
	bool IsPlayerInAnyVehicle() const
		{ return ::IsPlayerInAnyVehicle(playerid_); }
	bool IsPlayerInCheckpoint() const
		{ return ::IsPlayerInCheckpoint(playerid_); }
	bool IsPlayerInRaceCheckpoint() const
		{ return ::IsPlayerInRaceCheckpoint(playerid_); }

	void SetVirtualWorld(int worldid) const
		{ ::SetPlayerVirtualWorld(playerid_, worldid); }
	int GetVirtualWorld() const
		{ return ::GetPlayerVirtualWorld(playerid_); }

	void EnableStuntBonus(bool enable) const
		{ ::EnableStuntBonusForPlayer(playerid_, enable); }

	void TogglePlayerSpectating(bool toggle) const
		{ ::TogglePlayerSpectating(playerid_, toggle); }
	bool SpectatePlayer(int playerid, int mode) const 
		{ return ::PlayerSpectatePlayer(playerid_, playerid, mode); }
	bool SpectateVehicle(int vehicleid, int mode) const
		{ return ::PlayerSpectateVehicle(playerid_, vehicleid, mode); }

	void StartRecordingData(int recordtype, const char *recordname) const
		{ ::StartRecordingPlayerData(playerid_, recordtype, recordname); }
	void StartRecordingData(int recordtype, const std::string &recordname) const
		{ ::StartRecordingPlayerData(playerid_, recordtype, recordname.c_str()); }
	void StopRecordingData() const
		{ ::StopRecordingPlayerData(playerid_); }

private:
	const int playerid_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_PLAYERS_H */
