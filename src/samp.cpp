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

#include "fakeamx.h"
#include "wrapper.h"

SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessage(int playerid, long color, const char *message) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendClientMessage");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		3 * 4,
		playerid,
		color,
		message_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SendClientMessageToAll(long color, const char *message) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendClientMessageToAll");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		2 * 4,
		color,
		message_.address()
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToPlayer(int playerid, int senderid, const char *message) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendPlayerMessageToPlayer");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		3 * 4,
		playerid,
		senderid,
		message_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToAll(int senderid, const char *message) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendPlayerMessageToAll");
	FakeAmxHeapObject message_(message);
	cell params[] = {
		2 * 4,
		senderid,
		message_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SendDeathMessage(int killer, int killee, int weapon) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendDeathMessage");
	cell params[] = {
		3 * 4,
		killer,
		killee,
		weapon
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForAll(const char *text, long time, int style) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GameTextForAll");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * 4,
		text_.address(),
		time,
		style
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForPlayer(int playerid, const char *text, long time, int style) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GameTextForPlayer");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		4 * 4,
		playerid,
		text_.address(),
		time,
		style
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT long SAMPGDK_CALL GetTickCount() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetTickCount");
	return native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetMaxPlayers() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetMaxPlayers");
	return native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetGameModeText(const char *text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetGameModeText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		1 * 4, 
		text_.address()
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetTeamCount(long count) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetTeamCount");
	cell params[] = {
		1 * 4, 
		count
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, 
	float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) 
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddPlayerClass");
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

SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, 
	int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddPlayerClassEx");
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

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, 
	float z_angle, long color1, long color2)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddStaticVehicle");
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

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, 
	float z_angle, long color1, long color2, long respawn_delay) 
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddStaticVehicleEx");
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

SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticPickup(int model, int type, float x, float y, float z, long virtualworld) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddStaticPickup");
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

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePickup(int model, int type, float x, float y, float z, long virtualworld) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreatePickup");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPickup(int pickup) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DestroyPickup");
	cell params[] = {
		1 * 4,
		pickup
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL ShowNameTags(bool show) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ShowNameTags");
	cell params[] = {
		1 * 4,
		show
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL ShowPlayerMarkers(bool show) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ShowPlayerMarkers");
	cell params[] = {
		1 * 4,
		show
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL GameModeExit() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GameModeExit");
	native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetWorldTime(short hour) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetWorldTime");
	cell params[] = {
		1 * 4,
		hour
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetWeaponName(int weaponid, char *name, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetWeaponName");
	FakeAmxHeapObject name_(size);
	cell params[] = {
		3 * 4,
		weaponid,
		name_.address(),
		size
	};
	bool ret = native(&::fakeAmx, params) != 0;
	name_.GetAsString(name, size);
	return ret;
}

SAMPGDK_EXPORT void SAMPGDK_CALL EnableTirePopping(bool enable) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("EnableTirePopping");
	cell params[] = {
		1 * 4,
		enable
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AllowInteriorWeapons(bool allow) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AllowInteriorWeapons");
	cell params[] = {
		1 * 4,
		allow
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetWeather(int weatherid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetWeather");
	cell params[] = {
		1 * 4,
		weatherid
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetGravity(float gravity) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetGravity");
	cell params[] = {
		1 * 4,
		amx_ftoc(gravity)
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL AllowAdminTeleport(bool allow) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AllowAdminTeleport");
	cell params[] = {
		1 * 4,
		allow
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetDeathDropAmount(long amount) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetDeathDropAmount");
	cell params[] = {
		1 * 4,
		amount
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL CreateExplosion(float x, float y, float z, short type, float radius) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreateExplosion");
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

SAMPGDK_EXPORT void SAMPGDK_CALL EnableZoneNames(bool enable) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("EnableZoneNames");
	cell params[] = {
		1 * 4,
		enable
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL UsePlayerPedAnims() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("UsePlayerPedAnims");
	native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT void SAMPGDK_CALL DisableInteriorEnterExits() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisableInteriorEnterExits");
	native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT void SAMPGDK_CALL SetNameTagDrawDistance(float distance) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetNameTagDrawDistance");
	cell params[] = {
		1 * 4,
		amx_ftoc(distance)
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL DisableNameTagLOS() {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisableNameTagLOS");
	native(&::fakeAmx, 0);
}

SAMPGDK_EXPORT void SAMPGDK_CALL LimitGlobalChatRadius(float chat_radius) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("LimitGlobalChatRadius");
	cell params[] = {
		1 * 4,
		amx_ftoc(chat_radius)
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT void SAMPGDK_CALL LimitPlayerMarkerRadius(float marker_radius) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("LimitPlayerMarkerRadius");
	cell params[] = {
		1 * 4,
		amx_ftoc(marker_radius)
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ConnectNPC(const char *name, const char *script) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ConnectNPC");
	FakeAmxHeapObject name_(name);
	FakeAmxHeapObject script_(script);
	cell params[] = {
		2 * 4,
		name_.address(),
		script_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerNPC(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerNPC");
	cell params[] = {
		1 * 4,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAdmin(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsPlayerAdmin");
	cell params[] = {
		1 * 4,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Kick(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Kick");
	cell params[] = {
		1 * 4,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Ban(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Ban");
	cell params[] = {
		1 * 4,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL BanEx(int playerid, const char *reason) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("BanEx");
	FakeAmxHeapObject reason_(reason);
	cell params[] = {
		2 * 4,
		playerid,
		reason_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT void SAMPGDK_CALL SendRconCommand(const char *command) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SendRconCommand");
	FakeAmxHeapObject command_(command);
	cell params[] = {
		1 * 4,
		command_.address(),
	};
	native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsString(const char *varname, char *value, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetServerVarAsString");
	FakeAmxHeapObject varname_(varname);
	FakeAmxHeapObject value_(size); 
	cell params[] = {
		3 * 4,
		varname_.address(),
		value_.address(),
		size
	};
	bool ret = native(&::fakeAmx, params) != 0;
	value_.GetAsString(value, size);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetServerVarAsInt(const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetServerVarAsInt");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		1 * 4,
		varname_.address(),
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsBool(const char *varname) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetServerVarAsBool");
	FakeAmxHeapObject varname_(varname);
	cell params[] = {
		1 * 4,
		varname_.address(),
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerNetworkStats(int playerid, char *retstr, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerNetworkStats");
	FakeAmxHeapObject retstr_(size);
	cell params[] = {
		3 * 4,
		playerid,
		retstr_.address(),
		size
	};
	bool ret = native(&::fakeAmx, params) != 0;
	retstr_.GetAsString(retstr, size);
	return ret;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GetNetworkStats(char *retstr, size_t size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetNetworkStats");
	FakeAmxHeapObject retstr_(size);
	cell params[] = {
		2 * 4,
		retstr_.address(),
		size
	};
	bool ret = native(&::fakeAmx, params) != 0;
	retstr_.GetAsString(retstr, size);
	return ret;
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreateMenu(const char *title, int columns, float x, float y, float col1width, float col2width) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreateMenu");
	FakeAmxHeapObject title_(title);
	cell params[] = {
		6 * 4,
		title_.address(),
		columns,
		amx_ftoc(x),
		amx_ftoc(y),
		amx_ftoc(col1width),
		amx_ftoc(col2width)
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyMenu(int menuid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DestroyMenu");
	cell params[] = {
		1 * 4,
		menuid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL AddMenuItem(int menuid, int column, const char *menutext) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("AddMenuItem");
	FakeAmxHeapObject menutext_(menutext);
	cell params[] = {
		3 * 4,
		menuid,
		column,
		menutext_.address()
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL SetMenuColumnHeader(int menuid, int column, const char *columnheader) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("SetMenuColumnHeader");
	FakeAmxHeapObject columnheader_(columnheader);
	cell params[] = {
		3 * 4,
		menuid,
		column,
		columnheader_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowMenuForPlayer(int menuid, int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ShowMenuForPlayer");
	cell params[] = {
		2 * 4,
		menuid,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL HideMenuForPlayer(int menuid, int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("HideMenuForPlayer");
	cell params[] = {
		2 * 4,
		menuid,
		playerid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidMenu(int menuid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("IsValidMenu");
	cell params[] = {
		1 * 4,
		menuid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisableMenu(int menuid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisableMenu");
	cell params[] = {
		1 * 4,
		menuid
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DisableMenuRow(int menuid, int row) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DisableMenuRow");
	cell params[] = {
		2 * 4,
		menuid,
		row
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerMenu(int playerid) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GetPlayerMenu");
	cell params[] = {
		1 * 4,
		playerid
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT int SAMPGDK_CALL TextDrawCreate(float x, float y, const char *text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawCreate");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * 4,
		amx_ftoc(x),
		amx_ftoc(y),
		text_.address()
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawDestroy(int text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawDestroy");
	cell params[] = {
		1 * 4,
		text
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawLetterSize(int text, float x, float y) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawLetterSize");
	cell params[] = {
		3 * 4,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawTextSize(int text, float x, float y) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawTextSize");
	cell params[] = {
		3 * 4,
		text,
		amx_ftoc(x),
		amx_ftoc(y)
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawAlignment(int text, int alignment) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawAlignment");
	cell params[] = {
		2 * 4,
		text,
		alignment
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawColor(int text, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawColor");
	cell params[] = {
		2 * 4,
		text,
		color
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawUseBox(int text, bool use) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawUseBox");
	cell params[] = {
		2 * 4,
		text,
		use
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBoxColor(int text, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawBoxColor");
	cell params[] = {
		2 * 4,
		text,
		color
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetShadow(int text, int size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawSetShadow");
	cell params[] = {
		2 * 4,
		text,
		size
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetOutline(int text, int size) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawSetOutline");
	cell params[] = {
		2 * 4,
		text,
		size
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBackgroundColor(int text, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawBackgroundColor");
	cell params[] = {
		2 * 4,
		text,
		color
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawFont(int text, int font) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawFont");
	cell params[] = {
		2 * 4,
		text,
		font
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetProportional(int text, bool set) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawSetProportional");
	cell params[] = {
		2 * 4,
		text,
		set
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForPlayer(int playerid, int text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawShowForPlayer");
	cell params[] = {
		2 * 4,
		playerid,
		text
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForPlayer(int playerid, int text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawHideForPlayer");
	cell params[] = {
		2 * 4,
		playerid,
		text
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForAll(int text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawShowForAll");
	cell params[] = {
		1 * 4,
		text
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForAll(int text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawHideForAll");
	cell params[] = {
		1 * 4,
		text
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetString(int text, const char *string) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("TextDrawSetString");
	FakeAmxHeapObject string_(string);
	cell params[] = {
		2 * 4,
		text,
		string_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL GangZoneCreate(float minx, float miny, float maxx, float maxy) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneCreate");
	cell params[] = {
		4 * 4,
		amx_ftoc(minx),
		amx_ftoc(miny),
		amx_ftoc(maxx),
		amx_ftoc(maxy)
	};
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneDestroy(int zone) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneDestroy");
	cell params[] = {
		1 * 4,
		zone
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForPlayer(int playerid, int zone, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneShowForPlayer");
	cell params[] = {
		3 * 4,
		playerid,
		zone,
		color
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForAll(int zone, long color) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneShowForAll");
	cell params[] = {
		2 * 4,
		zone,
		color
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForPlayer(int playerid, int zone) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneHideForPlayer");
	cell params[] = {
		2 * 4,
		playerid,
		zone
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForAll(int zone) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneHideForAll");
	cell params[] = {
		1 * 4,
		zone
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForPlayer(int playerid, int zone, long flashcolor) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneFlashForPlayer");
	cell params[] = {
		3 * 4,
		playerid,
		zone,
		flashcolor
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForAll(int zone, long flashcolor) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneFlashForAll");
	cell params[] = {
		2 * 4,
		zone,
		flashcolor
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForPlayer(int playerid, int zone) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneStopFlashForPlayer");
	cell params[] = {
		2 * 4,
		playerid,
		zone
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForAll(int zone) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("GangZoneStopFlashForAll");
	cell params[] = {
		1 * 4,
		zone
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL Create3DTextLabel(const char *text, long color, float x, float y, float z, float DrawDistance, long virtualworld, bool testLOS) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Create3DTextLabel");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		8 * 4,
		text_.address(),
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

SAMPGDK_EXPORT bool SAMPGDK_CALL Delete3DTextLabel(int id) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Delete3DTextLabel");
	cell params[] = {
		1 * 4,
		id
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Attach3DTextLabelToPlayer");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Attach3DTextLabelToVehicle");
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

SAMPGDK_EXPORT bool SAMPGDK_CALL Update3DTextLabelText(int id, long color, const char *text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("Update3DTextLabelText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		3 * 4,
		id,
		color,
		text_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayer3DTextLabel(int playerid, const char *text, long color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("CreatePlayer3DTextLabel");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		10 * 4,
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
	return native(&::fakeAmx, params);
}

SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePlayer3DTextLabel(int playerid, int id) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("DeletePlayer3DTextLabel");
	cell params[] = {
		2 * 4,
		playerid,
		id
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL UpdatePlayer3DTextLabelText(int playerid, int id, long color, const char *text) {
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("UpdatePlayer3DTextLabelText");
	FakeAmxHeapObject text_(text);
	cell params[] = {
		4 * 4,
		playerid,
		id,
		color,
		text_.address()
	};
	return native(&::fakeAmx, params) != 0;
}

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption, 
	const char *info, const char *button1, const char *button2)
{
	static AMX_NATIVE native = Wrapper::GetInstance().GetNative("ShowPlayerDialog");
	FakeAmxHeapObject caption_(caption);
	FakeAmxHeapObject info_(info);
	FakeAmxHeapObject button1_(button1);
	FakeAmxHeapObject button2_(button2);
	cell params[] = {
		7 * 4,
		playerid,
		dialogid,
		style,
		caption_.address(),
		info_.address(),
		button1_.address(),
		button2_.address()
	};
	return native(&::fakeAmx, params) != 0;
}
