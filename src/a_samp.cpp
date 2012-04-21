// Copyright (C) 2011-2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/config.h>
#include <sampgdk/export.h>
#include <sampgdk/amx/amx.h>

#include "fakeamx.h"
#include "natives.h"

SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessage(int playerid, int color, const char *message) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendClientMessage");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		0,
		playerid,
		color,
		message_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessageToAll(int color, const char *message) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendClientMessageToAll");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		0,
		color,
		message_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToPlayer(int playerid, int senderid, const char *message) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendPlayerMessageToPlayer");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		0,
		playerid,
		senderid,
		message_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToAll(int senderid, const char *message) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendPlayerMessageToAll");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		0,
		senderid,
		message_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendDeathMessage(int killer, int killee, int weapon) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendDeathMessage");
	cell params[] = {
		0,
		killer,
		killee,
		weapon
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForAll(const char *text, int time, int style) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GameTextForAll");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		text_.address(),
		time,
		style
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForPlayer(int playerid, const char *text, int time, int style) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GameTextForPlayer");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		playerid,
		text_.address(),
		time,
		style
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetServerTickCount() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetTickCount");
	return FakeAmx::CallNative(native);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetMaxPlayers() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetMaxPlayers");
	return FakeAmx::CallNative(native);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetGameModeText(const char *text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetGameModeText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		text_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetTeamCount(int count) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetTeamCount");
	cell params[] = {
		0,
		count
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z,
	float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddPlayerClass");
	cell params[] = {
		0,
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle,
	int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddPlayerClassEx");
	cell params[] = {
		0,
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
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z,
	float z_angle, int color1, int color2)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddStaticVehicle");
	cell params[] = {
		0,
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		color1,
		color2
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z,
	float z_angle, int color1, int color2, int respawn_delay)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddStaticVehicleEx");
	cell params[] = {
		0,
		modelid,
		amx_ftoc(spawn_x),
		amx_ftoc(spawn_y),
		amx_ftoc(spawn_z),
		amx_ftoc(z_angle),
		color1,
		color2,
		respawn_delay
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddStaticPickup");
	cell params[] = {
		0,
		model,
		type,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		virtualworld
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePickup(int model, int type, float x, float y, float z, int virtualworld) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreatePickup");
	cell params[] = {
		0,
		model,
		type,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		virtualworld
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPickup(int pickup) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DestroyPickup");
	cell params[] = {
		0,
		pickup
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowNameTags(bool show) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("ShowNameTags");
	cell params[] = {
		0,
		show
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerMarkers(bool show) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("ShowPlayerMarkers");
	cell params[] = {
		0,
		show
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GameModeExit() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GameModeExit");
	return FakeAmx::CallNativeBool(native);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetWorldTime(int hour) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetWorldTime");
	cell params[] = {
		0,
		hour
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetWeaponName(int weaponid, char *name, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetWeaponName");
	FakeAmxHeapObject name_(size);
	cell params[] = {
		0,
		weaponid,
		name_.address(),
		size
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	name_.GetAsString(name, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL EnableTirePopping(bool enable) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("EnableTirePopping");
	cell params[] = {
		0,
		enable
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AllowInteriorWeapons(bool allow) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AllowInteriorWeapons");
	cell params[] = {
		0,
		allow
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetWeather(int weatherid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetWeather");
	cell params[] = {
		0,
		weatherid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetGravity(float gravity) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetGravity");
	cell params[] = {
		0,
		amx_ftoc(gravity)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL AllowAdminTeleport(bool allow) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AllowAdminTeleport");
	cell params[] = {
		0,
		allow
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetDeathDropAmount(int amount) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetDeathDropAmount");
	cell params[] = {
		0,
		amount
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL CreateExplosion(float x, float y, float z, int type, float radius) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreateExplosion");
	cell params[] = {
		0,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		type,
		amx_ftoc(radius)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL EnableZoneNames(bool enable) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("EnableZoneNames");
	cell params[] = {
		0,
		enable
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL UsePlayerPedAnims() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("UsePlayerPedAnims");
	return FakeAmx::CallNativeBool(native);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisableInteriorEnterExits() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DisableInteriorEnterExits");
	return FakeAmx::CallNativeBool(native);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetNameTagDrawDistance(float distance) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetNameTagDrawDistance");
	cell params[] = {
		0,
		amx_ftoc(distance)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisableNameTagLOS() {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DisableNameTagLOS");
	return FakeAmx::CallNativeBool(native);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL LimitGlobalChatRadius(float chat_radius) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("LimitGlobalChatRadius");
	cell params[] = {
		0,
		amx_ftoc(chat_radius)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL LimitPlayerMarkerRadius(float marker_radius) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("LimitPlayerMarkerRadius");
	cell params[] = {
		0,
		amx_ftoc(marker_radius)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ConnectNPC(const char *name, const char *script) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("ConnectNPC");
	FakeAmxHeapObject name_(name);
	FakeAmxHeapObject script_(script);
	cell params[] = {
		0,
		name_.address(),
		script_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerNPC(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsPlayerNPC");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAdmin(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsPlayerAdmin");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Kick(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Kick");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Ban(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Ban");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL BanEx(int playerid, const char *reason) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("BanEx");
	FakeAmxHeapObject reason_(reason);
	cell params[] = {
		0,
		playerid,
		reason_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendRconCommand(const char *command) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SendRconCommand");
	FakeAmxHeapObject command_(command);
	cell params[] = {
		0,
		command_.address(),
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsString(const char *varname, char *value, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetServerVarAsString");
	FakeAmxHeapObject varname_(varname);
	FakeAmxHeapObject value_(size);
	cell params[] = {
		0,
		varname_.address(),
		value_.address(),
		size
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	value_.GetAsString(value, size);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetServerVarAsInt(const char *varname) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetServerVarAsInt");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		0,
		varname_.address(),
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsBool(const char *varname) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetServerVarAsBool");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		0,
		varname_.address(),
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerNetworkStats(int playerid, char *retstr, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetPlayerNetworkStats");
	FakeAmxHeapObject retstr_(size);
	cell params[] = {
		0,
		playerid,
		retstr_.address(),
		size
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	retstr_.GetAsString(retstr, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetNetworkStats(char *retstr, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetNetworkStats");
	FakeAmxHeapObject retstr_(size);
	cell params[] = {
		0,
		retstr_.address(),
		size
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	retstr_.GetAsString(retstr, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerVersion(int playerid, char *version, int len) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetPlayerVersion");
	FakeAmxHeapObject version_(len + 1);
	cell params[] = {
		0,
		playerid,
		version_.address(),
		len
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	version_.GetAsString(version, len + 1);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL MenuCreate(const char *title, int columns, float x, float y, float col1width, float col2width) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreateMenu");
	FakeAmxHeapObject title_(title);
	cell params[] = {
		0,
		title_.address(),
		columns,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(col1width),
		amx_ftoc(col2width)
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDestroy(int menuid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DestroyMenu");
	cell params[] = {
		0,
		menuid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL MenuAddItem(int menuid, int column, const char *menutext) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("AddMenuItem");
	FakeAmxHeapObject menutext_(menutext);
	cell params[] = {
		0,
		menuid,
		column,
		menutext_.address()
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuSetColumnHeader(int menuid, int column, const char *columnheader) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SetMenuColumnHeader");
	FakeAmxHeapObject columnheader_(columnheader);
	cell params[] = {
		0,
		menuid,
		column,
		columnheader_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuShowForPlayer(int menuid, int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("ShowMenuForPlayer");
	cell params[] = {
		0,
		menuid,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuHideForPlayer(int menuid, int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("HideMenuForPlayer");
	cell params[] = {
		0,
		menuid,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidMenu(int menuid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("IsValidMenu");
	cell params[] = {
		0,
		menuid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDisable(int menuid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DisableMenu");
	cell params[] = {
		0,
		menuid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDisableRow(int menuid, int row) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DisableMenuRow");
	cell params[] = {
		0,
		menuid,
		row
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerMenu(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GetPlayerMenu");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL TextDrawCreate(float x, float y, const char *text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawCreate");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		amx_ftoc(x),
		amx_ftoc(y),
		text_.address()
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawDestroy(int text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawDestroy");
	cell params[] = {
		0,
		text
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawLetterSize(int text, float x, float y) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawLetterSize");
	cell params[] = {
		0,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawTextSize(int text, float x, float y) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawTextSize");
	cell params[] = {
		0,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawAlignment(int text, int alignment) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawAlignment");
	cell params[] = {
		0,
		text,
		alignment
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawColor(int text, int color) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawColor");
	cell params[] = {
		0,
		text,
		color
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawUseBox(int text, bool use) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawUseBox");
	cell params[] = {
		0,
		text,
		use
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBoxColor(int text, int color) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawBoxColor");
	cell params[] = {
		0,
		text,
		color
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetShadow(int text, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawSetShadow");
	cell params[] = {
		0,
		text,
		size
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetOutline(int text, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawSetOutline");
	cell params[] = {
		0,
		text,
		size
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBackgroundColor(int text, int color) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawBackgroundColor");
	cell params[] = {
		0,
		text,
		color
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawFont(int text, int font) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawFont");
	cell params[] = {
		0,
		text,
		font
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetProportional(int text, bool set) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawSetProportional");
	cell params[] = {
		0,
		text,
		set
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetSelectable(int text, bool set) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawSetSelectable");
	cell params[] = {
		0,
		text,
		set
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForPlayer(int playerid, int text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawShowForPlayer");
	cell params[] = {
		0,
		playerid,
		text
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForPlayer(int playerid, int text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawHideForPlayer");
	cell params[] = {
		0,
		playerid,
		text
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForAll(int text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawShowForAll");
	cell params[] = {
		0,
		text
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForAll(int text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawHideForAll");
	cell params[] = {
		0,
		text
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetString(int text, const char *string) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("TextDrawSetString");
	FakeAmxHeapObject string_(string);
	cell params[] = {
		0,
		text,
		string_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SelectTextDraw(int playerid, int hovercolor) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("SelectTextDraw");
	cell params[] = {
		0,
		playerid,
		hovercolor
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL CancelSelectTextDraw(int playerid) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CancelSelectTextDraw");
	cell params[] = {
		0,
		playerid
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GangZoneCreate(float minx, float miny, float maxx, float maxy) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneCreate");
	cell params[] = {
		0,
		amx_ftoc(minx),
		amx_ftoc(miny),
		amx_ftoc(maxx),
		amx_ftoc(maxy)
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneDestroy(int zone) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneDestroy");
	cell params[] = {
		0,
		zone
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForPlayer(int playerid, int zone, int color) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneShowForPlayer");
	cell params[] = {
		0,
		playerid,
		zone,
		color
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForAll(int zone, int color) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneShowForAll");
	cell params[] = {
		0,
		zone,
		color
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForPlayer(int playerid, int zone) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneHideForPlayer");
	cell params[] = {
		0,
		playerid,
		zone
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForAll(int zone) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneHideForAll");
	cell params[] = {
		0,
		zone
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForPlayer(int playerid, int zone, int flashcolor) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneFlashForPlayer");
	cell params[] = {
		0,
		playerid,
		zone,
		flashcolor
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForAll(int zone, int flashcolor) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneFlashForAll");
	cell params[] = {
		0,
		zone,
		flashcolor
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForPlayer(int playerid, int zone) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneStopFlashForPlayer");
	cell params[] = {
		0,
		playerid,
		zone
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForAll(int zone) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("GangZoneStopFlashForAll");
	cell params[] = {
		0,
		zone
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL Create3DTextLabel(const char *text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Create3DTextLabel");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		text_.address(),
		color,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(DrawDistance),
		virtualworld,
		testLOS
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Delete3DTextLabel(int id) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Delete3DTextLabel");
	cell params[] = {
		0,
		id
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Attach3DTextLabelToPlayer");
	cell params[] = {
		0,
		id,
		playerid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Attach3DTextLabelToVehicle");
	cell params[] = {
		0,
		id,
		vehicleid,
		amx_ftoc(OffsetX),
		amx_ftoc(OffsetY),
		amx_ftoc(OffsetZ)
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Update3DTextLabelText(int id, int color, const char *text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("Update3DTextLabelText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		id,
		color,
		text_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayer3DTextLabel(int playerid, const char *text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("CreatePlayer3DTextLabel");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		playerid,
		text_.address(),
		color,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(z),
		amx_ftoc(DrawDistance),
		attachedplayer,
		attachedvehicle,
		testLOS
	};
	return FakeAmx::CallNative(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePlayer3DTextLabel(int playerid, int id) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("DeletePlayer3DTextLabel");
	cell params[] = {
		0,
		playerid,
		id
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char *text) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("UpdatePlayer3DTextLabelText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		0,
		playerid,
		id,
		color,
		text_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption,
	const char *info, const char *button1, const char *button2)
{
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("ShowPlayerDialog");
	FakeAmxHeapObject caption_(caption);
	FakeAmxHeapObject info_(info);
	FakeAmxHeapObject button1_(button1);
	FakeAmxHeapObject button2_(button2);
	cell params[] = {
		0,
		playerid,
		dialogid,
		style,
		caption_.address(),
		info_.address(),
		button1_.address(),
		button2_.address()
	};
	return FakeAmx::CallNativeBool(native, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL gpci(int playerid, char *buffer, int size) {
	static AMX_NATIVE native = Natives::GetInstance().GetNativeWarn("gpci");
	FakeAmxHeapObject buffer_(size);
	cell params[] = {
		0,
		playerid,
		buffer_.address(),
		size
	};
	bool ret = FakeAmx::CallNativeBool(native, params);
	buffer_.GetAsString(buffer, size);
	return ret;
}