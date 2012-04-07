/* Copyright (C) 2011-2012, Zeex
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

#include <sampgdk/config.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/export.h>

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
SAMPGDK_EXPORT bool SAMPGDK_CALL EditAttachedObject(int playerid, int index);

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayerTextDraw(int playerid, float x, float y, const char *text);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawDestroy(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawLetterSize(int playerid, int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawTextSize(int playerid, int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawAlignment(int playerid, int text, int alignment);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawColor(int playerid, int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawUseBox(int playerid, int text, bool use);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawBoxColor(int playerid, int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawSetShadow(int playerid, int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawSetOutline(int playerid, int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawBackgroundColor(int playerid, int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawFont(int playerid, int text, int font);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawSetProportional(int playerid, int text, bool set);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawSetSelectable(int playerid, int text, bool set);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawShow(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawHide(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerTextDrawSetString(int playerid, int text, const char *string);

#define PLAYER_VARTYPE_NONE   (0)
#define PLAYER_VARTYPE_INT    (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT  (3)

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarInt(int playerid, const char *varname, int value);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarInt(int playerid, const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarString(int playerid, const char *varname, const char *value);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPVarString(int playerid, const char *varname, char *value, size_t size);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarFloat(int playerid, const char *varname, float value);
SAMPGDK_EXPORT float SAMPGDK_CALL GetPVarFloat(int playerid, const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePVar(int playerid, const char *varname);

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

#define CAMERA_CUT  2
#define CAMERA_MOVE 1

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraPos(int playerid, float x, float y, float z);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetCameraBehindPlayer(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraPos(int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraFrontVector(int playerid, float *x, float *y, float *z);
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerCameraMode(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachCameraToObject(int playerid, int objectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL AttachCameraToPlayerObject(int playerid, int playerobjectid);
SAMPGDK_EXPORT bool SAMPGDK_CALL InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut);
SAMPGDK_EXPORT bool SAMPGDK_CALL InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut);

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

	void SetSpawnInfo(int team, int skin, float x, float y, float z, float rotation, 
		int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) const
	{
		::SetSpawnInfo(id_, team, skin, x, y, z, rotation, 
			weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
	}
	void Spawn() const
		{ ::SpawnPlayer(id_); }
	void SetPos(float x, float y, float z) const
		{ ::SetPlayerPos(id_, x, y, z); }
	void SetPosFindZ(float x, float y, float z) const
		{ ::SetPlayerPosFindZ(id_, x, y, z); }
	void GetPos(float *x, float *y, float *z) const
		{ ::GetPlayerPos(id_, x, y, z); }
	void GetPos(float &x, float &y, float &z) const
		{ ::GetPlayerPos(id_, &x, &y, &z); }
	void SetFacingAngle(float angle) const
		{ ::SetPlayerFacingAngle(id_, angle); }
	void GetFacingAngle(float *angle) const
		{ ::GetPlayerFacingAngle(id_, angle); }
	void GetFacingAngle(float &angle) const
		{ ::GetPlayerFacingAngle(id_, &angle); }
	void IsInRangeOfPoint(float range, float x, float y, float z) const
		{ ::IsPlayerInRangeOfPoint(id_, range, x, y, z); }
	float GetDistanceFromPoint(float x, float y, float z) const
		{ return ::GetPlayerDistanceFromPoint(id_, x, y, z); }
	bool IsStreamedInFor(int playerid) const
		{ return ::IsPlayerStreamedIn(id_, playerid); }
	void SetInterior(int interiorid) const
		{ ::SetPlayerInterior(id_, interiorid); }
	int GetInterior() const 
		{ return ::GetPlayerInterior(id_); }
	void SetHealth(float health) const
		{ ::SetPlayerHealth(id_, health); }
	float GetHealth(int playerid) const { 
		float health; 
		::GetPlayerHealth(id_, &health); 
		return health;
	}
	void SetArmour(float armour) const
		{ ::SetPlayerArmour(id_, armour); }
	float GetArmour() const {
		float armour;
		::GetPlayerArmour(id_, &armour);
		return armour;
	}
	void SetAmmo(int weaponslot, int ammo) const
		{ ::SetPlayerAmmo(id_, weaponslot, ammo); }
	int GetAmmo() const
		{ return ::GetPlayerAmmo(id_); }
	int GetWeaponState() const
		{ return ::GetPlayerWeaponState(id_); }
	int GetTargetPlayer() const
		{ return ::GetPlayerTargetPlayer(id_); }
	void SetPlayerTeam(int teamid) const
		{ ::SetPlayerTeam(id_, teamid); }
	int GetPlayerTeam() const
		{ return ::GetPlayerTeam(id_); }
	void SetScore(int playerid, int score) const
		{ ::SetPlayerScore(id_, score); }
	int GetScore() const 
		{ return ::GetPlayerScore(id_); }
	int GetDrunkLevel() const 
		{ return ::GetPlayerDrunkLevel(id_); }
	void SetDrunkLevel(int level) const
		{ ::SetPlayerDrunkLevel(id_, level); }
	void SetColor(int color) const
		{ ::SetPlayerColor(id_, color); }
	int GetColor() const
		{ return ::GetPlayerColor(id_); }
	void SetSkin(int skinid) const
		{ ::SetPlayerSkin(id_, skinid); }
	int GetSkin(int playerid) const
		{ return ::GetPlayerSkin(id_); }
	void GiveWeapon(int weaponid, int ammo) const
		{ ::GivePlayerWeapon(id_, weaponid, ammo); }
	void ResetWeapons() const
		{ ::ResetPlayerWeapons(id_); }
	void SetArmedWeapon(int weaponid) const
		{ ::SetPlayerArmedWeapon(id_, weaponid); }
	void GetWeaponData(int slot, int *weapon, int *ammo) const
		{ ::GetPlayerWeaponData(id_, slot, weapon, ammo); }
	void GetWeaponData(int slot, int &weapon, int &ammo) const
		{ ::GetPlayerWeaponData(id_, slot, &weapon, &ammo); }
	void GiveMoney(int money) const
		{ ::GivePlayerMoney(id_, money); }
	void ResetMoney() const
		{ ::ResetPlayerMoney(id_); }
	bool SetName(const char *name) const
		{ return ::SetPlayerName(id_, name) > 0; }
	bool SetName(const std::string &name) const
		{ return ::SetPlayerName(id_, name.c_str()) > 0; }
	int GetMoney() const
		{ return ::GetPlayerMoney(id_); }
	int GetState() const
		{ return ::GetPlayerState(id_); }
	void GetIp(char *ip, size_t size) const
		{ ::GetPlayerIp(id_, ip, size); }
	int GetPing() const
		{ return ::GetPlayerPing(id_); }
	int GetWeapon() const
		{ return ::GetPlayerWeapon(id_); }
	void GetKeys(int *keys, int *updown, int *leftright) const
		{ ::GetPlayerKeys(id_, keys, updown, leftright); }
	void GetKeys(int &keys, int &updown, int &leftright) const
		{ ::GetPlayerKeys(id_, &keys, &updown, &leftright); }
	void GetName(char *name, size_t size) const
		{ ::GetPlayerName(id_, name, size); }
	std::string GetName() const {
		std::vector<char> name(MAX_PLAYER_NAME);
		::GetPlayerName(id_, name.data(), MAX_PLAYER_NAME);
		return std::string(name.data());
	}
	void SetTime(int hour, int minute) const
		{ ::SetPlayerTime(id_, hour, minute); }
	void GetTime(int *hour, int *minute) const
		{ ::GetPlayerTime(id_, hour, minute); }
	void GetTime(int &hour, int &minute) const
		{ ::GetPlayerTime(id_, &hour, &minute); }
	void ToggleClock(bool toggle) const
		{ ::TogglePlayerClock(id_, toggle); }
	void SetWeather(int weather) const
		{ ::SetPlayerWeather(id_, weather); }
	void ForceClassSelection(int playerid) const
		{ ::ForceClassSelection(id_); }
	void SetWantedLevel(int level) const
		{ ::SetPlayerWantedLevel(id_, level); }
	int GetWantedLevel() const 
		{ return ::GetPlayerWantedLevel(id_); }
	void SetFightingStyle(int style) const
		{ ::SetPlayerFightingStyle(id_, style); }
	int GetFightingStyle() const
		{ return ::GetPlayerFightingStyle(id_); }
	void SetVelocity(float x, float y, float z) const
		{ ::SetPlayerVelocity(id_, x, y, z); }
	void GetVelocity(float *x, float *y, float *z) const
		{ ::GetPlayerVelocity(id_, x, y, z); }
	void GetVelocity(float &x, float &y, float &z) const
		{ ::GetPlayerVelocity(id_, &x, &y, &z); }
	float GetSpeed() const {
		float velX, velY, velZ;
		GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}
	void PlayCrimeReport(int suspectid, int crime) const
		{ ::PlayCrimeReportForPlayer(id_, suspectid, crime); }
	bool PlayAudioStream(const char *url, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float distance = 50.0f, bool usepos = false) const
		{ return ::PlayAudioStreamForPlayer(id_, url, posX, posY, posZ, distance, usepos); }
	bool PlayAudioStream(const std::string &url, float posX, float posY, float posZ, float distance, bool usepos) const
		{ return ::PlayAudioStreamForPlayer(id_, url.c_str(), posX, posY, posZ, distance, usepos); }
	bool StopAudioStream() const
		{ return ::StopAudioStreamForPlayer(id_); }
	void SetShopName(const char *shopname) const
		{ ::SetPlayerShopName(id_, shopname); }
	void SetShopName(const std::string &shopname) const
		{ ::SetPlayerShopName(id_, shopname.c_str()); }
	void SetSkillLevel(int skill, int level) const
		{ ::SetPlayerSkillLevel(id_, skill, level); }
	int GetSurfingVehicleID() const
		{ return ::GetPlayerSurfingVehicleID(id_); }
	int GetSurfingObjectID(int playerid) const
		{ return ::GetPlayerSurfingObjectID(id_); }
	void RemoveBuilding(int modelid, float fX, float fY, float fZ, float fRadius) const
		{ ::RemoveBuildingForPlayer(id_, modelid, fX, fY, fZ, fRadius);	}

	void SetAttachedObject(int index, int modelid, int bone, float fOffsetX = 0.0f, float fOffsetY = 0.0f, float fOffsetZ = 0.0f, 
		float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, float fScaleX = 1.0f, float fScaleY = 1.0f, float fScaleZ = 1.0f) const
	{ 
		::SetPlayerAttachedObject(id_, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ); 
	}
	void RemoveAttachedObject(int index) const
		{ ::RemovePlayerAttachedObject(id_, index); }
	bool IsPlayerAttachedObjectSlotUsed(int playerid, int index) const
		{ return ::IsPlayerAttachedObjectSlotUsed(id_, index); }

	void SetChatBubble(const char *text, int color, float drawdistance, int expiretime) const
		{ ::SetPlayerChatBubble(id_, text, color, drawdistance, expiretime); }
	void SetChatBubble(const std::string &text, int color, float drawdistance, int expiretime) const
		{ ::SetPlayerChatBubble(id_, text.c_str(), color, drawdistance, expiretime); }

	void PutInVehicle(int vehicleid, int seatid) const
		{ ::PutPlayerInVehicle(id_, vehicleid, seatid); }
	int GetVehicleID() const
		{ return ::GetPlayerVehicleID(id_); }
	int GetVehicleSeat() const
		{ return ::GetPlayerVehicleSeat(id_); }
	void RemoveFromVehicle() const
		{ ::RemovePlayerFromVehicle(id_); }
	void ToggleControllable(bool toggle) const
		{ ::TogglePlayerControllable(id_, toggle); }
	void PlaySound(int playerid, int soundid, float x, float y, float z) const
		{ ::PlayerPlaySound(id_, soundid, x, y, z); }
	void ApplyAnimation(const char *animlib, const char *animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync = false) const
		{ ::ApplyAnimation(id_, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync); }
	void ClearAnimations(bool forcesync = false) const
		{ ::ClearAnimations(id_, forcesync); }
	int GetAnimationIndex() const
		{ return ::GetPlayerAnimationIndex(id_); }
	int GetSpecialAction() const
		{ return ::GetPlayerSpecialAction(id_); }
	void SetSpecialAction(int actionid) const
		{ ::SetPlayerSpecialAction(id_, actionid); }

	void SetCheckpoint(float x, float y, float z, float size) const
		{ ::SetPlayerCheckpoint(id_, x, y, z, size); }
	void DisableCheckpoint() const
		{ ::DisablePlayerCheckpoint(id_); }
	void SetRaceCheckpoint(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size) const
		{ ::SetPlayerRaceCheckpoint(id_, type, x, y, z, nextx, nexty, nextz, size); }
	void DisableRaceCheckpoint() const
		{ ::DisablePlayerRaceCheckpoint(id_); }
	void SetWorldBounds(float x_max, float x_min, float y_max, float y_min) const
		{ ::SetPlayerWorldBounds(id_, x_max, x_min, y_max, y_min); }
	void SerMarkerFor(int playerid, int color) const
		{ ::SetPlayerMarkerForPlayer(playerid, id_, color); }
	void ShowNameTagForPlayer(int playerid, bool show) const
		{ ::ShowPlayerNameTagForPlayer(playerid, id_, show); } 

	void SetMapIcon(int iconid, float x, float y, float z, int markertype, int color, int style = MAPICON_LOCAL) const
		{ ::SetPlayerMapIcon(id_, iconid, x, y, z, markertype, color, style); }
	void RemoveMapIcon(int iconid) const
		{ ::RemovePlayerMapIcon(id_, iconid); }

	void AllowTeleport(bool allow) const
		{ ::AllowPlayerTeleport(id_, allow); }

	void SetCameraPos(float x, float y, float z) const
		{ ::SetPlayerCameraPos(id_, x, y, z); }
	void SetCameraLookAt(float x, float y, float z, int cut = CAMERA_CUT) const
		{ ::SetPlayerCameraLookAt(id_, x ,y, z, cut); }
	void SetCameraBehind() const
		{ ::SetCameraBehindPlayer(id_); }
	void GetCameraPos(float *x, float *y, float *z) const
		{ ::GetPlayerCameraPos(id_, x, y, z); }
	void GetCameraPos(float &x, float &y, float &z) const
		{ ::GetPlayerCameraPos(id_, &x, &y, &z); }
	void GetCameraFrontVector(float *x, float *y, float *z) const
		{ ::GetPlayerCameraFrontVector(id_, x, y, z); }
	void GetCameraFrontVector(float &x, float &y, float &z) const
		{ ::GetPlayerCameraFrontVector(id_, &x, &y, &z); }
	int GetCameraMode() const
		{ return ::GetPlayerCameraMode(id_); }
	void AttachCameraToObject(int objectid) const
		{ ::AttachCameraToObject(id_, objectid); }
	bool AttachCameraToPlayerObject(int playerobjectid) const
		{ ::AttachCameraToPlayerObject(id_, playerobjectid); }
	bool InterpolateCameraPos(float FromX, float FromY, float FromZ, 
			float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) const
		{ ::InterpolateCameraPos(id_, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut); }
	bool InterpolateCameraLookAt(float FromX, float FromY, float FromZ, 
			float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) const
		{ ::InterpolateCameraLookAt(id_, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut); }

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

	void SetVirtualWorld(int worldid) const
		{ ::SetPlayerVirtualWorld(id_, worldid); }
	int GetVirtualWorld() const
		{ return ::GetPlayerVirtualWorld(id_); }

	void EnableStuntBonus(bool enable) const
		{ ::EnableStuntBonusForPlayer(id_, enable); }

	void TogglePlayerSpectating(bool toggle) const
		{ ::TogglePlayerSpectating(id_, toggle); }
	bool SpectatePlayer(int playerid, int mode = SPECTATE_MODE_NORMAL) const 
		{ return ::PlayerSpectatePlayer(id_, playerid, mode); }
	bool SpectateVehicle(int vehicleid, int mode = SPECTATE_MODE_NORMAL) const
		{ return ::PlayerSpectateVehicle(id_, vehicleid, mode); }

	void StartRecordingData(int recordtype, const char *recordname) const
		{ ::StartRecordingPlayerData(id_, recordtype, recordname); }
	void StartRecordingData(int recordtype, const std::string &recordname) const
		{ ::StartRecordingPlayerData(id_, recordtype, recordname.c_str()); }
	void StopRecordingData() const
		{ ::StopRecordingPlayerData(id_); }

	// From samp.h
	bool IsNPC() const 
		{ return ::IsPlayerNPC(id_); }
	bool IsAdmin() const
		{ return ::IsPlayerAdmin(id_); }
	void Kick() const
		{ ::Kick(id_); }
	void Ban() const
		{ ::Ban(id_); }
	void BanEx(const char *reason) const
		{ ::BanEx(id_, reason); }
	void BanEx(const std::string &reason) const
		{ ::BanEx(id_, reason.c_str()); }
	void GetNetworkStats(char *retstr, size_t size) const
		{ ::GetPlayerNetworkStats(id_, retstr, size); }
	int GetMenu() const
		{ return ::GetPlayerMenu(id_); }
	void SendMessage(int color, const char *message) const
		{ ::SendClientMessage(id_, color, message); }
	void SendMessage(int color, const std::string &message) const
		{ ::SendClientMessage(id_, color, message.c_str()); }
	void GameText(const char *text, int time, int style) const
		{ ::GameTextForPlayer(id_, text, time, style); }
	void GameText(const std::string &text, int time, int style) const
		{ ::GameTextForPlayer(id_, text.c_str(), time, style); }
	void GetVersion(char *version, size_t len) const
		{ ::GetPlayerVersion(id_, version, len); }
	void SelectTextDraw(int hovercolor) const
		{ ::SelectTextDraw(id_, hovercolor); }
	void CancelSelectTextDraw(int hovercolor) const
		{ ::CancelSelectTextDraw(id_); }

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

	void Destroy() const 
		{ ::PlayerTextDrawDestroy(playerid_, id_); }
	void SetLetterSize(float x, float y) const
		{ ::PlayerTextDrawLetterSize(playerid_, id_, x, y); }
	void SetTextSize(float x, float y) const 
		{ ::PlayerTextDrawTextSize(playerid_, id_, x, y); }
	void SetAlignment(int alignment) const 
		{ ::PlayerTextDrawAlignment(playerid_, id_, alignment); }
	void SetColor(int color) const 
		{ ::PlayerTextDrawColor(playerid_, id_, color); }
	void SetBackgroundColor(int text, int color) const 
		{ ::PlayerTextDrawBackgroundColor(playerid_, id_, color); }
	void UseBox(bool use) const 
		{ ::PlayerTextDrawUseBox(playerid_, id_, use); }
	void SetBoxColor(int color) const 
		{ ::PlayerTextDrawBoxColor(playerid_, id_, color); }
	void SetShadow(int size) const 
		{ ::PlayerTextDrawSetShadow(playerid_, id_, size); }
	void SetOutline(int size) const 
		{ ::PlayerTextDrawSetOutline(playerid_, id_, size); }
	void SetFont(int font) const 
		{ ::PlayerTextDrawFont(playerid_, id_, font); }
	void SetProportional(bool set) const 
		{ ::PlayerTextDrawSetProportional(playerid_, id_, set); }
	void SetString(const char *string) const
		{ ::PlayerTextDrawSetString(playerid_, id_, string); }
	void SetString(const std::string &string) const
		{ ::PlayerTextDrawSetString(playerid_, id_, string.c_str()); }
	void SetSelectable(bool set) const
		{ ::PlayerTextDrawSetSelectable(playerid_, id_, set); }
	void Show() const
		{ ::PlayerTextDrawShow(playerid_, id_); }
	void Hide() const 
		{ ::PlayerTextDrawHide(playerid_, id_); }

private:
	const int id_;
	const int playerid_;	
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_PLAYERS_H */
