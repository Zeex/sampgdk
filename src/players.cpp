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

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/samp.h>

#include "fakeamx.h"
#include "wrapper.h"

SAMPGDK_EXPORT bool SAMPGDK_CALL SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetSpawnInfo");
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
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SpawnPlayer(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SpawnPlayer");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerPos(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerPos");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerPosFindZ(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerPosFindZ");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerPos(int playerid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerPos");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		4 * 4,
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerFacingAngle(int playerid, float angle) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerFacingAngle");
	cell params[] = {
		2 * 4,
		playerid,
		amx_ftoc(angle)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerFacingAngle(int playerid, float &angle) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerFacingAngle");
	FakeAmxHeapObject angle_;
	cell params[] = {
		2 * 4,
		playerid,
		angle_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	angle = angle_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerInRangeOfPoint");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(range),
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT float SAMPGDK_CALL GetPlayerDistanceFromPoint(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerDistanceFromPoint");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	cell ret = FakeAmx::GetInstance().CallNative(native, params);
	return amx_ctof(ret);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerStreamedIn(int playerid, int forplayerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerStreamedIn");
	cell params[] = {
		2 * 4,
		playerid,
		forplayerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerInterior(int playerid, int interiorid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerInterior");
	cell params[] = {
		2 * 4,
		playerid,
		interiorid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerInterior(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerInterior");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerHealth(int playerid, float health) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerHealth");
	cell params[] = {
		2 * 4,
		playerid,
		amx_ftoc(health)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerHealth(int playerid, float &health) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerHealth");
	FakeAmxHeapObject health_;
	cell params[] = {
		2 * 4,
		playerid,
		health_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	health = health_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerArmour(int playerid, float armour) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerArmour");
	cell params[] = {
		2 * 4,
		playerid,
		amx_ftoc(armour)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerArmour(int playerid, float &armour) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerArmour");
	FakeAmxHeapObject armour_;
	cell params[] = {
		2 * 4,
		playerid,
		armour_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	armour = armour_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerAmmo(int playerid, int weaponslot, int ammo) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerAmmo");
	cell params[] = {
		3 * 4,
		playerid,
		weaponslot,
		ammo
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerAmmo(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerAmmo");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWeaponState(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerWeaponState");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerTargetPlayer(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerTargetPlayer");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerTeam(int playerid, int teamid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerTeam");
	cell params[] = {
		2 * 4,
		playerid,
		teamid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerTeam(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerTeam");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerScore(int playerid, long score) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerScore");
	cell params[] = {
		2 * 4,
		playerid,
		score
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT long SAMPGDK_CALL GetPlayerScore(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerScore");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerDrunkLevel(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerDrunkLevel");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerDrunkLevel(int playerid, int level) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerDrunkLevel");
	cell params[] = {
		2 * 4,
		playerid,
		level
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerColor(int playerid, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerColor");
	cell params[] = {
		2 * 4,
		playerid,
		color
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT long SAMPGDK_CALL GetPlayerColor(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerColor");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSkin(int playerid, int skinid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerSkin");
	cell params[] = {
		2 * 4,
		playerid,
		skinid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSkin(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerSkin");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GivePlayerWeapon(int playerid, int weaponid, int ammo) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GivePlayerWeapon");
	cell params[] = {
		3 * 4,
		playerid,
		weaponid,
		ammo
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ResetPlayerWeapons(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ResetPlayerWeapons");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerArmedWeapon(int playerid, int weaponid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerArmedWeapon");
	cell params[] = {
		2 * 4,
		playerid,
		weaponid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerWeaponData(int playerid, int slot, int &weapon, int &ammo) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerWeaponData");
	FakeAmxHeapObject weapon_;
	FakeAmxHeapObject ammo_;
	cell params[] = {
		4 * 4,
		playerid,
		slot,
		weapon_.address(),
		ammo_.address(),
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	weapon = weapon_.Get();
	ammo = ammo_.Get();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GivePlayerMoney(int playerid, long money) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GivePlayerMoney");
	cell params[] = {
		2 * 4,
		playerid,
		money
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ResetPlayerMoney(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ResetPlayerMoney");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL SetPlayerName(int playerid, const char *name) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerName");
	FakeAmxHeapObject name_(name);
	cell params[] = {
		2 * 4,
		playerid,
		name_.address()
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT long SAMPGDK_CALL GetPlayerMoney(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerMoney");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerState(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerState");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerIp(int playerid, char *ip, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerIp");
	FakeAmxHeapObject ip_(size);
	cell params[] = {
		3 * 4,
		playerid,
		ip_.address(),
		size
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	ip_.GetAsString(ip, size);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerPing(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerPing");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWeapon(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerWeapon");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerKeys(int playerid, int &keys, int &updown, int &leftright) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerKeys");
	FakeAmxHeapObject keys_;
	FakeAmxHeapObject updown_;
	FakeAmxHeapObject leftright_;
	cell params[] = {
		4 * 4,
		playerid,
		keys_.address(),
		updown_.address(),
		leftright_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	keys = keys_.Get();
	updown = updown_.Get();
	leftright = leftright_.Get();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerName(int playerid, char *name, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerName");
	FakeAmxHeapObject name_(size);
	cell params[] = {
		3 * 4,
		playerid,
		name_.address(),
		size
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	name_.GetAsString(name, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerTime(int playerid, int hour, int minute) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerTime");
	cell params[] = {
		3 * 4,
		playerid,
		hour,
		minute
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerTime(int playerid, int &hour, int &minute) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerTime");
	FakeAmxHeapObject hour_;
	FakeAmxHeapObject minute_;
	cell params[] = {
		3 * 4,
		playerid,
		hour_.address(),
		minute_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	hour = hour_.Get();
	minute = minute_.Get();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerClock(int playerid, bool toggle) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TogglePlayerClock");
	cell params[] = {
		2 * 4,
		playerid,
		toggle
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWeather(int playerid, int weather) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerWeather");
	cell params[] = {
		2 * 4,
		playerid,
		weather
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ForceClassSelection(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ForceClassSelection");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWantedLevel(int playerid, int level) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerWantedLevel");
	cell params[] = {
		2 * 4,
		playerid,
		level
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerWantedLevel(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerWantedLevel");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerFightingStyle(int playerid, int style) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerFightingStyle");
	cell params[] = {
		2 * 4,
		playerid,
		style
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerFightingStyle(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerFightingStyle");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerVelocity(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerVelocity");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerVelocity( int playerid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerVelocity");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		4 * 4,
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL PlayCrimeReportForPlayer(int playerid, int suspectid, int crime) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PlayCrimeReportForPlayer");
	cell params[] = {
		3 * 4,
		playerid,
		suspectid,
		crime
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

bool PlayAudioStreamForPlayer(int playerid, const char *url, 
	float posX, float posY, float posZ, float distance, bool usepos)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PlayAudioStreamForPlayer");
	FakeAmxHeapObject url_(url);
	cell params[] = {
		7 * 4,
		playerid,
		url_.address(),
		amx_ftoc(posX),
		amx_ftoc(posY),
		amx_ftoc(posZ),
		amx_ftoc(distance),
		usepos
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopAudioStreamForPlayer(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("StopAudioStreamForPlayer");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerShopName(int playerid, const char *shopname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerShopName");
	FakeAmxHeapObject shopname_(shopname);
	cell params[] = {
		2 * 4,
		playerid,
		shopname_.address()
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSkillLevel(int playerid, int skill, int level) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerSkillLevel");
	cell params[] = {
		3 * 4,
		playerid,
		skill,
		level
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSurfingVehicleID(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerSurfingVehicleID");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSurfingObjectID(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerSurfingObjectID");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

bool RemoveBuildingForPlayer(int playerid, int modelid, 
	float fX, float fY, float fZ, float fRadius)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("RemoveBuildingForPlayer");
	cell params[] = {
		6 * 4,
		playerid,
		modelid,
		amx_ftoc(fX),
		amx_ftoc(fY),
		amx_ftoc(fZ),
		amx_ftoc(fRadius)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

bool SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, 
	float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, 
	float fScaleY, float fScaleZ) 
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerAttachedObject");
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
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerAttachedObject(int playerid, int index) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("RemovePlayerAttachedObject");
	cell params[] = {
		2 * 4,
		playerid,
		index
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAttachedObjectSlotUsed(int playerid, int index) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerAttachedObjectSlotUsed");
	cell params[] = {
		2 * 4,
		playerid,
		index
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarInt(int playerid, const char *varname, int value) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPVarInt");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		3 * 4,
		playerid,
		varname_.address(),
		value
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarInt(int playerid, const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarInt");
	FakeAmxHeapObject varname_(varname);;
	cell params[] = {
		2 * 4,
		playerid,
		varname_.address()
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarString(int playerid, const char *varname, const char *value) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPVarString");
	FakeAmxHeapObject varname_(varname);
	FakeAmxHeapObject value_(value);
	cell params[] = {
		3 * 4,
		playerid,
		varname_.address(),
		value_.address()
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPVarString(int playerid, const char *varname, char *value, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarString");
	FakeAmxHeapObject varname_(varname);
	FakeAmxHeapObject value_(size);
	cell params[] = {
		4 * 4,
		playerid,
		varname_.address(),
		value_.address(),
		size
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	value_.GetAsString(value, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPVarFloat(int playerid, const char *varname, float value) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPVarFloat");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		3 * 4,
		playerid,
		varname_.address(),
		amx_ftoc(value)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT float SAMPGDK_CALL GetPVarFloat(int playerid, const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarFloat");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * 4,
		playerid,
		varname_.address()
	};
	cell ret = FakeAmx::GetInstance().CallNative(native, params);
	return amx_ctof(ret);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePVar(int playerid, const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DeletePVar");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * 4,
		playerid,
		varname_.address()
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarsUpperIndex(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarsUpperIndex");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPVarNameAtIndex(int playerid, int index, char *varname, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarNameAtIndex");
	FakeAmxHeapObject varname_(size);
	cell params[] = {
		4 * 4,
		playerid,
		index,
		varname_.address(),
		size
	};
	bool ret =  FakeAmx::GetInstance().CallBooleanNative(native, params);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPVarType(int playerid, const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPVarType");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		2 * 4,
		playerid,
		varname_.address()
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerChatBubble(int playerid, const char *text, long color, float drawdistance, long expiretime) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerChatBubble");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		5 * 4,
		playerid,
		text_.address(),
		color,
		amx_ftoc(drawdistance),
		expiretime
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL PutPlayerInVehicle(int playerid, int vehicleid, int seatid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PutPlayerInVehicle");
	cell params[] = {
		3 * 4,
		playerid,
		vehicleid,
		seatid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerVehicleID(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerVehicleID");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerVehicleSeat(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerVehicleSeat");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerFromVehicle(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("RemovePlayerFromVehicle");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerControllable(int playerid, bool toggle) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TogglePlayerControllable");
	cell params[] = {
		2 * 4,
		playerid,
		toggle
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerPlaySound(int playerid, int soundid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PlayerPlaySound");
	cell params[] = {
		5 * 4,
		playerid,
		soundid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

bool ApplyAnimation(int playerid, const char *animlib, const char *animname, 
	float fDelta, bool loop, bool lockx, bool locky, bool freeze, long time, bool forcesync)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ApplyAnimation");
	FakeAmxHeapObject animlib_(animlib);
	FakeAmxHeapObject animname_(animname);
	cell params[] = {
		10 * 4,
		playerid,
		animlib_.address(),
		animname_.address(),
		amx_ftoc(fDelta),
		loop,
		lockx,
		locky,
		freeze,
		time,
		forcesync
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ClearAnimations(int playerid, bool forcesync) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ClearAnimations");
	cell params[] = {
		2 * 4,
		playerid,
		forcesync
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerAnimationIndex(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerAnimationIndex");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetAnimationName(int index, char *animlib, size_t animlib_size, char *animname, size_t animname_size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetAnimationName");
	FakeAmxHeapObject animlib_(animlib_size);
	FakeAmxHeapObject animname_(animname_size);
	cell params[] = {
		5 * 4,
		index,
		animlib_.address(),
		animlib_size,
		animname_.address(),
		animname_size
	};
	bool ret =  FakeAmx::GetInstance().CallBooleanNative(native, params);
	animlib_.GetAsString(animlib, animlib_size);
	animname_.GetAsString(animname, animname_size);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerSpecialAction(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerSpecialAction");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerSpecialAction(int playerid, int actionid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerSpecialAction");
	cell params[] = {
		2 * 4,
		playerid,
		actionid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCheckpoint(int playerid, float x, float y, float z, float size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerCheckpoint");
	cell params[] = {
		5 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(size)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisablePlayerCheckpoint(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisablePlayerCheckpoint");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, 
	float nextx, float nexty, float nextz, float size) 
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerRaceCheckpoint");
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
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisablePlayerRaceCheckpoint(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisablePlayerRaceCheckpoint");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerWorldBounds");
	cell params[] = {
		5 * 4,
		playerid,
		amx_ftoc(x_max),
		amx_ftoc(x_min),
		amx_ftoc(y_max),
		amx_ftoc(y_min)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerMarkerForPlayer(int playerid, int showplayerid, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerMarkerForPlayer");
	cell params[] = {
		3 * 4,
		playerid,
		showplayerid,
		color
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ShowPlayerNameTagForPlayer");
	cell params[] = {
		3 * 4,
		playerid,
		showplayerid,
		show
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, long color, int style) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerMapIcon");
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
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL RemovePlayerMapIcon(int playerid, int iconid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("RemovePlayerMapIcon");
	cell params[] = {
		2 * 4,
		playerid,
		iconid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AllowPlayerTeleport(int playerid, bool allow) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AllowPlayerTeleport");
	cell params[] = {
		2 * 4,
		playerid,
		allow
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraPos(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerCameraPos");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerCameraLookAt(int playerid, float x, float y, float z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerCameraLookAt");
	cell params[] = {
		4 * 4,
		playerid,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z)
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetCameraBehindPlayer(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetCameraBehindPlayer");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraPos(int playerid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerCameraPos");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		4 * 4,
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerCameraFrontVector(int playerid, float &x, float &y, float &z) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerCameraFrontVector");
	FakeAmxHeapObject x_;
	FakeAmxHeapObject y_;
	FakeAmxHeapObject z_;
	cell params[] = {
		4 * 4,
		playerid,
		x_.address(),
		y_.address(),
		z_.address()
	};
	bool ret = FakeAmx::GetInstance().CallBooleanNative(native, params);
	x = x_.GetAsFloat();
	y = y_.GetAsFloat();
	z = z_.GetAsFloat();
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerCameraMode(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerCameraMode");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerConnected(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerConnected");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInVehicle(int playerid, int vehicleid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerInVehicle");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInAnyVehicle(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerInAnyVehicle");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInCheckpoint(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerInCheckpoint");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerInRaceCheckpoint(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerInRaceCheckpoint");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetPlayerVirtualWorld(int playerid, long worldid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetPlayerVirtualWorld");
	cell params[] = {
		2 * 4,
		playerid,
		worldid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT long SAMPGDK_CALL GetPlayerVirtualWorld(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerVirtualWorld");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL EnableStuntBonusForPlayer(int playerid, bool enable) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("EnableStuntBonusForPlayer");
	cell params[] = {
		2 * 4,
		playerid,
		enable
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL EnableStuntBonusForAll(bool enable) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("EnableStuntBonusForAll");
	cell params[] = {
		1 * 4,
		enable
	};
	FakeAmx::GetInstance().CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TogglePlayerSpectating(int playerid, bool toggle) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TogglePlayerSpectating");
	cell params[] = {
		2 * 4,
		playerid,
		toggle
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerSpectatePlayer(int playerid, int targetplayerid, int mode) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PlayerSpectatePlayer");
	cell params[] = {
		3 * 4,
		playerid,
		targetplayerid,
		mode
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("PlayerSpectateVehicle");
	cell params[] = {
		3 * 4,
		playerid,
		targetvehicleid,
		mode
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StartRecordingPlayerData(int playerid, int recordtype, const char *recordname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("StartRecordingPlayerData");
	FakeAmxHeapObject recordname_(recordname);
	cell params[] = {
		3 * 4,
		playerid,
		recordtype,
		recordname_.address()
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL StopRecordingPlayerData(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("StopRecordingPlayerData");
	cell params[] = {
		1 * 4,
		playerid
	};
	return FakeAmx::GetInstance().CallBooleanNative(native, params);
}
