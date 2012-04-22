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

#ifndef SAMPGDK_A_SAMP_H
#define SAMPGDK_A_SAMP_H
#pragma once

#include <sampgdk/config.h>
#include <sampgdk/export.h>

#include <stddef.h>

#define MAX_PLAYER_NAME     (24)
#define MAX_PLAYERS         (500)
#define MAX_VEHICLES        (2000)
#define INVALID_PLAYER_ID   (0xFFFF)
#define INVALID_VEHICLE_ID  (0xFFFF)
#define NO_TEAM             (255)
#define MAX_OBJECTS         (1000)
#define INVALID_OBJECT_ID   (0xFFFF)
#define MAX_GANG_ZONES      (1024)
#define MAX_TEXT_DRAWS      (2048)
#define MAX_MENUS           (128)
#define MAX_3DTEXT_GLOBAL   (1024)
#define MAX_3DTEXT_PLAYER   (1024)
#define MAX_PICKUPS         (4096)
#define INVALID_MENU        (0xFF)
#define INVALID_TEXT_DRAW   (0xFFFF)
#define INVALID_GANG_ZONE   (-1)
#define INVALID_3DTEXT_ID   (0xFFFF)

SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessage(int playerid, int color, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendClientMessageToAll(int color, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToPlayer(int playerid, int senderid, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendPlayerMessageToAll(int senderid, const char *message);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendDeathMessage(int killer, int killee, int weapon);
SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForAll(const char *text, int time, int style);
SAMPGDK_EXPORT bool SAMPGDK_CALL GameTextForPlayer(int playerid, const char *text, int time, int style);
SAMPGDK_EXPORT int SAMPGDK_CALL GetServerTickCount(); /* $real_name=GetTickCount */
SAMPGDK_EXPORT int SAMPGDK_CALL GetMaxPlayers();

SAMPGDK_EXPORT bool SAMPGDK_CALL SetGameModeText(const char *text);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetTeamCount(int count);
SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClass(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
SAMPGDK_EXPORT int SAMPGDK_CALL AddPlayerClassEx(int teamid, int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicle(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticVehicleEx(int modelid, float spawn_x, float spawn_y, float spawn_z, float z_angle, int color1, int color2, int respawn_delay);
SAMPGDK_EXPORT int SAMPGDK_CALL AddStaticPickup(int model, int type, float x, float y, float z, int virtualworld);
SAMPGDK_EXPORT int SAMPGDK_CALL CreatePickup(int model, int type, float x, float y, float z, int virtualworld);
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyPickup(int pickup);
SAMPGDK_EXPORT bool SAMPGDK_CALL ShowNameTags(bool show);
SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerMarkers(bool mode);
SAMPGDK_EXPORT bool SAMPGDK_CALL GameModeExit();
SAMPGDK_EXPORT bool SAMPGDK_CALL SetWorldTime(int hour);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetWeaponName(int weaponid, char *name, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL EnableTirePopping(bool enable);
SAMPGDK_EXPORT bool SAMPGDK_CALL AllowInteriorWeapons(bool allow);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetWeather(int weatherid);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetGravity(float gravity);
SAMPGDK_EXPORT bool SAMPGDK_CALL AllowAdminTeleport(bool allow);
SAMPGDK_EXPORT bool SAMPGDK_CALL SetDeathDropAmount(int amount);
SAMPGDK_EXPORT bool SAMPGDK_CALL CreateExplosion(float x, float y, float z, int type, float radius);
SAMPGDK_EXPORT bool SAMPGDK_CALL EnableZoneNames(bool enable);
SAMPGDK_EXPORT bool SAMPGDK_CALL UsePlayerPedAnims();
SAMPGDK_EXPORT bool SAMPGDK_CALL DisableInteriorEnterExits();
SAMPGDK_EXPORT bool SAMPGDK_CALL SetNameTagDrawDistance(float distance);
SAMPGDK_EXPORT bool SAMPGDK_CALL DisableNameTagLOS();
SAMPGDK_EXPORT bool SAMPGDK_CALL LimitGlobalChatRadius(float chat_radius);
SAMPGDK_EXPORT bool SAMPGDK_CALL LimitPlayerMarkerRadius(float marker_radius);

SAMPGDK_EXPORT bool SAMPGDK_CALL ConnectNPC(const char *name, const char *script);
SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerNPC(int playerid);

SAMPGDK_EXPORT bool SAMPGDK_CALL IsPlayerAdmin(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL Kick(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL Ban(int playerid);
SAMPGDK_EXPORT bool SAMPGDK_CALL BanEx(int playerid, const char *reason);
SAMPGDK_EXPORT bool SAMPGDK_CALL SendRconCommand(const char *command);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsString(const char *varname, char *value, int size);
SAMPGDK_EXPORT int SAMPGDK_CALL GetServerVarAsInt(const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetServerVarAsBool(const char *varname);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerNetworkStats(int playerid, char *retstr, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetNetworkStats(char *retstr, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL GetPlayerVersion(int playerid, char *version, int len);

SAMPGDK_EXPORT int SAMPGDK_CALL MenuCreate(const char *title, int columns, float x, float y, float col1width, float col2width); /* $real_name=CreateMenu */
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDestroy(int menuid); /* $real_name=DestroyMenu */
SAMPGDK_EXPORT int SAMPGDK_CALL MenuAddItem(int menuid, int column, const char *menutext); /* $real_name=AddMenuItem */
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuSetColumnHeader(int menuid, int column, const char *columnheader); /* $real_name=SetMenuColumnHeader */
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuShowForPlayer(int menuid, int playerid); /* $real_name=ShowMenuForPlayer */
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuHideForPlayer(int menuid, int playerid); /* $real_name=HideMenuForPlayer */
SAMPGDK_EXPORT bool SAMPGDK_CALL IsValidMenu(int menuid);
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDisable(int menuid); /* $real_name=DisableMenu */
SAMPGDK_EXPORT bool SAMPGDK_CALL MenuDisableRow(int menuid, int row); /* $real_name=DisableMenuRow */
SAMPGDK_EXPORT int SAMPGDK_CALL GetPlayerMenu(int playerid);

#define CreateMenu MenuCreate
#define DestroyMenu MenuDestroy
#define AddMenuItem MenuAddItem
#define SetMenuColumnHeader MenuSetColumnHeader
#define ShowMenuForPlayer MenuShowForPlayer
#define HideMenuForPlayer MenuHideForPlayer
#define DisableMenu MenuDisable
#define DisableMenuRow MenuDisableRow

SAMPGDK_EXPORT int SAMPGDK_CALL TextDrawCreate(float x, float y, const char *text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawDestroy(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawLetterSize(int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawTextSize(int text, float x, float y);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawAlignment(int text, int alignment);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawColor(int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawUseBox(int text, bool use);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBoxColor(int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetShadow(int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetOutline(int text, int size);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawBackgroundColor(int text, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawFont(int text, int font);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetProportional(int text, bool set);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetSelectable(int text, bool set);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForPlayer(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForPlayer(int playerid, int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawShowForAll(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawHideForAll(int text);
SAMPGDK_EXPORT bool SAMPGDK_CALL TextDrawSetString(int text, const char *string);
SAMPGDK_EXPORT bool SAMPGDK_CALL SelectTextDraw(int playerid, int hovercolor);
SAMPGDK_EXPORT bool SAMPGDK_CALL CancelSelectTextDraw(int playerid);

SAMPGDK_EXPORT int SAMPGDK_CALL GangZoneCreate(float minx, float miny, float maxx, float maxy);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneDestroy(int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForPlayer(int playerid, int zone, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneShowForAll(int zone, int color);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForPlayer(int playerid, int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneHideForAll(int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForPlayer(int playerid, int zone, int flashcolor);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneFlashForAll(int zone, int flashcolor);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForPlayer(int playerid, int zone);
SAMPGDK_EXPORT bool SAMPGDK_CALL GangZoneStopFlashForAll(int zone);

SAMPGDK_EXPORT int SAMPGDK_CALL Create3DTextLabel(const char *text, int color, float x, float y, float z, float DrawDistance, int virtualworld, bool testLOS);
SAMPGDK_EXPORT bool SAMPGDK_CALL Delete3DTextLabel(int id);
SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToPlayer(int id, int playerid, float OffsetX, float OffsetY, float OffsetZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL Attach3DTextLabelToVehicle(int id, int vehicleid, float OffsetX, float OffsetY, float OffsetZ);
SAMPGDK_EXPORT bool SAMPGDK_CALL Update3DTextLabelText(int id, int color, const char *text);

SAMPGDK_EXPORT int SAMPGDK_CALL CreatePlayer3DTextLabel(int playerid, const char *text, int color, float x, float y, float z, float DrawDistance, int attachedplayer, int attachedvehicle, bool testLOS);
SAMPGDK_EXPORT bool SAMPGDK_CALL DeletePlayer3DTextLabel(int playerid, int id);
SAMPGDK_EXPORT bool SAMPGDK_CALL UpdatePlayer3DTextLabelText(int playerid, int id, int color, const char *text);

#define DIALOG_STYLE_MSGBOX (0)
#define DIALOG_STYLE_INPUT  (1)
#define DIALOG_STYLE_LIST   (2)

SAMPGDK_EXPORT bool SAMPGDK_CALL ShowPlayerDialog(int playerid, int dialogid, int style, const char *caption, const char *info, const char *button1, const char *button2);

typedef void (SAMPGDK_CALL *TimerHandler)(int timerid, void *param);

SAMPGDK_EXPORT int SAMPGDK_CALL CreateTimer(int interval, bool repeat, TimerHandler hander, void *param); /* $skip */
SAMPGDK_EXPORT bool SAMPGDK_CALL DestroyTimer(int timerid); /* $skip */

#define SetTimer CreateTimer
#define KillTimer DestroyTimer

#define PLAYER_STATE_NONE                    (0)
#define PLAYER_STATE_ONFOOT                  (1)
#define PLAYER_STATE_DRIVER                  (2)
#define PLAYER_STATE_PASSENGER               (3)
#define PLAYER_STATE_EXIT_VEHICLE            (4)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER    (5)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER (6)
#define PLAYER_STATE_WASTED                  (7)
#define PLAYER_STATE_SPAWNED                 (8)
#define PLAYER_STATE_SPECTATING              (9)

#define PLAYER_MARKERS_MODE_OFF              (0)
#define PLAYER_MARKERS_MODE_GLOBAL           (1)
#define PLAYER_MARKERS_MODE_STREAMED         (2)

#define WEAPON_BRASSKNUCKLE       (1)
#define WEAPON_GOLFCLUB           (2)
#define WEAPON_NITESTICK          (3)
#define WEAPON_KNIFE              (4)
#define WEAPON_BAT                (5)
#define WEAPON_SHOVEL             (6)
#define WEAPON_POOLSTICK          (7)
#define WEAPON_KATANA             (8)
#define WEAPON_CHAINSAW           (9)
#define WEAPON_DILDO              (10)
#define WEAPON_DILDO2             (11)
#define WEAPON_VIBRATOR           (12)
#define WEAPON_VIBRATOR2          (13)
#define WEAPON_FLOWER             (14)
#define WEAPON_CANE               (15)
#define WEAPON_GRENADE            (16)
#define WEAPON_TEARGAS            (17)
#define WEAPON_MOLTOV             (18)
#define WEAPON_COLT45             (22)
#define WEAPON_SILENCED           (23)
#define WEAPON_DEAGLE             (24)
#define WEAPON_SHOTGUN            (25)
#define WEAPON_SAWEDOFF           (26)
#define WEAPON_SHOTGSPA           (27)
#define WEAPON_UZI                (28)
#define WEAPON_MP5                (29)
#define WEAPON_AK47               (30)
#define WEAPON_M4                 (31)
#define WEAPON_TEC9               (32)
#define WEAPON_RIFLE              (33)
#define WEAPON_SNIPER             (34)
#define WEAPON_ROCKETLAUNCHER     (35)
#define WEAPON_HEATSEEKER         (36)
#define WEAPON_FLAMETHROWER       (37)
#define WEAPON_MINIGUN            (38)
#define WEAPON_SATCHEL            (39)
#define WEAPON_BOMB               (40)
#define WEAPON_SPRAYCAN           (41)
#define WEAPON_FIREEXTINGUISHER   (42)
#define WEAPON_CAMERA             (43)
#define WEAPON_PARACHUTE          (46)
#define WEAPON_VEHICLE            (49)
#define WEAPON_DROWN              (53)
#define WEAPON_COLLISION          (54)

#define KEY_ACTION                (1)
#define KEY_CROUCH                (2)
#define KEY_FIRE                  (4)
#define KEY_SPRINT                (8)
#define KEY_SECONDARY_ATTACK      (16)
#define KEY_JUMP                  (32)
#define KEY_LOOK_RIGHT            (64)
#define KEY_HANDBRAKE             (128)
#define KEY_LOOK_LEFT             (256)
#define KEY_SUBMISSION            (512)
#define KEY_LOOK_BEHIND           (512)
#define KEY_WALK                  (1024)
#define KEY_ANALOG_UP             (2048)
#define KEY_ANALOG_DOWN           (4096)
#define KEY_ANALOG_LEFT           (8192)
#define KEY_ANALOG_RIGHT          (16384)
#define KEY_YES                   (65536)
#define KEY_NO                    (131072)
#define KEY_CTRL_BACK             (262144)
#define KEY_UP                    (-128)
#define KEY_DOWN                  (128)
#define KEY_LEFT                  (-128)
#define KEY_RIGHT                 (128)

#define CLICK_SOURCE_SCOREBOARD   (0)

SAMPGDK_EXPORT bool SAMPGDK_CALL gpci(int playerid, char *buffer, int size);

#ifdef __cplusplus

#include <string>

template<size_t N> inline bool GetNetworkStats(char (&retstr)[N]) {
	return GetNetworkStats(retstr, N);
}
template<size_t N> inline bool GetPlayerNetworkStats(int playerid, char (&retstr)[N]) {
	return GetPlayerNetworkStats(playerid, retstr, N);
}
template<size_t N> inline bool GetPlayerVersion(int playerid, char (&version)[N]) {
	return GetPlayerVersion(playerid, version, N);
}
template<size_t N> inline bool GetWeaponName(int weaponid, char (&name)[N]) {
	return GetWeaponName(weaponid, name, N);
}

class Menu {
public:
	Menu(int menuid) : id_(menuid) {}
	virtual ~Menu() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }	

	static Menu Create(const char *title, int columns, float x, float y, float col1width, float col2width = 0.0) 
		{ return ::MenuCreate(title, columns, x, y, col1width, col2width); }
	static Menu Create(const std::string &title, int columns, float x, float y, float col1width, float col2width) 
		{ return ::MenuCreate(title.c_str(), columns, x, y, col1width, col2width); }

	bool Destroy() const
		{ return ::MenuDestroy(id_); }
	int AddItem(int column, const char *menutext) const
		{ return ::MenuAddItem(id_, column, menutext); }
	int AddItem(int column, const std::string &menutext) const
		{ return ::MenuAddItem(id_, column, menutext.c_str()); }
	bool SetColumnHeader(int column, const char *columnheader) const
		{ return ::MenuSetColumnHeader(id_, column, columnheader); }
	bool SetColumnHeader(int column, const std::string &columnheader) const
		{ return ::MenuSetColumnHeader(id_, column, columnheader.c_str()); }
	bool ShowForPlayer(int playerid) const
		{ return ::MenuShowForPlayer(id_, playerid); }
	bool HideForPlayer(int playerid) const
		{ return ::MenuHideForPlayer(id_, playerid); }
	bool IsValid() const
		{ return ::IsValidMenu(id_); }
	bool Disable() const
		{ return ::MenuDisable(id_); }
	bool DisableRow(int row) const
		{ return ::MenuDisableRow(id_, row); }

private:
	Menu& operator=(const Menu& rhs);
	const int id_;
};

class TextDraw {
public:
	TextDraw(int text) : id_(text) {}
	virtual ~TextDraw() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	static TextDraw Create(float x, float y, const char *text) 
		{ return ::TextDrawCreate(x, y, text); }
	static TextDraw Create(float x, float y, const std::string &text) 
		{ return ::TextDrawCreate(x, y, text.c_str()); }

	bool Destroy() const 
		{ return ::TextDrawDestroy(id_); }
	bool SetLetterSize(float x, float y) const
		{ return ::TextDrawLetterSize(id_, x, y); }
	bool SetTextSize(float x, float y) const 
		{ return ::TextDrawTextSize(id_, x, y); }
	bool SetAlignment(int alignment) const 
		{ return ::TextDrawAlignment(id_, alignment); }
	bool SetColor(int color) const 
		{ return ::TextDrawColor(id_, color); }
	bool SetBackgroundColor(int color) const 
		{ return ::TextDrawBackgroundColor(id_, color); }
	bool UseBox(bool use) const 
		{ return ::TextDrawUseBox(id_, use); }
	bool SetBoxColor(int color) const 
		{ return ::TextDrawBoxColor(id_, color); }
	bool SetShadow(int size) const 
		{ return ::TextDrawSetShadow(id_, size); }
	bool SetOutline(int size) const 
		{ return ::TextDrawSetOutline(id_, size); }
	bool SetFont(int font) const 
		{ return ::TextDrawFont(id_, font); }
	bool SetProportional(bool set) const 
		{ return ::TextDrawSetProportional(id_, set); }
	bool SetString(const char *string) const
		{ return ::TextDrawSetString(id_, string); }
	bool SetString(const std::string &string) const
		{ return ::TextDrawSetString(id_, string.c_str()); }
	bool SetSelectable(bool set) const
		{ return ::TextDrawSetSelectable(id_, set); }
	bool ShowForPlayer(int playerid) const 
		{ return ::TextDrawShowForPlayer(playerid, id_); }
	bool HideForPlayer(int playerid) const 
		{ return ::TextDrawHideForPlayer(playerid, id_); }
	bool ShowForAll() const 
		{ return ::TextDrawShowForAll(id_); }
	bool HideForAll() const
		{ return ::TextDrawHideForAll(id_); }

private:
	TextDraw& operator=(const TextDraw& rhs);
	const int id_;
};

class GangZone {
public:
	GangZone(int zone) : id_(zone) {}
	virtual ~GangZone() {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	static GangZone Create(float minx, float miny, float maxx, float maxy) 
		{ return ::GangZoneCreate(minx, miny, maxx, maxy); }

	bool Destroy() const
		{ return ::GangZoneDestroy(id_); }
	bool ShowForPlayer(int playerid, int color) const
		{ return ::GangZoneShowForPlayer(playerid, id_, color); }
	bool ShowForAll(int color) const
		{ return ::GangZoneShowForAll(id_, color); }
	bool HideForPlayer(int playerid) const
		{ return ::GangZoneHideForPlayer(playerid, id_); }
	bool HideForAll() const
		{ return ::GangZoneHideForAll(id_); }
	bool FlashForPlayer(int playerid, int flashcolor) const
		{ return ::GangZoneFlashForPlayer(playerid, id_, flashcolor); }
	bool FlashForAll(int flashcolor) const
		{ return ::GangZoneFlashForAll(id_, flashcolor); }
	bool StopFlashForPlayer(int playerid) const
		{ return ::GangZoneStopFlashForPlayer(playerid, id_); }
	bool StopFlashForAll() const
		{ return ::GangZoneStopFlashForAll(id_); }

private:
	GangZone& operator=(const GangZone& rhs);
	const int id_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_SAMP_H */
